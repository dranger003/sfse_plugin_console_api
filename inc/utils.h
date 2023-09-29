#pragma once

namespace plugin
{
	class utils
	{
	public:
		static std::string get_timestamp() {
			auto now = std::chrono::system_clock::now();

			auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
			auto epoch = now_ms.time_since_epoch();
			auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
			auto ms = value.count() % 1000;
			auto now_time_t = std::chrono::system_clock::to_time_t(now);

			auto now_tm = std::tm();
			localtime_s(&now_tm, &now_time_t);

			return std::format("{:4}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}", now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday, now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec, ms);
		}

		static std::string get_env(const char* var_name) {
			auto buf = (char*)nullptr;
			auto len = std::size_t(0);
			auto val = std::string();

			if (!_dupenv_s(&buf, &len, var_name) && buf) {
				val = buf;
				free(buf);
			}

			return val;
		}

		static std::string expand_path(const std::string& path) {
			auto expanded_path = std::string(path);
			auto regex = std::regex("%(\\w+)%");
			auto match = std::smatch();

			while (std::regex_search(expanded_path, match, regex)) {
				auto value = utils::get_env(match[1].str().c_str());
				expanded_path.replace(match.position(), match.length(), value);
			}

			return expanded_path;
		}

		static std::map<std::string, std::string> parse_http_query(const std::string& query) {
			auto data = std::map<std::string, std::string>();
			auto regex = std::regex("([^&=]+)=([^&]*)");

			for (std::sregex_iterator i = std::sregex_iterator(query.begin(), query.end(), regex);
				i != std::sregex_iterator();
				++i) {
				std::smatch match = *i;
				data[match[1]] = match[2];
			}

			return data;
		}

		template<std::chrono::milliseconds::rep MS>
		static co_async<void> async_sleep() {
			auto timer = boost::asio::steady_timer(co_await boost::asio::this_coro::executor, std::chrono::milliseconds(MS));
			co_await timer.async_wait(boost::asio::use_awaitable);
		}
	};
}
