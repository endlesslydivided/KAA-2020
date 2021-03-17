#pragma once
#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include <iostream>
#include <fstream>
#include "LT.h"
#include "IT.h"
#include "FST.h"

#define MAX_FILE_NAME_SIZE 256
#define IMPORT_LEX_SIZE 6
using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in_ex;
		in_ex.size = 0;
		in_ex.lines = 1;
		in_ex.ignor = 0;
		char* line = new char[IN_MAX_LEN_TEXT];;
		int cols = 0;

		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream fin(infile);
		if (fin.fail()) throw ERROR_THROW(110);

		while (in_ex.size < IN_MAX_LEN_TEXT)
		{
			char k; fin.get(k);
			unsigned char uc = k;

			if (fin.eof())
			{
				text[in_ex.size] = STRING_END_ZERO;
				break;
			}
			if (in_ex.code[uc] == in_ex.T || in_ex.code[uc] == in_ex.D || in_ex.code[uc] == in_ex.A || in_ex.code[uc] == in_ex.N)
			{

				text[in_ex.size] = uc;
				in_ex.size++;
				cols++;
			}
			else if (in_ex.code[uc] == in_ex.I)
			{
				in_ex.ignor++;
			}
			else if (in_ex.code[uc] == in_ex.F)
			{
				throw ERROR_THROW_IN(111, in_ex.lines, cols);
			}
			else
			{
				text[in_ex.size] = in_ex.code[uc];
				in_ex.size++;
				cols++;
			}
			if (uc == IN_CODE_ENDL)
			{
				in_ex.lines++;
				cols = 0;
			}
		}
		in_ex.text = text;
		return in_ex;
	}


	IN ImportLibraries(const In::IN& source)
	{
		char* temp = new char[MAX_FILE_NAME_SIZE + 2];
		int str_number = 1;
		int str_position = 1;
		char* file_name = new char[MAX_FILE_NAME_SIZE];
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];
		bool ifimpfile = false;
		In::IN in_ex;
		in_ex.size = 0;
		in_ex.lines = 0;
		in_ex.ignor = 0;
		in_ex.text = text;

		for (int i = 0, j = 0; i < source.size; i++)
		{
			ifimpfile = false;
			if (source.text[i] == 'i')
			{
				for (int l = 0; l < IMPORT_LEX_SIZE; l++)
				{
					temp[j++] = source.text[i++];
				}
				temp[j] = '\0';
				FST::FST* _import = new FST::FST(IMPORT(temp));

				bool import_found = false;
				if (import_found = FST::execute(*_import))
				{
					delete _import;
					ifimpfile = true;
					int delete_import = i - 1;
					for (int g = 0; g < IMPORT_LEX_SIZE; g++)
					{
						source.text[delete_import--] = ' ';
					}
					temp[0] = '\0'; j = 0;
					for (; source.text[i] != '\"' && source.text[i] != '<' && i < source.size && source.text[i] != '\n';)
					{
						i++;
					}
					for (; source.text[i] != '\"' && source.text[i] != '>' && i < source.size && source.text[i] != '\n';)
					{
						temp[j++] = source.text[i++];
					}
					temp[j] = source.text[i];
					int k = 0;
					for (int j = 1; temp[j] != '\"' && temp[j] != '>'; k++, j++)
					{
						file_name[k] = temp[j];
					}
					file_name[k] = '\0';
				}
				else
				{
					delete _import;
					continue;
				}
				if (temp[0] == '\"')
				{
					in_ex.text = check_text(file_name, in_ex);
				}
				if (temp[0] == '<')
				{
					char file_patch[255] = { "Library\\" };
					strcat_s(file_patch, sizeof(file_patch), file_name);
					in_ex.text = check_text(file_patch, in_ex);
				}
				if (import_found)
				{
					int delete_file_name = i;
					for (int g = 0; g < j + 1; g++)
					{
						source.text[delete_file_name--] = ' ';
					}
				}

			}
			temp[0] = '\0';
			j = 0;
		}

			for (int i = 0; i < source.size; i++)
			{
				in_ex.text[in_ex.size] = source.text[i];
				in_ex.size++;
			}
		in_ex.ignor += source.ignor;
		in_ex.lines += source.lines;
		return in_ex;

	}

	unsigned char* check_text(char* file_name, In::IN& in_ex)
	{
		int cols = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream fin(file_name);
		if (!fin.is_open()) 
			throw ERROR_THROW(110);

		while (in_ex.size < IN_MAX_LEN_TEXT)
		{
			char k; fin.get(k);
			unsigned char uc = k;

			if (fin.eof())
			{
				text[in_ex.size] = STRING_END_ZERO;
				break;
			}
			if (in_ex.code[uc] == in_ex.T || in_ex.code[uc] == in_ex.D || in_ex.code[uc] == in_ex.A || in_ex.code[uc] == in_ex.N)
			{

				text[in_ex.size] = uc;
				in_ex.size++;
				cols++;
			}
			else if (in_ex.code[uc] == in_ex.I)
			{
				in_ex.ignor++;
			}
			else if (in_ex.code[uc] == in_ex.F)
			{
				throw ERROR_THROW_IN(111, in_ex.lines, cols);
			}
			else
			{
				text[in_ex.size] = in_ex.code[uc];
				in_ex.size++;
				cols++;
			}
			if (uc == IN_CODE_ENDL)
			{
				in_ex.lines++;
				cols = 0;
			}
		}
		return text;
	}
}