#include <pch.h>

BSTEventDetail::SinkBase::~SinkBase() {}

namespace plugin
{
	// 2023-09-30 14:34:17.255 [info] MenuOpenCloseEvent [FaderMenu][true]
	// 2023-09-30 14:34:17.255 [info] MenuOpenCloseEvent [LoadingMenu][true]
	// 2023-09-30 14:34:18.493 [info] MenuOpenCloseEvent [LoadingMenu][false]
	// 2023-09-30 14:34:18.493 [info] MenuOpenCloseEvent [FaderMenu][false]
	// 2023-09-30 14:34:18.701 [info] MenuOpenCloseEvent [MainMenu][true]
	// 2023-09-30 14:34:24.991 [info] MenuOpenCloseEvent [CursorMenu][true]
	// 2023-09-30 14:34:36.139 [info] MenuOpenCloseEvent [Console][true]
	// 2023-09-30 14:34:39.374 [info] MenuOpenCloseEvent [Console][false]
	// 2023-09-30 14:35:00.521 [info] MenuOpenCloseEvent [MainMenu][false]
	// 2023-09-30 14:35:00.521 [info] MenuOpenCloseEvent [FaderMenu][true]
	// 2023-09-30 14:35:00.522 [info] MenuOpenCloseEvent [CursorMenu][false]
	// 2023-09-30 14:35:05.048 [info] MenuOpenCloseEvent [LoadingMenu][true]
	// 2023-09-30 14:35:18.621 [info] MenuOpenCloseEvent [LoadingMenu][false]
	// 2023-09-30 14:35:18.763 [info] MenuOpenCloseEvent [HUDMenu][true]
	// 2023-09-30 14:35:18.763 [info] MenuOpenCloseEvent [HUDMessagesMenu][true]
	// 2023-09-30 14:35:20.498 [info] MenuOpenCloseEvent [FaderMenu][false]
	// 2023-09-30 14:35:52.294 [info] MenuOpenCloseEvent [DialogueMenu][true]
	// 2023-09-30 14:35:52.311 [info] MenuOpenCloseEvent [CursorMenu][true]
	// 2023-09-30 14:36:00.275 [info] MenuOpenCloseEvent [DialogueMenu][false]
	// 2023-09-30 14:36:00.275 [info] MenuOpenCloseEvent [CursorMenu][false]
	// 2023-09-30 14:36:27.991 [info] PlayerAddItemEvent
	// 2023-09-30 14:36:27.992 [info] TESContainerChangedEvent [0xFF017620][0x00000014][0x0000000F][2246]
	// 2023-09-30 14:36:38.612 [info] PlayerAddItemEvent
	// 2023-09-30 14:36:38.612 [info] TESContainerChangedEvent [0xFF021951][0x00000014][0x0000000F][15786]

	IMPLEMENT_EVENT_SINK_BEGIN(TESContainerChanged)
		if (arEvent.sourceContainerFormID == 0x00000014 || arEvent.targetContainerFormID == 0x00000014) {
			plugin::app::log()->i(
				"TESContainerChangedEvent [0x{:08X}][0x{:08X}][0x{:08X}][{}]",
				arEvent.sourceContainerFormID,
				arEvent.targetContainerFormID,
				arEvent.itemFormID,
				arEvent.count
			);
		}
	IMPLEMENT_EVENT_SINK_END(TESContainerChanged)

	IMPLEMENT_EVENT_SINK_BEGIN(PlayerAddItem)
		plugin::app::log()->i("PlayerAddItemEvent");
	IMPLEMENT_EVENT_SINK_END(PlayerAddItem)

	IMPLEMENT_EVENT_SINK_BEGIN(MenuOpenClose)
		plugin::app::log()->i("MenuOpenCloseEvent [{}][{}]", arEvent.MenuName.c_str(), arEvent.bOpening);
	IMPLEMENT_EVENT_SINK_END(MenuOpenClose)
}

#include "sfse/GameForms.cpp"
