#pragma once

namespace plugin
{
	class log
	{
	public:
		void open(const std::string& path, std::ios_base::openmode mode = std::ios::out) {
			log::close();

			_path = path;
			_stream.open(_path, mode);
		}

		void close() {
			if (_stream.is_open())
				_stream.close();
		}

		void reopen(std::ios_base::openmode mode) {
			open(_path, mode);
		}

		void p(const std::string& message, bool add_nl = true, bool flush = true) {
			if (!_stream.is_open())
				return;
		
			_stream << message;
		
			if (add_nl)
				_stream << std::endl;
		
			if (flush)
				_stream.flush();
		}

		template<typename... Args>
		void i(const std::string& fmt, Args&&... args)
		{
			auto message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			p(std::format("{} [info] {}", utils::get_timestamp(), message));
		}

		template<typename... Args>
		void w(const std::string& fmt, Args&&... args)
		{
			auto message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			p(std::format("{} [warning] {}", utils::get_timestamp(), message));
		}

		template<typename... Args>
		void e(const std::string& fmt, Args&&... args)
		{
			auto message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			p(std::format("{} [error] {}", utils::get_timestamp(), message));
		}

	private:
		std::string _path;
		std::ofstream _stream;
	};
}
