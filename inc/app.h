#pragma once

namespace plugin
{
	static PluginHandle handle = static_cast<PluginHandle>(0);

	class app
	{
	private:
		app() {}

	public:
		class config : public plugin::config
		{
		public:
			struct {
				bool enable;
				bool overwrite;
				std::string path;
			} file_output;

			struct {
				bool enable;
				std::string host;
				std::uint16_t port;
				bool disable_cors;
				bool disable_static_files;
				std::string path;
			} api_hosting;

			virtual void load(const std::string& path) {
				plugin::config::load(path);

				auto file_output_was_enabled = file_output.enable;
				auto web_console_was_enabled = api_hosting.enable;

				{ // Plugin
					file_output.enable = config::get<bool>("Plugin.bEnableFileOutput", false);
					api_hosting.enable = config::get<bool>("Plugin.bEnableWebConsole", false);
				}

				{ // FileOutput
					file_output.overwrite = config::get<bool>("FileOutput.bOverwrite", true);
					file_output.path = utils::expand_path(config::get<std::string>("FileOutput.sPath", "Data\\SFSE\\plugins\\" PLUGIN_NAME ".log"));
				}

				{ // WebConsole
					api_hosting.host = config::get<std::string>("WebConsole.sHost", "127.0.0.1");
					api_hosting.port = config::get<std::uint32_t>("WebConsole.iPort", 55555);
					api_hosting.disable_cors = config::get<bool>("WebConsole.bDisableCORS", false);
					api_hosting.disable_static_files = config::get<bool>("WebConsole.bDisableStaticFiles", false);
					api_hosting.path = utils::expand_path(config::get<std::string>("WebConsole.sStaticFilesPath", "Data\\SFSE\\plugins\\" PLUGIN_NAME "\\"));
				}

				if (!file_output_was_enabled && file_output.enable) {
					plugin::app::console_output_file()->open(file_output.path, file_output.overwrite ? std::ios::out : std::ios::app);
					plugin::app::log()->i("console output to file enabled [{}]", file_output.path);
				}
				else if (file_output_was_enabled && !file_output.enable) {
					plugin::app::console_output_file()->close();
					plugin::app::log()->i("console output to file disabled");
				}
				else if (file_output_was_enabled && file_output.enable) {
					plugin::app::console_output_file()->close();
					plugin::app::console_output_file()->open(file_output.path, file_output.overwrite ? std::ios::out : std::ios::app);
					plugin::app::log()->i("console output to file re-opened [{}]", file_output.path);
				}

				plugin::app::server()->set_disable_cors(api_hosting.disable_cors);
				plugin::app::server()->set_disable_static_files(api_hosting.disable_static_files);
				plugin::app::server()->set_path(api_hosting.path);

				if (api_hosting.enable) {
					if (plugin::app::server()->running()) {
						plugin::app::server()->stop();
						plugin::app::log()->i("http server stopped");
					}

					if (!plugin::app::server()->start(api_hosting.host, api_hosting.port)) {
						plugin::app::log()->i("http server not started (unable to start)");
					}
					else {
						if (plugin::app::server()->wait_for_listening()) {
							api_hosting.host = plugin::app::server()->host();
							plugin::app::log()->i("http server started on http://{}:{}/", api_hosting.host, api_hosting.port);
						}
						else {
							plugin::app::log()->i("http server not started (unable to start)");
						}
					}
				}
			}
		};

		static plugin::app* inst() {
			static auto _inst = plugin::app();
			return &_inst;
		}

		static plugin::log* log() {
			static auto _log = plugin::log();
			return &_log;
		}

		static plugin::app::config* cfg() {
			static auto _cfg = plugin::app::config();
			return &_cfg;
		}

		static plugin::server* server() {
			static auto _server = plugin::server();
			return &_server;
		}

		static plugin::log* console_output_file() {
			static auto _output = plugin::log();
			return &_output;
		}

		static boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<4096>>* console_output_queue() {
			static auto _queue = boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<4096>>();
			return &_queue;
		}

		bool preload(const SFSEInterface*) {
			// unused for now
			return true;
		}

		bool load(const SFSEInterface* sfse) {
			auto messaging = static_cast<SFSEMessagingInterface*>(sfse->QueryInterface(kInterface_Messaging));
			return messaging->RegisterListener(plugin::handle, "SFSE", &app::_event_callback);
		}

	private:
		static void _event_callback(SFSEMessagingInterface::Message* message) {
			switch (message->type) {
			case SFSEMessagingInterface::kMessage_PostLoad:
				plugin::app::inst()->_postload();
				break;
			case SFSEMessagingInterface::kMessage_PostPostLoad:
				plugin::app::inst()->_postpostload();
				break;
			}
		}

