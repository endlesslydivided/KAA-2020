#pragma once

#include "In.h"
#include "Error.h"
#include "tokens-division.h"
#include "LT.h"
#include "FST.h"
#include "IT.h"


void token_divivison(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* temp = new char[token_size] {};
	int str_number = 1;
	int str_position = 1;
	bool sign = false;
	In::IN in_ex;

	for (int i = 0, j = 0; i < source.size; i++)
	{
		if ((in_ex.code[(source.text[i])] != in_ex.D && in_ex.code[(source.text[i])] != in_ex.A && !sign) ||
			( in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i+1])] == in_ex.A)||
			((source.text[i]) == '-' && in_ex.code[(source.text[i + 1])] == in_ex.N && in_ex.code[(source.text[i - 1])] != in_ex.N))
		{
			temp[j++] = source.text[i];
			str_position++;
			if ((in_ex.code[lexTable.table[lexTable.size - 1].lexema] == in_ex.A || in_ex.code[lexTable.table[lexTable.size - 1].lexema] == in_ex.D) &&
				((temp[j - 1]) == '-' && in_ex.code[(source.text[i + 1])] == in_ex.N))
			{
				i++;
				do
				{
					temp[j++] = source.text[i];
					str_position++;
					i++;
				} while ((in_ex.code[(source.text[i])] != in_ex.D ) ||
					(in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i + 1])] == in_ex.A));
				i--;
			}
			if (in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i + 1])] == in_ex.A)
			{
				sign = true;
				i++;
				temp[j++] = source.text[i];
			}
			continue;
		}
		else
		{
			if (j != 0)
			{
				i--;
				temp[j] = '\0';				
				if (token_analize(temp, str_number, lexTable, idTable))
				{
					temp[0] = '\0'; j = 0;
					continue;
				}
				else
					throw ERROR_THROW_IN(123, str_number, str_position);
			}
			else
			{
				if (source.text[i] == '\"')
				{
					temp[j++] = source.text[i++];

					for (int c = 0; source.text[i] != '\"'; c++)
					{
						if (c <= TI_STR_MAXSIZE)
						{
							temp[j++] = source.text[i++];
						}
						else
							throw ERROR_THROW_IN(127, str_number, str_position);
					}

					if (source.text[i] == '\"')
					{
						temp[j++] = source.text[i];
						temp[j] = '\0';
						if (token_analize(temp, str_number, lexTable, idTable))
						{
							temp[0] = '\0'; j = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(123, str_number, str_position);
					}
					else
						throw ERROR_THROW_IN(124, str_number, str_position);
				}
				if (source.text[i] == '\'')
			{
				temp[j++] = source.text[i++];
				for (int c = 0; source.text[i] != '\''; c++)
				{
					if (c <= TI_CHAR_MAXSIZE)
					{
						temp[j++] = source.text[i++];
					}
					else
						throw ERROR_THROW_IN(130, str_number, str_position);
				}

				if (source.text[i] == '\'')
				{
					temp[j++] = source.text[i];
					temp[j] = '\0';
					if (token_analize(temp, str_number, lexTable, idTable))
					{
						temp[0] = '\0'; j = 0;
						continue;
					}
					else
						throw ERROR_THROW_IN(123, str_number, str_position);
				}
				else
					throw ERROR_THROW_IN(124, str_number, str_position);
			}
				if (source.text[i] != '\n')
				{
					if (source.text[i] == ' ' || source.text[i] == '\t')
					{
						str_position++;
						continue;
					}

					temp[0] = source.text[i]; temp[1] = '\0';
					if (token_analize(temp, str_number, lexTable, idTable))
						str_position++;
					else
						throw ERROR_THROW_IN(123, str_number, str_position);

					temp[0] = '/0'; j = 0;
				}
			}
			sign = false;
		}
		if (source.text[i] == '\n')
		{
			str_number++;
			str_position = 0;
		}
	}
	delete[] temp;
	bool main_flag = false;
	for (int iter = 0; iter < lexTable.size; iter++)
	{
		if(lexTable.GetEntry(iter).idxTI != -1)
		if (strcmp(idTable.table[lexTable.GetEntry(iter).idxTI].id,"main") == 0)
		{
			main_flag = true;
			break;
		}
	}
	if (!main_flag)
		throw ERROR_THROW_IN(131, -1, -1);
	for (int iter = 0; iter < lexTable.size; iter++)
	{
		if(lexTable.GetEntry(iter).idxTI != -1)
		if (idTable.table[lexTable.GetEntry(iter).idxTI].value.operation == '/')
		{
			if (lexTable.GetEntry(iter).idxTI != -1)
			if (idTable.table[lexTable.GetEntry(iter).idxTI].value.vint == 0 &&(idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDDATATYPE::UINT || 
				idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDDATATYPE::INT)&&
				(idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDTYPE::L ||
				idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDTYPE::P ||
				idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDTYPE::V ||
				idTable.table[lexTable.GetEntry(iter).idxTI].iddatatype == IT::IDTYPE::VF))
			{
				throw ERROR_THROW_IN(145, lexTable.GetEntry(iter).sn, -1);
			}
		}
	}
	
}

