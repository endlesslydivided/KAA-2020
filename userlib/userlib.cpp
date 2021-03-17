#pragma once
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "userlib.h"

#pragma warning(disable: 4996)

extern "C"
{
	static int N_SYSTEM = 0;
	char* _stdcall strcon(char* str1, char* str2)
	{
		char* buf  = (char*)malloc(255);
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		if (!str1 || !str2)
		{
			std::cout << "ERROR: Null string in strcon function!!!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		int size = 0;
		for (; str2[size] != '\0'; size++)
			buf[size] = str2[size];
		for (int i = 0; str1[i] != '\0'; size++,i++)
			buf[size] = str1[i];
		buf[size] = '\0';
		return  buf;
	}
	int _stdcall strl(char* str1)
	{
		int length = strlen(str1);
		return  length;
	}
	unsigned int _stdcall random(unsigned int number)
	{
		srand(time(0));
		return (rand() % number) ;
	}
	void _stdcall outstr(char* s)
	{
		if (s != nullptr)
		{
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			char* buf = (char*)malloc(255);
			int bufLength = 0;
			for (int iter = 0; s[iter] != '\0'; iter++)
			{
				if (s[iter] == '|')
				{
					buf[bufLength++] = s[iter++];
					buf[bufLength++] = s[iter++];
					buf[bufLength] = '\0';
				}
				if (strcmp(buf, "|e") == 0)
				{
					std::cout << std::endl; iter--;
				}
				else if (strcmp(buf, "|t") == 0)
				{
					std::cout << "\t"; iter--;
				}
				else if (strcmp(buf, "|b") == 0)
				{
					N_SYSTEM = 2; iter--;
				}
				else if (strcmp(buf, "|h") == 0)
				{
					N_SYSTEM = 16; iter--;
				}
				else if (strcmp(buf, "|o") == 0)
				{
					N_SYSTEM = 8; iter--;
				}
				else if (strcmp(buf, "|d") == 0)
				{
					N_SYSTEM = 10; iter--;
				}
				else if (strcmp(buf, "|f") == 0)
				{
					std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
					iter--;
				}
				else if (strcmp(buf, "||") == 0)
				{
					std::cout << "|"; iter--;
				}
				else if(bufLength != 0)
				{
					std::cout << buf;iter--;
				}
				else
				{
					std::cout << s[iter];
				}		
				bufLength = 0;
				buf[bufLength] = '\0';
			}
		
		}
		else
			std::cout << "Empty line!";
	}
	void _stdcall outint(int i)
	{
		switch (N_SYSTEM)
		{
		case 2:
		{
			int multiple = 0;
			for (; multiple < 8; multiple++)
			{
				if (pow(8, multiple) > abs(i))break;;
			}
			for (int iter = sizeof(i) * multiple - 1; iter >= 0; --iter)
			{
				std::cout << (int)((i >> iter) & 1);
			}
			break;
		}
		case 8:
		{
			std::cout << std::oct << i;
			break;
		}
		case 10:
		{
			std::cout << std::dec << i;
			break;
		}
		case 16:
		{
			std::cout << "0x" << std::hex << i;
			break;
		}
		default:std::cout << i; break;
		}
	}
	void _stdcall outbool(bool* i)
	{
		if(*i == 0)
		std::cout << "false";
		else
		std::cout << "true";
	}
	void _stdcall outchar(char* i)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		std::cout << *i;
	}
	void _stdcall outuint(unsigned int i)
	{
		switch (N_SYSTEM)
		{
		case 2:
		{
			int multiple = 0;
			for (; multiple < 8; multiple++)
			{
				if (pow(8, multiple) > i)break;
			}
			for (int iter = sizeof(i) * multiple - 1; iter >= 0; --iter)
			{
				std::cout << ((i >> iter) & 1);
			}
			break;
		}
		case 8:
		{
			std::cout << std::oct << i;
			break;
		}
		case 10:
		{
			std::cout << std::dec << i;
			break;
		}
		case 16:
		{
			std::cout << "0x" << std::hex << i;
			break;
		}
		default:std::cout << i; break;
		}
	}
	unsigned int _stdcall intToUint(int number)
	{
		return (unsigned int) number;
	}
	int _stdcall uintToInt(unsigned int number)
	{
		return (int)number;
	}
}