		void _postload() {
			auto res = _init_log();
			if (!res) {
				return;
			}

			plugin::app::log()->i("log initialized");

			res = _init_server();
			if (!res) {
				plugin::app::log()->e("unable to initialize http server");
				return;
			}

			plugin::app::log()->i("http server initialized");

			res = _init_config();
			if (!res) {
				plugin::app::log()->e("unable to load config");
				return;
			}

			plugin::app::log()->i("config initialized");

			res = _init_hooks();
			if (!res) {
				plugin::app::log()->e("unable to apply hooks");
				return;
			}

			plugin::app::log()->i("hooks applied");
		}

		void _postpostload() {
			// unused
		}

		bool _init_log() {
			try {
				auto path = std::filesystem::path(utils::get_env("USERPROFILE")) / "Documents/My Games/Starfield/SFSE/Logs/" PLUGIN_NAME ".log";
				plugin::app::log()->open(path.string());
				return true;
			}
			catch (std::exception&) {
				return false;
			}
		}

		bool _init_server() {
			try {
				static auto console_endpoint = [](
					boost::asio::ip::tcp::socket& socket,
					boost::beast::http::request<boost::beast::http::string_body>& request,
					boost::beast::http::response<boost::beast::http::string_body>& response
				) -> co_async<bool> {
					plugin::app::console_output_queue()->consume_all([](std::string&) {});

					auto command = request.body();
					game::console::execute(command.c_str());

					auto done = false;
					auto output_line = std::string();
					auto timestamp = std::chrono::steady_clock::now();
					auto body = std::ostringstream();

					while (!done) {
						while (!plugin::app::console_output_queue()->pop(output_line)) {
							if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timestamp).count() > 500) {
								done = true;
								break;
							}

							plugin::utils::async_sleep<10>();
						}

						if (done)
							continue;

						body << output_line;
						timestamp = std::chrono::steady_clock::now();
					}

					response.set(boost::beast::http::field::content_type, "text/plain");
					response.set(boost::beast::http::field::cache_control, "no-cache");
					response.body() = body.str();

					co_return true;
				};

				plugin::app::server()->map_post("/console", console_endpoint);

				return true;
			}
			catch (std::exception&) {
				return false;
			}
		}

		bool _init_config() {
			try {
				auto path = std::filesystem::path("Data\\SFSE\\plugins\\" PLUGIN_NAME ".ini");
				plugin::app::cfg()->load(path.string());
				return true;
			}
			catch (std::exception&) {
				return false;
			}
		}

		bool _init_hooks() {
			try {
				game::hooks::hook_game_shutting_down::apply([]() {
					plugin::app::server()->stop();
					plugin::app::log()->i("game shutting down, http server stopped");
				});

				game::hooks::hook_console_execute_command::apply([](const std::string& command) -> bool {
					static auto dump_config = []() {
						game::console::printf("LOG path >> %s", plugin::app::log()->path().c_str());
						game::console::printf("Plugin.bEnableFileOutput >> %u", (std::uint8_t)plugin::app::cfg()->file_output.enable);
						game::console::printf("Plugin.bEnableWebConsole >> %u", (std::uint8_t)plugin::app::cfg()->api_hosting.enable);
						game::console::printf("FileOutput.bOverwrite >> %u", (std::uint8_t)plugin::app::cfg()->file_output.overwrite);
						game::console::printf("FileOutput.sPath >> %s", std::filesystem::absolute(plugin::app::cfg()->file_output.path).string().c_str());
						game::console::printf("WebConsole.sHost >> %s", plugin::app::cfg()->api_hosting.host.c_str());
						game::console::printf("WebConsole.iPort >> %u", plugin::app::cfg()->api_hosting.port);
						game::console::printf("WebConsole.bDisableCORS >> %u", plugin::app::cfg()->api_hosting.disable_cors);
						game::console::printf("WebConsole.bDisableStaticFiles >> %u", plugin::app::cfg()->api_hosting.disable_static_files);
						game::console::printf("WebConsole.sStaticFilesPath >> %s", std::filesystem::absolute(plugin::app::cfg()->api_hosting.path).string().c_str());
					};

					auto match = std::smatch();
					if (std::regex_search(command, match, std::regex(R"(^(\w+)\.(\w+)$)")) && match[1].str() == PLUGIN_NAME) {
						if (match[2] == "reload_config") {
							game::console::printf(command.c_str());
							std::thread([]() {
								plugin::app::cfg()->reload();
								dump_config();
							}).detach();

							return false;
						}
						else if (match[2] == "dump_config") {
							game::console::printf(command.c_str());
							dump_config();

							return false;
						}
					}

					return true;
				});

				game::hooks::hook_console_output_line::apply([](const std::string& line) -> bool {
					if (plugin::app::cfg()->file_output.enable) {
						plugin::app::console_output_file()->p(line, false, true);
					}

					if (plugin::app::cfg()->api_hosting.enable) {
						while (!plugin::app::console_output_queue()->push(line))
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
					}

					return true;
				});

				return true;
			}
			catch (std::exception&) {
				return false;
			}
		}
	};
}
