#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "IT.h"
#include "LT.h"
#include "Log.h"
#include <vector>
#define BEFORE_DATA_SECTIONS_ENTRY ".586\n.model flat, stdcall\nincludelib userlib.lib\nincludelib kernel32.lib\nincludelib libucrt.lib"
#define CSMAXSIZE 1000


namespace CG
{

	enum INSTRUCTIONTYPE
	{
		PUSH = 0,
		FUNC = 2,
		RET = 3,
		PRNT = 4,
		ADD = 5,
		ADDSTR = 6,
		DIFF = 7,
		DIV = 9,
		MUL = 10,
		SEM = 11,
		PARM = 12,
		CALL = 13,
		ENDP = 14,
		FOR = 15,
		FOR_1 = 16,
		MOV = 17,
		LESS = 18,
		MORE = 19,
		NOTEQUAL = 20,
		EQUAL = 21,
		BLEFT = 22,
		BRIGHT = 23,
		CONV = 24
	};

	struct ConstSegment
	{
		char** Data;
		int size;
		int maxSize;
		ConstSegment(int _size)
		{
			size = 0;
			maxSize = _size + 4;
			Data = new char*[maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			strcpy_s(Data[size++], TI_STR_MAXSIZE,BEFORE_DATA_SECTIONS_ENTRY); 
			strcpy_s(Data[size++], TI_STR_MAXSIZE,"\n\nExitProcess PROTO : DWORD\nstrl PROTO : DWORD\nrandom PROTO : DWORD\noutstr PROTO : DWORD\noutbool PROTO : DWORD\noutchar PROTO : DWORD\noutuint PROTO : DWORD\noutint PROTO : SDWORD\nstrcon PROTO : DWORD, : DWORD ");
			strcpy_s(Data[size++], TI_STR_MAXSIZE, "\nintToUint PROTO : SDWORD\nuintToInt PROTO : DWORD");
			strcpy_s(Data[size++], TI_STR_MAXSIZE, "\n.stack 4096\n.const");
			strcpy_s(Data[size++], TI_STR_MAXSIZE, "\n\toverflow db 'ERROR: VARIABLE OVERFLOW', 0 \n\tnull_division db 'ERROR: DIVISION BY ZERO', 0");

		}
	};
	struct DataSegment
	{
		char** Data;
		int size;
		int maxSize;
		DataSegment(int _size)
		{
			size = 0;
			maxSize = _size + 1;
			Data = new char*[maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			strcpy_s(Data[size++], TI_STR_MAXSIZE, "\n.data");
		}
	};
	struct CodeSegment
	{
		char** Data;
		int size;
		int maxSize;
		void add(std::string str);
		CodeSegment()
		{
			size = 0;
			maxSize = CSMAXSIZE;
			Data = new char*[maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			strcpy_s(Data[size++], TI_STR_MAXSIZE,"\n.code");
		}
	};



	void add(IT::IdTable& idTable, ConstSegment& cnst);
	void add(IT::IdTable& idTable, DataSegment& dataseg);
	void generateExpression(std::vector<LT::Entry>& tempEntries, CodeSegment& CS, int idxTI, IT::IdTable idTable, IT::IDDATATYPE type = IT::INT);
	void	CodeSegmentGeneration(CodeSegment& CS, LT::LexTable l, IT::IdTable& idTable);
	std::string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable idTable, IT::IDDATATYPE type = IT::INT, std::string fucn_name = "");
	void endOfFucntion(CodeSegment& CS);
	void startGeneration(wchar_t* file, ConstSegment& CnstS, DataSegment& DS, CodeSegment& CS);

	void print(Log::LOG log, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg);
}