#pragma once
#include <windows.h>
#include <vector>
namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t findDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	uintptr_t AdjustPointer(uintptr_t ptr, int offset);
}