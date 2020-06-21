﻿#include "pch.h"
#include "plugin_64.h"

namespace TooltipAndButton {
	extern "C" {
		void tooltipAndButtonProc1();
		void tooltipAndButtonProc2();
		void tooltipAndButtonProc3();
		void tooltipAndButtonProc4();
		void tooltipAndButtonProc5();
		void tooltipAndButtonProc6();
		uintptr_t tooltipAndButtonProc1ReturnAddress;
		uintptr_t tooltipAndButtonProc1CallAddress;
		uintptr_t tooltipAndButtonProc2ReturnAddress;
		uintptr_t tooltipAndButtonProc3ReturnAddress;
		uintptr_t tooltipAndButtonProc4ReturnAddress1;
		uintptr_t tooltipAndButtonProc4ReturnAddress2;
		uintptr_t tooltipAndButtonProc5ReturnAddress1;
		uintptr_t tooltipAndButtonProc5ReturnAddress2;
		uintptr_t tooltipAndButtonProc6ReturnAddress1;
		uintptr_t tooltipAndButtonProc6ReturnAddress2;
	}

	DllError tooltipAndButtonProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			//  mov     byte ptr [rbp+440h+var_3B8], 0
			BytePattern::temp_instance().find_pattern("C6 85 88 00 00 00 00 45 0F B6 04 06");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				tooltipAndButtonProc1CallAddress = Injector::GetBranchDestination(address + 0x16).as_int();

				// nop
				tooltipAndButtonProc1ReturnAddress = address + 0x1B;

				Injector::MakeJMP(address, tooltipAndButtonProc1, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc1Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc1Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// movzx   eax, byte ptr [r14+rax]
			BytePattern::temp_instance().find_pattern("41 0F B6 04 06 4D 8B 8C C7 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r9, r9
				tooltipAndButtonProc2ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, tooltipAndButtonProc2, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc2Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc2Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov ecx, ebx
			BytePattern::temp_instance().find_pattern("8B CB 0F B6 04 01 4D 8B 9C C7 E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test r11, r11
				tooltipAndButtonProc3ReturnAddress = address + 0xE;

				Injector::MakeJMP(address, tooltipAndButtonProc3, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc3Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc3Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// cmp     [rbp+440h+var_400], 0
			BytePattern::temp_instance().find_pattern("83 7D 40 00 0F 85 F8 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz {loc_xxxxx} / inc ebx
				tooltipAndButtonProc4ReturnAddress1 = Injector::GetBranchDestination(address + 0x4).as_int();

				// jz loc_xxxxx
				tooltipAndButtonProc4ReturnAddress2 = address + 14;

				Injector::MakeJMP(address, tooltipAndButtonProc4, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc4Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc4Injector = true;
		}

		return e;
	}

	// これはwin32のときはUnk3にあったが統合した。proc1～4とは別のprocにinjectしている
	DllError tooltipAndButtonProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov     rdi, [rsp+48h+arg_0]
			BytePattern::temp_instance().find_pattern("48 8B 7C 24 50 41 3B F6 44 0F 4F F6");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理のリターン先２")) {
				tooltipAndButtonProc5ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.tooltipAndButtonProc5Injector = true;
			}

			// movsxd  rax, ebx
			BytePattern::temp_instance().find_pattern("48 63 C3 0F B6 0C 28 4D 8B 84 CC E8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz short loc_xxxxx
				tooltipAndButtonProc5ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, tooltipAndButtonProc5, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc5Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc5Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc6Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// inc ebx
			BytePattern::temp_instance().find_pattern("FF C3 3B 5D 08 7D 23 41 B9 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１のカウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jmp		loc_xxxxx  
				tooltipAndButtonProc6ReturnAddress1 = Injector::GetBranchDestination(address + 0xD).as_int();
				//  mov     rbx, [rbp+440h+arg_48]
				tooltipAndButtonProc6ReturnAddress2 = address + 0x2A;

				Injector::MakeJMP(address, tooltipAndButtonProc6, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc6Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc6Injector = true;
		}

		return e;
	}
	
	DllError Init(RunOptions options) {
		DllError result = {};

		result |= tooltipAndButtonProc1Injector(options);
		result |= tooltipAndButtonProc2Injector(options);
		result |= tooltipAndButtonProc3Injector(options);
		result |= tooltipAndButtonProc4Injector(options);
		result |= tooltipAndButtonProc5Injector(options);
		result |= tooltipAndButtonProc6Injector(options);

		return result;
	}
}