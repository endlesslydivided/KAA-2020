#pragma once
#include "LT.h"
#include "IT.h"
#include "PN.h"
#include "IN.h"
#include <stdlib.h>

#define BEGIN_SYMBOL '|'

namespace PN
{
	bool Stack::push(LT::Entry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	bool Stack::push(PN::lexEntry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	lexEntry* Stack::pop()
	{
		if (this->current_size != 0)
		{

			lexEntry temp(*this->head);
			delete this->head;
			this->head = temp.next;
			this->current_size--;

			return &lexEntry(temp);
		}
		else
			return 0;
	}

	char Stack::Last_element(IT::IdTable idTable)
	{
		if (this->head->lexema == 'v')
			return idTable.table[this->head->idxTI].value.operation;
		return this->head->lexema;
	}


	bool PolishNotation(int lt_position, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		PN::Stack* literals = new PN::Stack;
		PN::Stack* operators = new PN::Stack;

		operators->push({ BEGIN_SYMBOL, -1, -1 });

		bool flag = true;
		bool is_complete = false;
		int function_id_position = 0;
		LT::Entry temp;
		In::IN in_ex;

		for (int i = lt_position; flag;)
		{
			temp = lexTable.GetEntry(i);

			if (idTable.GetEntry(temp.idxTI).idtype == IT::IDTYPE::F)
			{
				LT::Entry temp_1;
				temp_1 = lexTable.GetEntry(i);
				temp_1.lexema = '\@';
				char buffer[ID_MAXSIZE];
				int parm_quantity = 0;
				i++;
				for (; lexTable.GetEntry(i).lexema != ')'&& lexTable.GetEntry(i).lexema != ';'; i++)
				{

					if (in_ex.code[lexTable.GetEntry(i).lexema] != in_ex.D)
					{
						parm_quantity++;
						temp = lexTable.GetEntry(i);
						literals->push(temp);
					}
				}
				if (lexTable.GetEntry(i).lexema == ';' && parm_quantity == 0)
				{
					break;
				}
				_itoa_s(parm_quantity, buffer, 10);
				literals->push(temp_1);
				literals->push({ buffer[0],temp_1.sn,temp_1.idxTI });
				i++;
				continue;
			}
			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL)
			{
				literals->push(temp);
				i++;
				continue;
			}
			switch (operators->Last_element(idTable))
			{

			
			case BEGIN_SYMBOL:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH||
						idTable.table[temp.idxTI].value.operation == BINARY_LEFT||
						idTable.table[temp.idxTI].value.operation == BINARY_RIGHT)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexema == LEX_RIGHTTHESIS) { flag = false; }
				if (temp.lexema == LEX_SEMICOLON ||
					temp.lexema == LEX_EQUALITY_SIGN ||
					temp.lexema == LEX_LESS_SIGN ||
					temp.lexema == LEX_MORE_SIGN ||
					temp.lexema == LEX_NOTEQUALITY_SIGN) { is_complete = true; flag = false; }
				break;
			}
			case PLUS:
			case BINARY_LEFT:
			case BINARY_RIGHT:
			case MINUS:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == BINARY_LEFT ||
						idTable.table[temp.idxTI].value.operation == BINARY_RIGHT)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTTHESIS ||
						temp.lexema == LEX_SEMICOLON ||
						temp.lexema == LEX_EQUALITY_SIGN ||
						temp.lexema == LEX_LESS_SIGN ||
						temp.lexema == LEX_MORE_SIGN ||
						temp.lexema == LEX_NOTEQUALITY_SIGN)
					{
						literals->push(*operators->pop());
						break;
					}
				}

				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
			}

			case STAR:
			case DIRSLASH:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH ||
						idTable.table[temp.idxTI].value.operation == BINARY_LEFT ||
						idTable.table[temp.idxTI].value.operation == BINARY_RIGHT)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_RIGHTTHESIS ||
						temp.lexema == LEX_SEMICOLON ||
						temp.lexema == LEX_EQUALITY_SIGN ||
						temp.lexema == LEX_LESS_SIGN ||
						temp.lexema == LEX_MORE_SIGN ||
						temp.lexema == LEX_NOTEQUALITY_SIGN)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				if (temp.lexema == LEX_LEFTTHESIS)
				{
					operators->push(temp);
					i++;
					break;
				}
			}
			case LEX_LEFTTHESIS:
			{
				if (temp.lexema == LEX_SEMICOLON || 
					temp.lexema == LEX_EQUALITY_SIGN ||
					temp.lexema == LEX_LESS_SIGN ||
					temp.lexema == LEX_MORE_SIGN ||
					temp.lexema == LEX_NOTEQUALITY_SIGN)
					flag = false;

				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH ||
						idTable.table[temp.idxTI].value.operation == BINARY_LEFT ||
						idTable.table[temp.idxTI].value.operation == BINARY_RIGHT)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexema == LEX_RIGHTTHESIS)
				{
					operators->pop();
					i++;
					break;
				}
			}
			default:
				flag = false;
			}
		}

		if (is_complete)
		{
			PN::lexEntry* temp;
			int count = literals->getCount();
			LT::Entry* temp_array = new LT::Entry[count];

			for (int i = count - 1; i >= 0; i--)
			{
				temp = literals->pop();
				if (temp)
				{
					temp_array[i] = *temp;
				}
			}

			for (int i = lt_position, j = 0; lexTable.table[i].lexema != LEX_SEMICOLON &&
				lexTable.table[i].lexema != LEX_EQUALITY_SIGN &&
				lexTable.table[i].lexema != LEX_LESS_SIGN &&
				lexTable.table[i].lexema != LEX_MORE_SIGN &&
				lexTable.table[i].lexema != LEX_NOTEQUALITY_SIGN; i++)
			{
				if ((i - count) < lt_position)
					lexTable.table[i] = temp_array[j++];
				else
					lexTable.table[i] = { '#', lexTable.table[i].sn, -1 };
			}

			delete[] temp_array;
			delete literals;
			delete operators;
			return true;
		}
		else
		{
			delete literals;
			delete operators;
			return false;
		}
	}
}

