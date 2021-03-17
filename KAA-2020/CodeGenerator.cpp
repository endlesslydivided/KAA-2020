#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <vector>
#include <string>
#include "CodeGenerator.h"
#include "In.h"
#include "PN.h"
#include "Log.h"
#include <string> 
#include <sstream>
#include <fstream>
#pragma once

using namespace std;
namespace CG
{
	void add(IT::IdTable& idTable, ConstSegment& cnst)
	{
		string str;
		for (int i = 0; i < idTable.size; i++)
		{
			if (idTable.table[i].idtype == IT::L && idTable.table[i].iddatatype == IT::STR)
			{
				str += "\n\t"; 
				str += idTable.table[i].parent_function; 
				str += idTable.table[i].id; str += " BYTE ";
				str += idTable.table[i].value.vstr.str;
				str += ", 0";
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
			else if (idTable.table[i].idtype == IT::L &&  idTable.table[i].iddatatype == IT::INT)
			{
				str += "\n\t"; 
				str += idTable.table[i].parent_function;
				str += idTable.table[i].id; str += " SDWORD ";
				/*if (idTable.table[i].value.vint < 0)
				str += "-";*/

				str += to_string(idTable.table[i].value.vint);
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
			else if (idTable.table[i].idtype == IT::L && idTable.table[i].iddatatype == IT::UINT)
			{
				str += "\n\t"; 
				str += idTable.table[i].parent_function;
				str += idTable.table[i].id;
				str += " DWORD ";
				str += to_string(idTable.table[i].value.vuint);
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
			else if (idTable.table[i].idtype == IT::L && idTable.table[i].iddatatype == IT::CHAR)
			{
				str += "\n\t"; 
				str += idTable.table[i].parent_function;
				str += idTable.table[i].id; str += " BYTE ";
				str += to_string((int)idTable.table[i].value.vchar);
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
			else if (idTable.table[i].idtype == IT::L && idTable.table[i].iddatatype == IT::BOOL)
			{
				str += "\n\t"; 

				str += idTable.table[i].parent_function;
				str += idTable.table[i].id; str += " BYTE ";
				str += to_string(idTable.table[i].value.vbool);
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}

		}
	}
	void add(IT::IdTable& idTable, DataSegment& dataseg)
	{
		for (int i = 0; i < idTable.size; i++)
		{
			if (idTable.table[i].idtype == IT::V || idTable.table[i].idtype == IT::VF)
			{
				switch (idTable.table[i].iddatatype)
				{
				case IT::INT:
					strcpy_s(dataseg.Data[dataseg.size], TI_STR_MAXSIZE, "\n\t");

					strcat(dataseg.Data[dataseg.size], idTable.table[i].parent_function);
					strcat(dataseg.Data[dataseg.size], idTable.table[i].id);
					strcat(dataseg.Data[dataseg.size++], " SDWORD 0");
					break;
				case IT::STR:
					strcpy_s(dataseg.Data[dataseg.size], TI_STR_MAXSIZE, "\n\t");

					strcat(dataseg.Data[dataseg.size], idTable.table[i].parent_function);
					strcat(dataseg.Data[dataseg.size], idTable.table[i].id);
					strcat(dataseg.Data[dataseg.size++], " DWORD ?");
					break;
				case IT::BOOL:
					strcpy_s(dataseg.Data[dataseg.size], TI_STR_MAXSIZE, "\n\t");

					strcat(dataseg.Data[dataseg.size], idTable.table[i].parent_function);
					strcat(dataseg.Data[dataseg.size], idTable.table[i].id);
					strcat(dataseg.Data[dataseg.size++], " BYTE 0");
					break;
				case IT::CHAR:
					strcpy_s(dataseg.Data[dataseg.size], TI_STR_MAXSIZE, "\n\t");

					strcat(dataseg.Data[dataseg.size], idTable.table[i].parent_function);
					strcat(dataseg.Data[dataseg.size], idTable.table[i].id);
					strcat(dataseg.Data[dataseg.size++], " BYTE 0");
					break;
				case IT::UINT:
					strcpy_s(dataseg.Data[dataseg.size], TI_STR_MAXSIZE, "\n\t");

					strcat(dataseg.Data[dataseg.size], idTable.table[i].parent_function);
					strcat(dataseg.Data[dataseg.size], idTable.table[i].id);
					strcat(dataseg.Data[dataseg.size++], " DWORD 0");
					break;
				}
			}

		}
	}
	void CodeSegment::add(string str)
	{
		strcpy_s(Data[size++],TI_STR_MAXSIZE, str.c_str());
	}

	void	CodeSegmentGeneration(CodeSegment& CS, LT::LexTable lexTable, IT::IdTable& idTable)
	{
		int type_number;
		char buffer[255];
		for (int iter = 0; iter < lexTable.size; iter++)
		{
			if (lexTable.GetEntry(iter).idxTI != -1)
			{
				if (idTable.table[lexTable.GetEntry(iter).idxTI].idtype == IT::IDTYPE::F &&
					iter == idTable.table[lexTable.GetEntry(iter).idxTI].first_in &&
					strcmp(idTable.table[lexTable.GetEntry(iter).idxTI].id, "strl") != 0 && strcmp(idTable.table[lexTable.GetEntry(iter).idxTI].id, "random") != 0)
				{
					for (int i = 0; i < idTable.table[lexTable.GetEntry(iter).idxTI].parmQuantity; i++)
					{
						type_number = (int)idTable.table[lexTable.GetEntry(iter).idxTI].parms[i];
						_itoa_s(type_number, buffer, 10);
						strcat_s(idTable.table[lexTable.GetEntry(iter).idxTI].id, buffer);
					}
				}
			}
		}
		vector<LT::Entry> ñondition_part1;
		vector<vector<LT::Entry>> ñondition_part1_vectors;
		vector<LT::Entry> ñondition_part2;
		vector<vector<LT::Entry>> ñondition_part2_vectors;
		string metka[255];
		vector<LT::Entry> compare_operator;
		vector<LT::Entry> counter;
		vector<LT::Entry> counter_change;
		vector<vector<LT::Entry>> counter_change_vectors;
		bool ifmain = false;
		int iffor = 0;
		In::IN myinf;
		string str;
		vector<LT::Entry> str_for;
		vector<LT::Entry> tempEntries;
		string func_name;
		int idxTI;
		for (int i = 0; i < lexTable.size; i++)
		{
			str.clear();
			while (myinf.code[lexTable .table[i].lexema] != myinf.D && 
				lexTable.table[i].lexema != '\0' &&
				lexTable.table[i].lexema != '=' &&
				lexTable.table[i].lexema != LEX_MORE_SIGN &&
				lexTable.table[i].lexema != LEX_LESS_SIGN &&
				lexTable.table[i].lexema != LEX_EQUALITY_SIGN &&
				lexTable.table[i].lexema != LEX_NOTEQUALITY_SIGN)
			{
				str += lexTable.table[i++].lexema;
				if (lexTable.table[i - 1].lexema == 'i' || lexTable.table[i - 1].lexema == 'l')
				{
					idxTI = lexTable.table[i - 1].idxTI;
				}
				else if (lexTable.table[i - 1].lexema == 'o' || lexTable.table[i - 1].lexema == 'r')
					break;
			}

			if (str == "tfi")
			{
				func_name = idTable.table[idxTI].id;

				if (idTable.table[idxTI].parent_function_num != -1)
				{
					func_name += idTable.table[idxTI].parmQuantity;
				}
				func_name += "_proc";
				CS.add(generateInstructions(FUNC, idxTI, idTable, idTable.table[idxTI].iddatatype, func_name));
				continue;
			}

			if (str == "ti" && idTable.table[idxTI].idtype == IT::P)
			{
				CS.add(generateInstructions(PARM, idxTI, idTable, idTable.table[idxTI].iddatatype));
				continue;
			}
			if ((str == "ti" || str == "i") && lexTable.table[i].lexema == '=')
			{
				i++;
				while (lexTable.table[i].lexema != LEX_SEMICOLON)
				{
					tempEntries.push_back(lexTable.table[i]);
					i++;
				}
				string pop_result;
				if ((idTable.table[idxTI].iddatatype == IT::IDDATATYPE::STR) && tempEntries.size() == 1)
				{

					pop_result = "\n\t mov "; pop_result += idTable.table[idxTI].parent_function; pop_result += idTable.table[idxTI].id; pop_result += ",offset "; 
					pop_result += idTable.table[tempEntries[0].idxTI].parent_function; pop_result += idTable.table[tempEntries[0].idxTI].id;					
				}
				else if ((idTable.table[idxTI].iddatatype == IT::IDDATATYPE::STR) && tempEntries.size() != 1)
				{
					generateExpression(tempEntries, CS, idxTI, idTable, idTable.table[idxTI].iddatatype);
					pop_result = "\n\tpop "; pop_result += idTable.table[idxTI].parent_function; pop_result += idTable.table[idxTI].id; 
				}
				else if (idTable.table[idxTI].iddatatype == IT::IDDATATYPE::CHAR || idTable.table[idxTI].iddatatype == IT::IDDATATYPE::BOOL)
				{
					generateExpression(tempEntries, CS, idxTI, idTable, idTable.table[idxTI].iddatatype);
					pop_result = "\n\tpop dword ptr "; pop_result += idTable.table[idxTI].parent_function; pop_result += idTable.table[idxTI].id; 
				}
				else
				{
					generateExpression(tempEntries, CS, idxTI, idTable, idTable.table[idxTI].iddatatype);
					pop_result = "\n\tpop ";
					pop_result += idTable.table[idxTI].parent_function;
					pop_result += idTable.table[idxTI].id;
				}
				CS.add(pop_result);
				tempEntries.clear();
				continue;
			}
			if (str == "i" && !strcmp(idTable.table[idxTI].id, "main"))
			{
					ifmain = true;
					func_name = "main";
					CS.add(generateInstructions(FUNC, lexTable.table[i].idxTI, idTable, IT::INT, func_name));
					continue;
			}
			else if (str == "c") 
			{
				i++;
				for (; lexTable.table[i].lexema != '{'; i++)
				{
					str_for.push_back(lexTable.table[i]);
				}
				int iter = 0;
				while (str_for[iter].lexema != 'i')
				{
					iter++;
				}
				idxTI = str_for[iter].idxTI;
				iter += 2;
				while (str_for[iter].lexema != ';')
				{
					tempEntries.push_back(str_for[iter]);
					iter++;
				}
				generateExpression(tempEntries, CS, idxTI, idTable, idTable.table[idxTI].iddatatype);
				string pop_result = "\n\tpop ";
				pop_result += idTable.table[idxTI].parent_function;
				pop_result += idTable.table[idxTI].id;
				CS.add(pop_result);
				tempEntries.clear();
				iter++;
				while (str_for[iter].lexema != '<' && str_for[iter].lexema != '>' && str_for[iter].lexema != '~' && str_for[iter].lexema != '!')
				{
					ñondition_part1.push_back(str_for[iter++]);
				}
				ñondition_part1_vectors.push_back(ñondition_part1);
				compare_operator.push_back(str_for[iter]);
				iter++;
				while (str_for[iter].lexema != ';')
				{
					ñondition_part2.push_back(str_for[iter++]);
				}
				ñondition_part2_vectors.push_back(ñondition_part2);
				iter++;
				counter.push_back(str_for[iter]);
				iter++;
				while (str_for[iter].lexema != ';')
				{
					counter_change.push_back(str_for[iter++]);
				}
				counter_change_vectors.push_back(counter_change);
				metka[iffor] = "\n\tmetka";
				metka[iffor] += idTable.table[counter[iffor].idxTI].parent_function ;
				metka[iffor] += idTable.table[counter[iffor].idxTI].id;
				metka[iffor] += ':';
				CS.add(metka[iffor]);
				metka[iffor].clear();
				metka[iffor] = " metka";
				metka[iffor] += idTable.table[counter[iffor].idxTI].parent_function;
				metka[iffor] += idTable.table[counter[iffor].idxTI].id;
				str_for.clear();
				iffor++;
				continue;
			}

			if (str == "o")
			{
				int l = i;
				while (lexTable.table[l].lexema != LEX_SEMICOLON)
				{
					tempEntries.push_back(lexTable.table[l]);
					l++;
				}
				generateExpression(tempEntries, CS, -1, idTable, idTable.table[lexTable.table[i].idxTI].iddatatype);
				CS.add(generateInstructions(PRNT, -1, idTable, idTable.table[lexTable.table[i].idxTI].iddatatype, func_name));
				continue;
			}
			if (lexTable.table[i].lexema == '}' && iffor > 0)
			{
				string out = "\n\t pop ";
				vector<vector<LT::Entry>> buf;
				out += idTable.table[counter[iffor - 1].idxTI].parent_function;
				out += idTable.table[counter[iffor - 1].idxTI].id;
				buf.push_back(counter_change_vectors[iffor - 1]);
				generateExpression(buf[0], CS, -1, idTable, idTable.table[idxTI].iddatatype);
				CS.add(out);
				buf.clear();
				buf.push_back(ñondition_part1_vectors[iffor - 1]);
				generateExpression(buf[0], CS, -1, idTable, idTable.table[idxTI].iddatatype);
				CS.add("\n\tpop ebx");
				buf.clear();
				buf.push_back(ñondition_part2_vectors[iffor - 1]);
				generateExpression(buf[0], CS, -1, idTable, idTable.table[idxTI].iddatatype);
				buf.clear();
				CS.add("\n\tpop eax");
				switch (compare_operator[iffor - 1].lexema)
				{
				case '<':
				{
					CS.add("\n\t cmp ebx, eax");
					CS.add("\n\tjb " + metka[iffor - 1]);
					break;
				}
				case '>':
				{
					CS.add("\n\t cmp ebx, eax");
					CS.add("\n\tja " + metka[iffor - 1]);
					break;
				}
				case '~':
				{
					CS.add("\n\t cmp ebx, eax");
					CS.add("\n\tje " + metka[iffor - 1]);
					break;
				}
				case '!':
				{
					CS.add("\n\t cmp ebx, eax");
					CS.add("\n\tjne " + metka[iffor - 1]);
					break;
				}
				}
				--iffor;
				if (iffor == 0)
				{
					ñondition_part1.clear();
					ñondition_part1_vectors.clear();
					ñondition_part2.clear();
					ñondition_part2_vectors.clear();
					compare_operator.clear();
					counter.clear();
					counter_change.clear();
					counter_change_vectors.clear();
				}
				continue;
			}
			if (lexTable.table[i].lexema == '}')
			{
				if (iffor)
				{
					iffor = false;
					continue;
				}
				if (ifmain)
				{
					CS.add(generateInstructions(RET, 1, idTable));
					CS.add(generateInstructions(ENDP, NULL, idTable, idTable.table[idxTI].iddatatype, func_name));
					break;
				}
				CS.add(generateInstructions(ENDP, NULL, idTable, idTable.table[idxTI].iddatatype, func_name));
				continue;
			}
			if (str == "r")
			{
				int l = i;
				if (ifmain)
				{
					endOfFucntion(CS);
					continue;
				}
				while (lexTable.table[l].lexema != LEX_SEMICOLON)
				{
					tempEntries.push_back(lexTable.table[l]);
					l++;
				}
				generateExpression(tempEntries, CS, NULL, idTable, idTable.table[idxTI].iddatatype);
				endOfFucntion(CS);
				CS.add(generateInstructions(RET, NULL, idTable));
				continue;
			}
		}
	}
	void endOfFucntion(CodeSegment& CS)
	{
		CS.add("\n\n\tjmp EXIT\n\tEXIT_DIV_ON_NULL:\n\tpush offset null_division\n\tcall outstr\n\tpush - 1\n\tcall ExitProcess");
		CS.add("\n\n\tEXIT_OVERFLOW:\n\tpush offset overflow\n\tcall outstr\n\tpush - 2\n\tcall ExitProcess\n\n\tEXIT:");
	}
	void generateExpression(vector<LT::Entry>& tempEntries, CodeSegment& CS, int idxTI, IT::IdTable idTable, IT::IDDATATYPE type)
	{
		bool isboolop = 0;
		bool isconvert = false;
		string out;
		vector<LT::Entry> typeconvertion;
		int begin = 0; int end = 0; int count = 0;

		for (size_t i = 0; i < tempEntries.size(); i++)
		{
			switch (tempEntries[i].lexema)
			{

			case LEX_LITERAL:
			case LEX_ID:		
			{
				CS.add(generateInstructions(PUSH, tempEntries[i].idxTI, idTable));	break;
			}
			case LEX_SEMICOLON: CS.add(generateInstructions(SEM, idxTI, idTable));	break;
			case '@':			CS.add(generateInstructions(CALL, tempEntries[i].idxTI, idTable));	break;
			case '<':
			{
				std::ostringstream oss;
				oss << tempEntries[0].sn;
				string number_str = oss.str();
				out = "\n\tpop ebx \n\tpop eax \n\t cmp eax,ebx";
				out += "\n\tjl istrue";
				out += number_str;
				out += "\n\tpush 0";
				out += "\n\tjmp exit"; out += number_str;
				out += "\n\tistrue";
				out += number_str;
				out += ":\n\tpush 1";
				out += "\n\texit"; out += number_str; out += ":";
				isboolop = true;
				break;
			}
			case '>':
			{
				std::ostringstream oss;
				oss << tempEntries[0].sn;
				string number_str = oss.str();
				out = "\n\tpop ebx \n\tpop eax \n\t cmp eax,ebx";
				out += "\n\tjg istrue";
				out += number_str;
				out += "\n\tpush 0";
				out += "\n\tjmp exit"; out += number_str;
				out += "\n\tistrue";
				out += number_str;
				out += ":\n\tpush 1";
				out += "\n\texit"; out += number_str; out += ":";
				isboolop = true;
				break;
			}
			case '~':
			{
				std::ostringstream oss;
				oss << tempEntries[0].sn;
				string number_str = oss.str();
				out = "\n\tpop ebx \n\tpop eax \n\t cmp eax,ebx";
				out += "\n\tje istrue";
				out += number_str;
				out += "\n\tpush 0";
				out += "\n\tjmp exit"; out += number_str;
				out += "\n\tistrue";
				out += number_str;
				out += ":\n\tpush 1 ";
				out += "\n\texit"; out += number_str; out += ":";
				isboolop = true;
				break;
			}
			case '!':
			{
				std::ostringstream oss;
				oss << tempEntries[0].sn;
				string number_str = oss.str();
				out = "\n\tpop ebx \n\tpop eax \n\t cmp eax,ebx";
				out += "\n\tjne istrue";
				out += number_str;
				out += "\n\tpush 0";
				out += "\n\tjmp exit"; out += number_str;
				out += "\n\tistrue";
				out += number_str;
				out += ":\n\tpush 1 ";
				out += "\n\texit"; out += number_str; out += ":";
				isboolop = true;
				break;
			}
			case '(':
			{
				isconvert = true;
				typeconvertion.push_back(tempEntries[i + 1]);
				i += 2;
				break;
			}
			}
			if (tempEntries[i].idxTI != -1 && idTable.table[tempEntries[i].idxTI].idtype == IT::IDTYPE::D)
			{
				switch (idTable.table[tempEntries[i].idxTI].value.operation)
				{
				case PLUS:
				{		if (type == IT::INT || type == IT::UINT)
						{
							CS.add(generateInstructions(ADD, tempEntries[i].idxTI, idTable));
						}
						else
						{
							CS.add(generateInstructions(ADDSTR, tempEntries[i].idxTI, idTable));
						}
						break;
				}
				case STAR:	CS.add(generateInstructions(MUL, tempEntries[i].idxTI, idTable));	break;
				case MINUS:	CS.add(generateInstructions(DIFF, tempEntries[i].idxTI, idTable));	break;
				case DIRSLASH:	CS.add(generateInstructions(DIV, tempEntries[i].idxTI, idTable));	break;
				case BINARY_LEFT:	CS.add(generateInstructions(BLEFT, tempEntries[i].idxTI, idTable));	break;
				case BINARY_RIGHT:	CS.add(generateInstructions(BRIGHT, tempEntries[i].idxTI, idTable));	break;
				}
			}

		};

		if (isboolop)
		{
			CS.add(out);
		}
		out.clear();
		if (isconvert)
		{
			if (idTable.table[typeconvertion[0].idxTI].value.operation == 'u')
				out = "\n\tcall intToUint \n\tpush eax";
			if (idTable.table[typeconvertion[0].idxTI].value.operation == 'i')
				out = "\n\tcall uintToInt \n\tpush eax";
			CS.add(out);
		}
		tempEntries.clear();
	}
	string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable idTable, IT::IDDATATYPE type, string fucn_name)
	{
		string str; static int ret = 0;
		switch (t)
		{
		case FUNC:
		{
			str += "\n\n"; str += fucn_name; str += " PROC";
			return str;
			break;
		}
		case PARM:
		{
			str += ", "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id; str += " : ";
			switch (type)
			{
			case IT::STR: str += "DWORD"; ret += 4;  return str; break;
			case IT::INT: str += "SDWORD"; ret += 4;   return str; break;
			case IT::UINT: str += "DWORD"; ret += 4;   return str; break;
			case IT::BOOL: str += "DWORD"; ret += 1;   return str; break;
			case IT::CHAR: str += "DWORD"; ret += 1;   return str; break;
			}
			break;
		}
		case PUSH:
		{
		if ((idTable.table[idxTI].iddatatype == IT::INT || idTable.table[idxTI].iddatatype == IT::UINT) && idTable.table[idxTI].idtype != IT::F)
		{
			str += "\n\tpush "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
		else if ((idTable.table[idxTI].iddatatype == IT::STR || idTable.table[idxTI].iddatatype == IT::BOOL || idTable.table[idxTI].iddatatype == IT::CHAR) && idTable.table[idxTI].idtype == IT::P)
		{
			str += "\n\tpush dword ptr "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
		else if ((idTable.table[idxTI].iddatatype == IT::STR) && idTable.table[idxTI].idtype == IT::L)
		{
			str += "\n\tpush offset "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
		else if ((idTable.table[idxTI].iddatatype == IT::CHAR || idTable.table[idxTI].iddatatype == IT::STR) && (idTable.table[idxTI].idtype == IT::V || idTable.table[idxTI].idtype == IT::VF))
		{
			str += "\n\tpush dword ptr "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
		else if (( idTable.table[idxTI].iddatatype == IT::BOOL) && idTable.table[idxTI].idtype != IT::F)
		{
			str += "\n\tpush offset "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
			else if (idTable.table[idxTI].idtype != IT::F)
		{
			str += "\n\tpush offset "; str += idTable.table[idxTI].parent_function;	str += idTable.table[idxTI].id;
		}
			return str;
			break;
		}
		case RET:	
		{	if (idxTI)
		{
			return "\n\tpush 0\n\tcall ExitProcess\n";
		}
		else
		{
			char str[30]; char buf[4];
			strcpy(str, "\n\tpop eax\n\tret ");
			_itoa(ret, buf, 10);
			strcat(str, buf);
			strcat(str, "\n");
			ret = 0;
			return str;  break;
		}
		}
		case ADD:		return "\n\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case BLEFT:		return "\n\tpop ecx\n\tpop eax\n\tsal eax, cl\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case BRIGHT:	return "\n\tpop ecx\n\tpop eax\n\tsar  eax, cl\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case ADDSTR:	return "\n\tcall strcon\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case DIFF:		return "\n\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case MUL:		return "\n\tpop eax\n\tpop ebx\n\timul eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case DIV:		return "\n\tpop ebx\n\tpop eax\n\ttest ebx,ebx\n\tjz EXIT_DIV_ON_NULL\n\tcdq\n\tidiv ebx\n\tpush eax"; break;
		case ENDP:	
		{
			str += "\n"; str += fucn_name; str += " ENDP";
			switch ((strcmp(fucn_name.c_str(), "main") == 0) ? true : false)
			{
			case true: str += "\nend main"; return str;
			case false:						return str;
			}
			break;
		}
		case PRNT:	
		{
			if (type == IT::STR)
				return "\n\tcall outstr";
			else if (type == IT::CHAR)
				return "\n\tcall outchar"; 
			else if (type == IT::BOOL)
				return "\n\tcall outbool";
			else if (type == IT::INT)
				return "\n\tcall outint";
			else if (type == IT::UINT)
				return "\n\tcall outuint";
			break;
		}
		case SEM:	
		{	if (idxTI != -1 && idTable.table[idxTI].iddatatype == IT::INT && idTable.table[idxTI].idtype != IT::F)
		{
			str += "\n\tpop "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}
			else if (idxTI != -1 && idTable.table[idxTI].iddatatype == IT::STR)
		{
			str += "\n\tpush offset "; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
		}	
		return str; 
		break;
		}
		case CALL:  
		{
			if (strcmp(idTable.table[idxTI].id, "strl") && strcmp(idTable.table[idxTI].id, "random"))
			{
				str += "\n\tcall "; str += idTable.table[idxTI].id; str += "_proc";
			}
			else
			{
				str += "\n\tcall "; str += idTable.table[idxTI].id; 
			}
			str += "\n\tpush eax";
			return str; 
			break;
		}
		case MOV:
		{
			str += "\n\tmov ecx,"; str += idTable.table[idxTI].parent_function; str += idTable.table[idxTI].id;
			return str;
			break;
		}
		}
	}
	void print(Log::LOG log, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg)
	{
		for (int i = 0; i < cnst.size; i++)
			*log.stream << cnst.Data[i];
		for (int i = 0; i < dataseg.size; i++)
			*log.stream << dataseg.Data[i];
		for (int i = 0; i < codeseg.size; i++)
			*log.stream << codeseg.Data[i];
	}
	void DataOut(ofstream& _file, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg)
	{
		for (int i = 0; i < cnst.size; i++)
			_file << cnst.Data[i];
		for (int i = 0; i < dataseg.size; i++)
			_file << dataseg.Data[i];
		for (int i = 0; i < codeseg.size; i++)
			_file << codeseg.Data[i];
	}
	void startGeneration(wchar_t* file, ConstSegment& CnstS, DataSegment& DS, CodeSegment& CS)
	{
		wchar_t buf[255];
		wcscpy_s(buf, file);
		ofstream _file; _file.open(buf, ios_base::out | ios_base::trunc);						//Çàïèñü  àññåìáëåðà â ôàéë
		if (_file.is_open())
		{
			remove((char*)buf);
		}
		DataOut(_file, CnstS, DS, CS);
		_file.close();
	}
};
