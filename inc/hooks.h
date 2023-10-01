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
		//using console_execute_command_t = bool (*)(const std::string&);
		using console_execute_command_t = bool (*)(const SCRIPT_PARAMETER* paramInfo, const char*, TESObjectREFR* thisObj, TESObjectREFR* containingObj, Script* script, ScriptLocals* locals, float* result, u32* opcodeOffsetPtr);
		using console_output_line_t = bool (*)(const std::string&);

		class hook_game_shutting_down {
		private:
			static const std::uintptr_t rva = 0x023FB21C;

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

		class hook_game_command_init {
		private:
			static const std::uintptr_t rva = 0x01AEB32C;

			static void fcn() {
				auto i = 0;
				auto cmds = commands();
				auto dummy_func = RelocAddr<void*>(0x012559D0);

				for (Script::SCRIPT_FUNCTION* iter = g_firstConsoleCommand; iter->eOutput < (Script::kScript_NumConsoleCommands + Script::kScript_ConsoleOpBase); ++iter) {
					Script::SCRIPT_FUNCTION& cmd = *iter;

					if (!cmd.pExecuteFunction)
						continue;

					if (i < cmds.size() && cmd.pExecuteFunction == dummy_func) {
						cmd.pFunctionName = cmds[i]->pFunctionName;
						cmd.pShortName = cmds[i]->pShortName;
						cmd.pHelpString = cmds[i]->pHelpString;
						cmd.bReferenceFunction = cmds[i]->bReferenceFunction;
						cmd.sParamCount = cmds[i]->sParamCount;
						cmd.pExecuteFunction = cmds[i]->pExecuteFunction;
						cmd.bEditorFilter = cmds[i]->bEditorFilter;
						cmd.bInvalidatesCellList = cmds[i]->bInvalidatesCellList;
						++i;
					}
				}

				return;
			}

			static std::vector<Script::SCRIPT_FUNCTION*>& commands(std::vector<Script::SCRIPT_FUNCTION*> cmds = std::vector<Script::SCRIPT_FUNCTION*>()) {
				auto static _commands = cmds;
				return _commands;
			}

		public:
			static void apply(std::vector<Script::SCRIPT_FUNCTION*> cmds) {
				commands(cmds);

				static struct _code : Xbyak::CodeGenerator {
					_code() {
						Xbyak::Label label1;
						mov(byte[rbx + 0x10], 0x1);						// IMM/03/01/D | C6 43 10 01                          | C6 43 10 ??
						add(rsp, 0x20);									// IMM/03/01/D | 48 83 C4 20                          | 48 83 C4 ??
						pop(rbx);										//    /00/00/D | 5B                                   | 5B
						//ret();										//    /00/00/D | C3                                   | C3
						jmp(ptr[rip + label1]);
						L(label1);
						dq(reinterpret_cast<uint64_t>(fcn));
					}
				} code;

				auto addr = RelocAddr<std::uintptr_t>(rva);
				game::hooks::trampoline()->write6Branch(addr, code.getCode<std::uintptr_t>());
				auto buf = std::vector<std::uint8_t>(10 - 6, 0x90);
				safeWriteBuf(addr + 6, &buf[0], buf.size());
			}
		};

		class hook_console_output_line {
		private:
			static const std::uintptr_t rva = 0x02886905;

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
