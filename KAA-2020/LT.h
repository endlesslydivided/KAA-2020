#pragma once
#pragma once

#include "IT.h"

#define LEXEMA_FIXSIZE  1			//������������� ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX	-1	// ��� �������� ������� ���������������				
#define	LEX_INTEGER		't'			// ������� ��� int
#define	LEX_UINTEGER	't'			// ������� ��� uint
#define	LEX_BOOL		't'			// ������� ��� bool
#define	LEX_STRING		't'			// ������� ��� string
#define	LEX_CHAR		't'			// ������� ��� char

#define	LEX_FOR			'c'			// ������� ��� for

#define	LEX_RANDOM		'i'			// ������� ��� random
#define LEX_MAIN		'i'			// ������� ��� main
#define LEX_STRLEN		'i'			// ������� ��� strlen

#define	LEX_ID			'i'			// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_OUT			'o'			// ������� ��� out
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTBRACE	'{'			// ������� ��� {
#define	LEX_RIGHTBRACE	'}'			// ������� ��� }
#define	LEX_LEFTSB		'['			// ������� ��� [
#define	LEX_RIGHTSB		']'			// ������� ��� ]
#define	LEX_LEFTTHESIS	'('			// ������� ��� (
#define	LEX_RIGHTTHESIS	')'			// ������� ��� )
#define	LEX_PLUS		'v'			// ������� ��� +
#define	LEX_MINUS		'v'			// ������� ��� -
#define	LEX_STAR		'v'			// ������� ��� *
#define	LEX_DIRSLASH	'v'			// ������� ��� /
#define	LEX_EQUAL_SIGN	'='			// ������� ��� = 
#define	LEX_NOTEQUALITY_SIGN	'!'			// ������� ��� !=
#define	LEX_EQUALITY_SIGN	'~'			// ������� ��� ==
#define	LEX_LESS_SIGN	'<'			// ������� ��� =
#define	LEX_MORE_SIGN	'>'			// ������� ��� =


#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'

#define PARM_LEX L".lex.txt" 

namespace LT								// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema;							// �������
		int sn;									// ����� ������ � �������� ������
		int idxTI;								// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable								// �������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size;								// ������� ������ ������� ������ < maxsize
		Entry* table;							// ������ ����� ������� ������


		Entry GetEntry(								// �������� ������ ������� ������
			int n									// ����� ���������� ������
		);

		void PrintLexTable(const wchar_t* in);		// ����� ������ � ����	
		void PrintLexTable(const wchar_t* in, const wchar_t* name);
		LexTable();

		void PrintLexTableControle(const wchar_t* in, const wchar_t* name, IT::IdTable it);
	};

	void Add(									// �������� ������ � ������� ������
		LexTable& lextable,						// ��������� ������� ������
		Entry entry								// ������ ������� ������
	);


	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
};