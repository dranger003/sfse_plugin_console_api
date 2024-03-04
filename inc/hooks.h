#pragma once

namespace game
{
	class hooks
	{
	private:
		static BranchTrampoline* trampoline() {
			static auto _trampoline = BranchTrampoline();
			_trampoline.create(0x1000); // 4KiB
			return &_trampoline;
		}

	public:
		using game_shutting_down_t = void (*)();
		using console_execute_command_t = bool (*)(const std::string&);
		using console_output_line_t = bool (*)(const std::string&);
		using hook_some_event_t = void (*)(std::uintptr_t, std::uintptr_t);

		class hook_game_shutting_down {
		private:
			static const std::uintptr_t rva = 0x02448A2C; // 0x024489DC

			struct ret_t : Xbyak::CodeGenerator {
				ret_t() {
					Xbyak::Label label1;
					push(rbp);										//    /00/00/D | 40 55                                | 40 55
					push(rbx);										//    /00/00/D | 53                                   | 53
					push(rsi);										//    /00/00/D | 56                                   | 56
					push(rdi);										//    /00/00/D | 57                                   | 57
					push(r12);										//    /00/00/D | 41 54                                | 41 54
					jmp(ptr[rip + label1]);
					L(label1);
					dq(RelocAddr<std::uintptr_t>(rva + 7).getUIntPtr());
				}
			};

			static const ret_t& ret() {
				static auto _ret = ret_t();
				return _ret;
			}

			static std::uintptr_t fcn(std::double_t unk1, std::uintptr_t unk2, std::double_t unk3) {
				_callback()();

				auto res = ret().getCode<decltype(&fcn)>()(unk1, unk2, unk3);
				return res;
			}

		public:
			static void apply(game_shutting_down_t callback) {
				_callback() = callback;
				auto reloc = RelocAddr<std::uintptr_t>(rva);
				game::hooks::trampoline()->write6Branch(reloc.getUIntPtr(), reinterpret_cast<std::uintptr_t>(&fcn));
				safeWrite8(reloc.getUIntPtr() + 6, 0x90);
			}

		private:
			static game_shutting_down_t& _callback() {
				static auto _cb = game_shutting_down_t(nullptr);
				return _cb;
			}
		};

		class hook_console_execute_command {
		private:
			static const std::uintptr_t rva = 0x028D30A4; // 0x028D3064

			struct ret_t : Xbyak::CodeGenerator {
				ret_t() {
					Xbyak::Label label1;
					mov(rax, rsp);									//    /00/00/D | 48 8B C4                             | 48 8B C4
					mov(ptr[rax + 0x10], rdx);						// DSP/03/01/D | 48 89 50 10                          | 48 89 50 ??
					jmp(ptr[rip + label1]);
					L(label1);
					dq(RelocAddr<std::uintptr_t>(rva + 7).getUIntPtr());
				}
			};

			static const ret_t& ret() {
				static auto _ret = ret_t();
				return _ret;
			}

			static std::uintptr_t fcn(std::double_t unk1, std::uintptr_t unk2, ...) {
				if (!_callback()(reinterpret_cast<const char*>(unk2)))
					return 0;

				auto res = ret().getCode<decltype(&fcn)>()(unk1, unk2);
				return res;
			}

		public:
			static void apply(console_execute_command_t callback) {
				_callback() = callback;
				auto reloc = RelocAddr<std::uintptr_t>(rva);
				game::hooks::trampoline()->write6Branch(reloc.getUIntPtr(), reinterpret_cast<std::uintptr_t>(&fcn));
				safeWrite8(reloc.getUIntPtr() + 6, 0x90);
			}

		private:
			static console_execute_command_t& _callback() {
				static auto _cb = console_execute_command_t(nullptr);
				return _cb;
			}
		};

		class hook_console_output_line {
		private:
			static const std::uintptr_t rva = 0x028D8945; // 0x028D8905

			struct ret_t : Xbyak::CodeGenerator {
				ret_t() {
					Xbyak::Label label1;
					mov(ptr[rsp + 0x8], rbx);						// DSP/04/01/D | 48 89 5C 24 08                       | 48 89 5C 24 ??
					jmp(ptr[rip + label1]);
					L(label1);
					dq(RelocAddr<std::uintptr_t>(rva + 5).getUIntPtr());
				}
			};

			static const ret_t& ret() {
				static auto _ret = ret_t();
				return _ret;
			}

			static void fcn(std::uintptr_t unk1, std::uintptr_t unk2) {
				if (!_callback()(reinterpret_cast<const char*>(unk2)))
					return;

				ret().getCode<decltype(&fcn)>()(unk1, unk2);
			}

		public:
			static void apply(console_output_line_t callback) {
				_callback() = callback;
				auto reloc = RelocAddr<std::uintptr_t>(rva);
				game::hooks::trampoline()->write5Branch(reloc.getUIntPtr(), reinterpret_cast<std::uintptr_t>(&fcn));
			}

		private:
			static console_output_line_t& _callback() {
				static auto _cb = console_output_line_t(nullptr);
				return _cb;
			}
		};
	};
}
