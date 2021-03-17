#pragma once

extern "C"
{
	void _stdcall outstr(char*);
	unsigned int _stdcall intToUint(int);
	int _stdcall uintToInt(unsigned int);
	void _stdcall outchar(char*);
	void _stdcall outuint(unsigned int);
	void _stdcall outbool(bool*);
	void _stdcall outint(int i);
	int _stdcall strl(char*);
	unsigned int _stdcall random(unsigned int);
	char* _stdcall strcon(char* str1, char* str2);
}