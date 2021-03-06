#pragma once
#include <Windows.h>

#define DO_ONCE(todo) do { \
   static std::once_flag _flag ;\
   std::call_once(_flag, todo); \
} while (false)

#define STR_MERGE_IMPL(x, y)				x##y
#define STR_MERGE(x,y)						STR_MERGE_IMPL(x,y)
#define MAKE_PAD(size)						BYTE STR_MERGE(pad_, __COUNTER__) [ size ]

#define DEFINE_MEMBER_0(x, y)				x
#define DEFINE_MEMBER_N(x,offset)			struct { MAKE_PAD(offset); x; }

#define OBJ_MINION  1
#define OBJ_HERO    2
#define OBJ_MISSILE 3

extern DWORD g_BaseAddr;

template< typename Function > Function CallVirtual(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	return (Function)(dwAddress);
}

inline char* GetStr(DWORD offset) {
	if (*(int*)(offset + 0x10) > 15)
		return (char*)(*(DWORD*)offset);
	else
		return (char*)offset;
}

inline int createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

char* stristr(const char* str1, const char* str2);

float calculate2dDistance(float x1, float y1, float x2, float y2);

DWORD FindD3D9VTable(DWORD Len);

DWORD GetD3D9VTableFunction(int VTableIndex);