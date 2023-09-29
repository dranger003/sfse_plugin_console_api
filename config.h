#pragma once

namespace plugin
{
	class config
	{
	protected:
		config() {}

	public:
		virtual ~config() {}

		virtual void load(const std::string& path) {
			_path = path;
			boost::property_tree::ini_parser::read_ini(_path, _ptree);
		}

		virtual void reload() {
			load(_path);
		}

		template<typename T>
		T get(const std::string& key, T default_value) {
			try {
				return _ptree.get<T>(key);
			}
			catch (std::exception&) {
				return default_value;
			}
		}

	private:
		std::string _path;
		boost::property_tree::ptree _ptree;
	};
}