bool token_analize(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	static Flag_type_variable flag_type_variable;

	switch (token[0])
	{
	case LEX_COMMA:
	{
		Add(lexTable, { LEX_COMMA,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFTBRACE:
	{
		Add(lexTable, { LEX_LEFTBRACE,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHTBRACE:
	{
		Add(lexTable, { LEX_RIGHTBRACE,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFTTHESIS:
	{
		Add(lexTable, { LEX_LEFTTHESIS,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHTTHESIS:
	{	
		if (lexTable.table[lexTable.size - 1].lexema == 't')
	{
		switch (flag_type_variable.type)
		{
		case Flag_type_variable::UINT: 
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, 'u' });
			lexTable.table[lexTable.size - 1].idxTI = idTable.size - 1;
			break; 
		};
		case Flag_type_variable::INT: 
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, 'i' }); 
			lexTable.table[lexTable.size - 1].idxTI = idTable.size - 1;
			break; 
		};
		}
	}
		Add(lexTable, { LEX_RIGHTTHESIS,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_SEMICOLON:
	{
		Add(lexTable, { LEX_SEMICOLON,str_number,LT_TI_NULLXDX });
		return true;
	}

	case '+':
	{
		idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, '+' });
		Add(lexTable, { LEX_PLUS,str_number,idTable.size - 1 });
		return true;
	}

	case '-':
	{
		In::IN in_ex;
		if (lexTable.table[lexTable.size - 1].idxTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		if (in_ex.code[token[1]] == in_ex.N)
		{
			FST::FST* number_literal = new FST::FST(INTEGER_LITERAL(token));
			if (FST::execute(*number_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL,str_number,i });
				else
				{
					if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
					{
						if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::INT)
						{
							if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
							{
								throw  ERROR_THROW_IN(146, lexTable.table[i].sn, -1);
							}
							idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vint = atoi(token);
							char* name;
							name = idTable.GetLexemaName();
							idTable.Add({ "\0",name, IT::IDDATATYPE::INT, IT::IDTYPE::L });
							idTable.table[idTable.size - 1].value.vint = atoi(token);
						}
						else if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::UINT)
						{
							throw ERROR_THROW_IN(147, str_number, -1);
						}
					}
					else
					{
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::IDDATATYPE::INT, IT::IDTYPE::L });
						idTable.table[idTable.size - 1].value.vint = atoi(token);
					}
					Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
				}
				delete number_literal;
				number_literal = NULL;
				return true;
			}
		}
		idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, '-' });
		Add(lexTable, { LEX_MINUS,str_number,idTable.size - 1 });
		return true;
	}


	case '*':
	{
		if (lexTable.table[lexTable.size - 1].idxTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, '*' });
		Add(lexTable, { LEX_STAR,str_number,idTable.size - 1 });
		return true;
	}

	case '/':
	{
		if (lexTable.table[lexTable.size - 1].idxTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, '/' });
		Add(lexTable, { LEX_DIRSLASH,str_number,idTable.size - 1 });
		return true;
	}
	case LEX_NOTEQUALITY_SIGN:
	{
		if (token[1] == '=')
		{
		Add(lexTable, { LEX_NOTEQUALITY_SIGN,str_number,LT_TI_NULLXDX });
		return true;
		}
		return false;
	}
	case LEX_EQUAL_SIGN:
	{
		if (token[1] == '=')
		{
			Add(lexTable, { LEX_EQUALITY_SIGN,str_number,LT_TI_NULLXDX });
			return true;
		}
		Add(lexTable, { LEX_EQUAL_SIGN,str_number,LT_TI_NULLXDX });
		return true;
	}
	case LEX_MORE_SIGN:
	{
		if (token[1] == '>')
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, BINARY_RIGHT });
			Add(lexTable, { LEX_DIRSLASH,str_number,idTable.size - 1 });
			return true;
		}
		Add(lexTable, { LEX_MORE_SIGN,str_number,LT_TI_NULLXDX });
		return true;
	}
	case LEX_LESS_SIGN:
	{
		if (token[1] == '<')
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, BINARY_LEFT });
			Add(lexTable, { LEX_DIRSLASH,str_number,idTable.size - 1 });
			return true;
		}
		Add(lexTable, { LEX_LESS_SIGN,str_number,LT_TI_NULLXDX });
		return true;
	}
	case 'f':
	{
		FST::FST* function = new FST::FST(FUNCTION(token));
		FST::FST* _for = new FST::FST(FOR(token));
		FST::FST* _false = new FST::FST(FALSE(token));
		if (FST::execute(*function))
		{
			Add(lexTable, { LEX_FUNCTION,str_number,LT_TI_NULLXDX });

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;
		}
		else if (FST::execute(*_for))
		{
			char* name = idTable.GetViewName();
			idTable.Add({ "\0", name, IT::IDDATATYPE::DEF, IT::IDTYPE::D });
			Add(lexTable, { LEX_FOR,str_number,idTable.size - 1});

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;
		}
		else if (FST::execute(*_false))
		{

			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
				{
					idTable.table[idTable.size - 1].value.vbool = false;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::IDDATATYPE::BOOL, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vbool = false;
				}
				else
				{
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name , IT::IDDATATYPE::BOOL, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vbool = false;
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;

		}
		else
		{
			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'i':
	{
		FST::FST* integer = new FST::FST(INTEGER(token));
		if (FST::execute(*integer))
		{
			Add(lexTable, { LEX_INTEGER,str_number,LT_TI_NULLXDX });

			delete integer;
			integer = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = Flag_type_variable::INT;
			return true;
		}
		else
		{
			delete integer;
			integer = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'u':
	{
		FST::FST* uinteger = new FST::FST(UINTEGER(token));
		if (FST::execute(*uinteger))
		{
			Add(lexTable, { LEX_UINTEGER,str_number,LT_TI_NULLXDX });

			delete uinteger;
			uinteger = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = Flag_type_variable::UINT;
			return true;
		}
		else
		{
			delete uinteger;
			uinteger = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 't':
	{
		FST::FST* _true = new FST::FST(TRUE(token));
		if (FST::execute(*_true))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
				{
					idTable.table[idTable.size - 1].value.vbool = true;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::IDDATATYPE::BOOL, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vbool = true;
				}
				else
				{
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::IDDATATYPE::BOOL, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vbool = false;
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}

			delete _true;
			_true = NULL;
			return true;
		}
		else
		{
			delete _true;
			_true = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'b':
	{
		FST::FST* tbool = new FST::FST(BOOL(token));
		if (FST::execute(*tbool))
		{
			Add(lexTable, { LEX_BOOL,str_number,LT_TI_NULLXDX });

			delete tbool;
			tbool = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = Flag_type_variable::BOOL;
			return true;
		}
		else
		{
			delete tbool;
			tbool = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'c':
	{
		FST::FST* t_char = new FST::FST(CHAR(token));
		if (FST::execute(*t_char))
		{
			Add(lexTable, { LEX_CHAR,str_number,LT_TI_NULLXDX });

			delete t_char;
			t_char = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = Flag_type_variable::CHAR;
			return true;
		}
		else
		{
			delete t_char;
			t_char = NULL;
			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 's':
	{
		FST::FST* string = new FST::FST(STRING(token));
		if (FST::execute(*string))
		{
			Add(lexTable, { LEX_STRING,str_number,LT_TI_NULLXDX });

			delete string;
			string = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = Flag_type_variable::STR;
			return true;
		}
		else
		{
			delete string;
			string = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'r':
	{
		FST::FST* _return = new FST::FST(RETURN(token));
		if (FST::execute(*_return))
		{
			Add(lexTable, { LEX_RETURN,str_number,LT_TI_NULLXDX });

			delete _return;
			_return = NULL;
			return true;
		}
		else
		{
			delete _return;
			_return = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'o':
	{
		FST::FST* _out = new FST::FST(OUT(token));
		if (FST::execute(*_out))
		{
			Add(lexTable, { LEX_OUT,str_number,LT_TI_NULLXDX });

			delete _out;
			_out = NULL;
			return true;
		}
		else
		{
			delete _out;
			_out = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case '\"':
	{
		FST::FST* string_literal = new FST::FST(STRING_LITERAL(token));
		if (FST::execute(*string_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
				{
					int j = 0;
					idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vstr.len = 0;
					
					for (; token[j] != '\0';)
					{
 						idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vstr.str[idTable.table[idTable.size - 1].value.vstr.len] = token[j];
						idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vstr.len++;
						j++;
					}
					idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vstr.str[idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vstr.len++] = '\0';
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0", name, IT::IDDATATYPE::STR, IT::IDTYPE::L });
					j = 0;
					for (; token[j] != '\0';)
					{
						idTable.table[idTable.size - 1].value.vstr.str[idTable.table[idTable.size - 1].value.vstr.len] = token[j];
						idTable.table[idTable.size - 1].value.vstr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vstr.str[idTable.table[idTable.size - 1].value.vstr.len++] = '\0';
					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}
				else
				{
					int j = 0;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0", name, IT::IDDATATYPE::STR, IT::IDTYPE::L });
					i++;
					for (; token[i] != '\0'; i++)
					{
						idTable.table[idTable.size - 1].value.vstr.str[idTable.table[idTable.size - 1].value.vstr.len] = token[i];
						idTable.table[idTable.size - 1].value.vstr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vstr.str[j] = '\0';
					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}			
			;
			}

			delete string_literal;
			string_literal = NULL;
			return true;
		}
	}
	case '\'':
	{
		FST::FST* char_literal = new FST::FST(CHAR_LITERAL(token));
		if (FST::execute(*char_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
				{
					if (token[1] > 128 || token[1] < -127)
					{
						throw  ERROR_THROW_IN(148, lexTable.table[i].sn, -1);
					}
						idTable.table[lexTable.table[lexTable.size - 2].idxTI].value.vchar = token[1];
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::IDDATATYPE::CHAR, IT::IDTYPE::L });
						idTable.table[idTable.size - 1].value.vchar = token[1];
				}
				else
				{
					if (token[1] > 128 || token[1] < -127)
					{
						throw  ERROR_THROW_IN(148, lexTable.table[i].sn, -1);
					}
					char* name;
					name =  idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::IDDATATYPE::CHAR, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vchar =token[1];
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}
			delete char_literal;
			char_literal = NULL;
			return true;
		}
	}
	case 'm':
	{
		FST::FST* _main = new FST::FST(MAIN(token));
		if (FST::execute(*_main))
		{
			for (int iter = 0; iter < idTable.size; iter++)
			{
				if (strcmp(idTable.GetEntry(iter).id, "main") == 0)
				{
					throw ERROR_THROW_IN(129, str_number, idTable.size - 1);
				}
			}
			idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
			Add(lexTable, { LEX_MAIN,str_number,idTable.size - 1 });
			delete _main;
			_main = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			return true;
		}
		else
		{
			delete _main;
			_main = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	default:
	{
		FST::FST* number_literal = new FST::FST(INTEGER_LITERAL(token));
		if (FST::execute(*number_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL,str_number,i });
			else
			{

				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=')
				{
					if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::INT || idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::BOOL)
					{
						if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
						{
							throw  ERROR_THROW_IN(146, lexTable.table[i].sn, -1);
						}
						idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vint = atoi(token);
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::IDDATATYPE::INT, IT::IDTYPE::L });
						idTable.table[idTable.size - 1].value.vint = atoi(token);
					}
					else if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).iddatatype == IT::UINT)
					{
						if (atoi(token) > pow(2, 32) - 1 || atoi(token) < 0)
						{
							throw  ERROR_THROW_IN(147, lexTable.table[i].sn, -1);
						}
						idTable.table[lexTable.GetEntry(lexTable.size - 2).idxTI].value.vuint = atoi(token);
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::IDDATATYPE::UINT, IT::IDTYPE::L });
						idTable.table[idTable.size - 1].value.vuint = atoi(token);
					}
					
				}
				else
				{
					if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
					{
						throw  ERROR_THROW_IN(146, lexTable.table[i].sn, -1);
					}
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::IDDATATYPE::INT, IT::IDTYPE::L });
					idTable.table[idTable.size - 1].value.vint = atoi(token);
				}
				Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
			}
			delete number_literal;
			number_literal = NULL;
			return true;
		}
		else
		{
			delete number_literal;
			number_literal = NULL;

			return  func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	}
}

bool func_var(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable, Flag_type_variable& flag_type_variable)
{
	FST::FST* id = new FST::FST(IDENTIFICATOR(token));
	if (FST::execute(*id))
	{
		bool Checked_id = false;

		//функция
		if (strcmp(token, "main") == 0 || strcmp(token, "strl") == 0 || strcmp(token, "random") == 0 ||
			((lexTable.GetEntry(lexTable.size - 1).lexema == LEX_FUNCTION &&
				lexTable.GetEntry(lexTable.size - 2).lexema == 't') &&
				flag_type_variable.LT_posititon == lexTable.size - 2))
		{
			int check = idTable.IsId(token);
			if (check == -1 || idTable.table[check].iddatatype != flag_type_variable.type)
			{
				if (flag_type_variable.type == Flag_type_variable::INT)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
				}
				if (flag_type_variable.type == Flag_type_variable::STR)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F });
				}
				if (flag_type_variable.type == Flag_type_variable::CHAR)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::CHAR, IT::IDTYPE::F });
				}
				if (flag_type_variable.type == Flag_type_variable::BOOL)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::BOOL, IT::IDTYPE::F });
				}
				if (flag_type_variable.type == Flag_type_variable::UINT)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::UINT, IT::IDTYPE::F });
				}
				if (strcmp(token, "strl") == 0)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
				}
				if (strcmp(token, "random") == 0)
				{
					idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
				}
				flag_type_variable.LT_posititon = -1;
				flag_type_variable.type = Flag_type_variable::DEF;

				if (strcmp(token, "strl") == 0)
				{
					Add(lexTable, { LEX_STRLEN, str_number, idTable.size - 1 });
				}
				else if (strcmp(token, "random") == 0)
				{
					Add(lexTable, { LEX_RANDOM, str_number, idTable.size - 1 });
				}
				else
				{
					Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
					idTable.table[idTable.size - 1].first_in = lexTable.size - 1;
				}
				Checked_id = true;
			}
			else if ((strcmp(token, "strl") == 0 || strcmp(token, "random") == 0) && idTable.IsId(token) != -1)
			{
					if (strcmp(token, "strl") == 0)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
						idTable.table[idTable.size - 1].parmQuantity = 1;
						Add(lexTable, { LEX_STRLEN, str_number, idTable.size - 1 });
					}
					if (strcmp(token, "random") == 0)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
						idTable.table[idTable.size - 1].parmQuantity = 1;
						Add(lexTable, { LEX_RANDOM, str_number, idTable.size - 1 });
					}
					Checked_id = true;
			}
			else
				throw ERROR_THROW_IN(123, str_number, -1);
		}
		//параметр функции 
		if (!Checked_id &&
			(lexTable.GetEntry(lexTable.size - 1).lexema == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
		{
			bool LeftBrace = false;
			for (int i = lexTable.size - 1; i > 0; i--)
			{
				LT::Entry entry = lexTable.GetEntry(i);
				if (entry.lexema == LEX_LEFTBRACE)
					LeftBrace = true;
				bool type_check = (idTable.GetEntry(entry.idxTI).idtype == IT::IDTYPE::F);
				if (lexTable.GetEntry(i).lexema == LEX_ID&& type_check)
				{
					if (lexTable.GetEntry(i - 1).lexema == LEX_FUNCTION && lexTable.GetEntry(i - 2).lexema == 't')
					{
						if (LeftBrace == true) break;
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,i) == -1)
						{
							if (flag_type_variable.type == Flag_type_variable::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token , IT::IDDATATYPE::INT, IT::IDTYPE::P });
								idTable.table[(lexTable.GetEntry(i).idxTI)].parms[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::INT;
								idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;

							}
							if (flag_type_variable.type == Flag_type_variable::STR)
							{
 								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token  , IT::IDDATATYPE::STR, IT::IDTYPE::P });
								idTable.table[(lexTable.GetEntry(i).idxTI)].parms[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::STR;
								idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
							}
							if (flag_type_variable.type == Flag_type_variable::UINT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token , IT::IDDATATYPE::UINT, IT::IDTYPE::P });
								idTable.table[(lexTable.GetEntry(i).idxTI)].parms[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::UINT;
								idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
							}
							if (flag_type_variable.type == Flag_type_variable::BOOL)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token  , IT::IDDATATYPE::BOOL, IT::IDTYPE::P });
								idTable.table[(lexTable.GetEntry(i).idxTI)].parms[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::BOOL;
								idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
							}
							if (flag_type_variable.type == Flag_type_variable::CHAR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token  , IT::IDDATATYPE::CHAR, IT::IDTYPE::P });
								idTable.table[(lexTable.GetEntry(i).idxTI)].parms[idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity] = IT::IDDATATYPE::BOOL;
								idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
							}
							flag_type_variable.LT_posititon = -1;
							flag_type_variable.type = Flag_type_variable::DEF;

							Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
							Checked_id = true;
							break;
						}
						else
							throw ERROR_THROW_IN(125, str_number, -1);
					}
				}
			}
		}

		//переменная(определена ли она уже?)
		if (!Checked_id && (lexTable.GetEntry(lexTable.size - 1).lexema == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
		{
			bool LeftBrace = false;
			bool RightBrace = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				char LEXEMA = lexTable.GetEntry(i).lexema;
				if (LEXEMA == LEX_LEFTBRACE)
				{
					LeftBrace = true;
				}
				if (LEXEMA == LEX_RIGHTBRACE)
				{
					RightBrace = true;
				}
				if (LEXEMA == LEX_FOR && LeftBrace && RightBrace)
				{
					LeftBrace = false;
					RightBrace = false;
					continue;
				}
				if ((LeftBrace && !RightBrace &&
					((LEXEMA == LEX_ID  && idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F && lexTable.table[i - 1].lexema == 'f'))||
					((LEXEMA == LEX_ID && strcmp(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,"main") == 0)))|| (LEXEMA == LEX_FOR && (!LeftBrace && !RightBrace))
					)
				{
					if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,i) == -1)
					{

						if (LEXEMA == LEX_FOR)
						{
							LeftBrace = false;
							for (int l = i; l >= 0; l--)
							{
								char LEXEMA = lexTable.GetEntry(l).lexema;
								if (LEXEMA == LEX_LEFTBRACE)
								{
									LeftBrace = true;
								}
								if (LEXEMA == LEX_ID  && idTable.GetEntry(lexTable.GetEntry(l).idxTI).idtype == IT::IDTYPE::F && LeftBrace)
								{
									idTable.Add({ idTable.GetForName(idTable.GetEntry(lexTable.GetEntry(l).idxTI).id,flag_type_variable),token, (IT::IDDATATYPE)flag_type_variable.type, IT::IDTYPE::VF });
									break;
								}
								if (LEXEMA == LEX_FOR)
								{
									idTable.Add({ idTable.GetForName(idTable.GetEntry(lexTable.GetEntry(l).idxTI).id,flag_type_variable),token, (IT::IDDATATYPE)flag_type_variable.type, IT::IDTYPE::VF });
									break;
								}
							}
							
						}
						else
						{
							if (flag_type_variable.type == Flag_type_variable::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token, IT::IDDATATYPE::INT, IT::IDTYPE::V });
							}
							if (flag_type_variable.type == Flag_type_variable::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token , IT::IDDATATYPE::STR, IT::IDTYPE::V });
							}
							if (flag_type_variable.type == Flag_type_variable::CHAR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token, IT::IDDATATYPE::CHAR, IT::IDTYPE::V });
							}
							if (flag_type_variable.type == Flag_type_variable::BOOL)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token , IT::IDDATATYPE::BOOL, IT::IDTYPE::V });
							}
							if (flag_type_variable.type == Flag_type_variable::UINT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,lexTable.GetEntry(i).idxTI,token , IT::IDDATATYPE::UINT, IT::IDTYPE::V });
							}
							
						}
						flag_type_variable.LT_posititon = -1;
						flag_type_variable.type = Flag_type_variable::DEF;

						Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
						Checked_id = true;
						break;
					}
					else
						throw ERROR_THROW_IN(125, str_number, -1);
				}


			}
		}
		

		//идентификаторы с учётом области видимости
		if (!Checked_id)
		{
			bool LeftBrace = false; 
			bool RightBrace = false; 
			bool LeftThesis = false;
			bool RightThesis = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				char LEXEMA = lexTable.GetEntry(i).lexema;          
				if (LEXEMA == LEX_LEFTBRACE)
				{
					LeftBrace = true;
				}
				if (LEXEMA == LEX_RIGHTBRACE)
				{
					RightBrace = true;
				}
				if (LEXEMA == LEX_LEFTTHESIS)
				{
					LeftThesis = true;
				}
				if (LEXEMA == LEX_RIGHTTHESIS)
				{
					RightThesis = true;
				}
				if (LEXEMA == LEX_FOR && LeftBrace && RightBrace && LeftThesis && RightThesis)
				{
					LeftBrace = false;
					RightBrace = false;
					LeftThesis = false;
					RightThesis = false;
					continue;
				}
				if ((LeftBrace && !RightBrace && ((LEXEMA == LEX_ID  && idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F))) || 
					(LEXEMA == LEX_FOR && (LeftBrace && !RightBrace) || (LEXEMA == LEX_FOR && (LeftThesis && !RightThesis))))
				{
					int temp = 0;
					IT::Entry id_f;
					id_f = idTable.GetEntry(lexTable.GetEntry(i).idxTI);
					if (LEXEMA == LEX_FOR)
					{
						temp = idTable.IsId(token, id_f);
					}
					if (temp == -1)
					{
						int iter = i;
						do
						{
							for (; lexTable.GetEntry(iter).lexema != LEX_LEFTBRACE && iter >= 0; iter--)
							{
							}
							for (; iter >= 0; iter--)
							{
								if (lexTable.GetEntry(iter).idxTI != -1 && iter >= 0)
									if (idTable.table[lexTable.GetEntry(iter).idxTI].idtype == IT::F)
										break;
								if (iter >= 0)
								if (lexTable.GetEntry(iter).lexema == LEX_FOR)
									break;
							}
							if (iter >= 0)
						temp = idTable.IsId(token, idTable.table[lexTable.GetEntry(iter).idxTI]);
						} while (temp == -1 && iter >=0 && iter >= 0);
					}
					if(idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
					{
						temp = idTable.IsId(token, id_f, lexTable.GetEntry(i).idxTI);
					}
					if (temp != -1)
					{
 						Add(lexTable, { LEX_ID,str_number,temp });
						break;
					}
					else
					{
						temp = idTable.IsId(token);
						if (idTable.GetEntry(temp).idtype != IT::IDTYPE::F)
						{
							token[256] = '\0';
						}
						if (temp != -1 && idTable.GetEntry(temp).idtype == IT::IDTYPE::F)
						{
							Add(lexTable, { LEX_ID,str_number,temp });
							break;
						}
						else throw ERROR_THROW_IN(126, str_number, -1);
					}
				}
			}
		}

		delete id;
		id = NULL;
		return true;
	}
	else
	{
		delete id;
		id = NULL;
		return false;
	}
}
