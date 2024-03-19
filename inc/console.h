#pragma once

namespace game
{
	class console
	{
	public:
		static void printf(const char* fmt, ...) {
			// 
			static auto p1 = RelocAddr<std::uintptr_t*>(0x06532650); // 0x06581A10
			static auto p2 = RelocAddr<std::uintptr_t(*)(std::uintptr_t, const char*, va_list)>(0x0286EF28); // 0x028D8B18

			if (*p1 && p2) {
				auto args = va_list();
				va_start(args, fmt);
				(*p2)(*p1, fmt, args);
				va_end(args);
			}
		}

		static std::uintptr_t execute(const char* cmd) {
			static auto p1 = RelocAddr<std::uintptr_t(*)(std::double_t, const char*)>(0x028694B4); // 0x028D30A4
			return p1 ? (*p1)(0.0, cmd) : 0;
		}
	};
}
