#pragma once
#include <iostream>
namespace FST
{
	struct RELATION
	{
		char symbol; // ������ ��������
		short nnode; // ����� ������� �������
		RELATION(
			char c = 0x00,
			short ns = NULL
		);
	};

	struct NODE
	{
		short n_relation; // ��-�� ����������� ����
		RELATION* relations; // ����
		NODE();
		NODE(short n,
			RELATION rel, ...
		);
	};

	struct FST
	{
		const char* string; //�������
		short position; //������� � �������
		short nstates; //���-�� ���������
		NODE* nodes; //���� ��������
		short* rstates; //��������� ���������
		FST(const char* s,
			short ns,
			NODE n, ...
		);
	};

	bool step(FST& fst, short* rstates); // ������ ������ �������
	bool execute(FST& fsts);  //������������ �������
}

#define FUNCTION(string) string, 9,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE(1, FST::RELATION('i', 6)),  \
			FST::NODE(1, FST::RELATION('o', 7)),  \
			FST::NODE(1, FST::RELATION('n', 8)),  \
			FST::NODE()			

#define INTEGER(string) string, 4,			  \
			FST::NODE(1, FST::RELATION('i', 1)),  \
			FST::NODE(1, FST::RELATION('n', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE()		

#define FOR(string) string, 4,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('o', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE()		

#define UINTEGER(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('u', 1)),  \
			FST::NODE(1, FST::RELATION('i', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('t', 4)),  \
			FST::NODE()		

#define CHAR(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('c', 1)),  \
			FST::NODE(1, FST::RELATION('h', 2)),  \
			FST::NODE(1, FST::RELATION('a', 3)),  \
			FST::NODE(1, FST::RELATION('r', 4)),  \
			FST::NODE()	
#define MAIN(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('m', 1)),  \
			FST::NODE(1, FST::RELATION('a', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('n', 4)),  \
			FST::NODE()	
#define STRING(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('s', 1)),  \
			FST::NODE(1, FST::RELATION('t', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('i', 4)),  \
			FST::NODE(1, FST::RELATION('n', 5)),  \
			FST::NODE(1, FST::RELATION('g', 6)),  \
			FST::NODE()		

#define RANDOM(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('r', 1)),  \
			FST::NODE(1, FST::RELATION('a', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('d', 4)),  \
			FST::NODE(1, FST::RELATION('o', 5)),  \
			FST::NODE(1, FST::RELATION('m', 6)),  \
			FST::NODE()	

#define RETURN(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('r', 1)),  \
			FST::NODE(1, FST::RELATION('e', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE(1, FST::RELATION('u', 4)),  \
			FST::NODE(1, FST::RELATION('r', 5)),  \
			FST::NODE(1, FST::RELATION('n', 6)),  \
			FST::NODE()	

#define BOOL(string) string, 5,				  \
			FST::NODE(1, FST::RELATION('b', 1)),  \
			FST::NODE(1, FST::RELATION('o', 2)),  \
			FST::NODE(1, FST::RELATION('o', 3)),  \
			FST::NODE(1, FST::RELATION('l', 4)),  \
			FST::NODE()	

#define OUT(string) string, 4,				  \
			FST::NODE(1, FST::RELATION('o', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE()	

#define IMPORT(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('i', 1)),  \
			FST::NODE(1, FST::RELATION('m', 2)),  \
			FST::NODE(1, FST::RELATION('p', 3)),  \
			FST::NODE(1, FST::RELATION('o', 4)),  \
			FST::NODE(1, FST::RELATION('r', 5)),  \
			FST::NODE(1, FST::RELATION('t', 6)),  \
			FST::NODE()	

#define FALSE(string) string, 6,				  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('a', 2)),  \
			FST::NODE(1, FST::RELATION('l', 3)),  \
			FST::NODE(1, FST::RELATION('s', 4)),  \
			FST::NODE(1, FST::RELATION('e', 5)),  \
			FST::NODE()	

#define TRUE(string) string, 5,				  \
			FST::NODE(1, FST::RELATION('t', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('u', 3)),  \
			FST::NODE(1, FST::RELATION('e', 4)),  \
			FST::NODE()	

#define IDENTIFICATOR(string) string, 1,	\
			FST::NODE(63,	FST::RELATION('a', 0),	FST::RELATION('b', 0),	\
							FST::RELATION('c', 0),	FST::RELATION('d', 0),	\
							FST::RELATION('e', 0),	FST::RELATION('f', 0),	\
							FST::RELATION('g', 0),	FST::RELATION('h', 0),	\
							FST::RELATION('i', 0),	FST::RELATION('j', 0),	\
							FST::RELATION('k', 0),	FST::RELATION('l', 0),	\
							FST::RELATION('m', 0),	FST::RELATION('n', 0),	\
							FST::RELATION('o', 0),	FST::RELATION('p', 0),	\
							FST::RELATION('q', 0),	FST::RELATION('r', 0),	\
							FST::RELATION('s', 0),	FST::RELATION('t', 0),	\
							FST::RELATION('u', 0),	FST::RELATION('v', 0),	\
							FST::RELATION('w', 0),	FST::RELATION('x', 0),	\
							FST::RELATION('y', 0),	FST::RELATION('z', 0),	\
							FST::RELATION('A', 0),	FST::RELATION('B', 0),	\
							FST::RELATION('C', 0),	FST::RELATION('D', 0),	\
							FST::RELATION('E', 0),	FST::RELATION('F', 0),	\
							FST::RELATION('G', 0),	FST::RELATION('H', 0),	\
							FST::RELATION('I', 0),	FST::RELATION('J', 0),	\
							FST::RELATION('K', 0),	FST::RELATION('L', 0),	\
							FST::RELATION('M', 0),	FST::RELATION('N', 0),	\
							FST::RELATION('O', 0),	FST::RELATION('P', 0),	\
							FST::RELATION('Q', 0),	FST::RELATION('R', 0),	\
							FST::RELATION('S', 0),	FST::RELATION('T', 0),	\
							FST::RELATION('U', 0),	FST::RELATION('V', 0),	\
							FST::RELATION('W', 0),	FST::RELATION('X', 0),	\
							FST::RELATION('Y', 0),	FST::RELATION('Z', 0),	\
							FST::RELATION('0', 0),	FST::RELATION('1', 0),	\
							FST::RELATION('2', 0),	FST::RELATION('3', 0),	\
							FST::RELATION('4', 0),	FST::RELATION('5', 0),	\
							FST::RELATION('6', 0),	FST::RELATION('7', 0),	\
							FST::RELATION('8', 0),	FST::RELATION('9', 0),	\
							FST::RELATION('_', 0)),	\
			FST::NODE()			

#define STRING_LITERAL(string) string, 3,	\
	FST::NODE(1, FST::RELATION('\"', 1)),	\
	FST::NODE(143,	FST::RELATION(' ', 1),	\
					FST::RELATION('a', 1), FST::RELATION('b', 1),	FST::RELATION('c', 1), FST::RELATION('d', 1),	\
					FST::RELATION('e', 1), FST::RELATION('f', 1),	FST::RELATION('g', 1), FST::RELATION('h', 1),	\
					FST::RELATION('i', 1), FST::RELATION('j', 1),	FST::RELATION('k', 1), FST::RELATION('l', 1),	\
					FST::RELATION('m', 1), FST::RELATION('n', 1),	FST::RELATION('o', 1), FST::RELATION('p', 1),	\
					FST::RELATION('q', 1), FST::RELATION('r', 1),	FST::RELATION('s', 1), FST::RELATION('t', 1),	\
					FST::RELATION('u', 1), FST::RELATION('v', 1),	FST::RELATION('w', 1), FST::RELATION('x', 1),	\
					FST::RELATION('y', 1), FST::RELATION('z', 1),	FST::RELATION('A', 1), FST::RELATION('B', 1),	\
					FST::RELATION('C', 1), FST::RELATION('D', 1),	FST::RELATION('E', 1), FST::RELATION('F', 1),	\
					FST::RELATION('G', 1), FST::RELATION('H', 1),	FST::RELATION('I', 1), FST::RELATION('J', 1),	\
					FST::RELATION('K', 1), FST::RELATION('L', 1),	FST::RELATION('M', 1), FST::RELATION('N', 1),	\
					FST::RELATION('O', 1), FST::RELATION('P', 1),	FST::RELATION('Q', 1), FST::RELATION('R', 1),	\
					FST::RELATION('S', 1), FST::RELATION('T', 1),	FST::RELATION('U', 1), FST::RELATION('V', 1),	\
					FST::RELATION('W', 1), FST::RELATION('X', 1),	FST::RELATION('Y', 1), FST::RELATION('Z', 1),	\
					FST::RELATION('0', 1), FST::RELATION('1', 1),	FST::RELATION('2', 1), FST::RELATION('3', 1),	\
					FST::RELATION('4', 1), FST::RELATION('5', 1),	FST::RELATION('6', 1), FST::RELATION('7', 1),	\
					FST::RELATION('8', 1), FST::RELATION('9', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('=', 1), FST::RELATION('+', 1),	FST::RELATION('-', 1), FST::RELATION('*', 1),	\
					FST::RELATION('/', 1), FST::RELATION('(', 1),	FST::RELATION(')', 1), FST::RELATION('{', 1),	\
					FST::RELATION('}', 1), FST::RELATION(';', 1),	FST::RELATION(',', 1), FST::RELATION('?', 1),	\
					FST::RELATION('!', 1), FST::RELATION('\"', 2)),\
	FST::NODE()

#define CHAR_LITERAL(string) string, 3,	\
	FST::NODE(1, FST::RELATION('\'', 1)),	\
	FST::NODE(143,	FST::RELATION(' ', 1),FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),	\
					FST::RELATION('d', 1),FST::RELATION('e', 1),FST::RELATION('f', 1),FST::RELATION('g', 1),	\
					FST::RELATION('h', 1),FST::RELATION('i', 1),FST::RELATION('j', 1),FST::RELATION('k', 1),	\
					FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),FST::RELATION('o', 1),	\
					FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),	\
					FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),	\
					FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1),FST::RELATION('0', 1),	\
					FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),	\
					FST::RELATION('5', 1),FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),	\
					FST::RELATION('9', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),FST::RELATION('�', 1),FST::RELATION('=', 1),FST::RELATION('+', 1),	\
					FST::RELATION('-', 1),FST::RELATION('*', 1),FST::RELATION('/', 1),FST::RELATION('(', 1),	\
					FST::RELATION(')', 1),FST::RELATION('{', 1),FST::RELATION('}', 1),FST::RELATION(';', 1),	\
					FST::RELATION(',', 1),FST::RELATION('?', 1),FST::RELATION('!', 1),FST::RELATION('A', 1), \
					FST::RELATION('B', 1),	\
					FST::RELATION('C', 1), FST::RELATION('D', 1),	FST::RELATION('E', 1), FST::RELATION('F', 1),	\
					FST::RELATION('G', 1), FST::RELATION('H', 1),	FST::RELATION('I', 1), FST::RELATION('J', 1),	\
					FST::RELATION('K', 1), FST::RELATION('L', 1),	FST::RELATION('M', 1), FST::RELATION('N', 1),	\
					FST::RELATION('O', 1), FST::RELATION('P', 1),	FST::RELATION('Q', 1), FST::RELATION('R', 1),	\
					FST::RELATION('S', 1), FST::RELATION('T', 1),	FST::RELATION('U', 1), FST::RELATION('V', 1),	\
					FST::RELATION('W', 1), FST::RELATION('X', 1),	FST::RELATION('Y', 1), FST::RELATION('Z', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
					FST::RELATION('�', 1), FST::RELATION('�', 1),	FST::RELATION('�', 1), FST::RELATION('�', 1),	\
FST::RELATION('\'', 2)),\
	FST::NODE()

#define INTEGER_LITERAL(string) string, 1,	\
	FST::NODE(10,	FST::RELATION('0', 0),	\
					FST::RELATION('1', 0),	\
					FST::RELATION('2', 0),	\
					FST::RELATION('3', 0),	\
					FST::RELATION('4', 0),	\
					FST::RELATION('5', 0),	\
					FST::RELATION('6', 0),	\
					FST::RELATION('7', 0),	\
					FST::RELATION('8', 0),	\
					FST::RELATION('9', 0)),	\
	FST::NODE()
