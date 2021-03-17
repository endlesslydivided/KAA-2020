#pragma once
#include "SemanticAnalys.h"

bool SemanticAnalyze(LT::LexTable& lexTable, IT::IdTable& idTable)
{
	bool Standart_LIB = false;
	int isMain = 0;
	bool isFunction = false;
	bool choiсe = true;
	int isBrace = 0;
	bool isReturn = false;
	bool expression_Num = true;
	int isFor = 0;

	for (int i = 0, j; i < lexTable.size; i++)
	{
#pragma region 141 -функция ничего не возвращает (main)
		if (strcmp(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, "main") == 0)
		{
			if (isFunction == true || isReturn == true)
			{
				throw ERROR_THROW_IN(141, lexTable.table[i].sn, -1);
				choiсe = false;
				break;
			}
			isFunction = true;
			isReturn = true;
			isMain++;
			continue;
		}
#pragma endregion
#pragma region 137,139,140 - Неверное количество параметров вызываемой функции или неверный параметры (strl,random)
		if (lexTable.GetEntry(i).lexema == '@')
		{

			if (strcmp(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, "strl") == 0)
			{
				int parm_q = 0;
				int b = i - 1;
				int parm_lexema = lexTable.GetEntry(i + 1).lexema & 0x0f;
				while ((lexTable.table[b].lexema == LEX_ID || lexTable.table[b].lexema == LEX_LITERAL) && parm_q < parm_lexema)
				{
					parm_q++;
					b--;
				}
				if (parm_q != 1)
					throw ERROR_THROW_IN(137, lexTable.table[i].sn, -1);
				if ((lexTable.table[i - 1].lexema == LEX_ID || lexTable.table[i - 1].lexema == LEX_LITERAL) && idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i - 1).idxTI).id)].iddatatype != IT::IDDATATYPE::STR)
				{
					throw ERROR_THROW_IN(139, lexTable.table[i].sn, -1);
					choiсe = false;
				}
				continue;
			}
			if (strcmp(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, "random") == 0)
			{
				int parm_q = 0;
				int b = i - 1;
				int parm_lexema = lexTable.GetEntry(i + 1).lexema & 0x0f;
				while ((lexTable.table[b].lexema == LEX_ID || lexTable.table[b].lexema == LEX_LITERAL) && parm_q < parm_lexema)
				{
					parm_q++;
					b--;
				}
				if (parm_q != 1)
					throw ERROR_THROW_IN(137, lexTable.table[i].sn, -1);
				if ((lexTable.table[i - 1].lexema == LEX_ID || lexTable.table[i - 1].lexema == LEX_LITERAL) && idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i - 1).idxTI).id)].iddatatype != IT::IDDATATYPE::UINT)
				{
					throw ERROR_THROW_IN(140, lexTable.table[i].sn, -1);
					choiсe = false;
				}
				continue;
			}
		}
#pragma endregion
		switch (lexTable.table[i].lexema)
		{
			case LEX_INTEGER:
			{
#pragma region 132 - Имя идентификатора не может быть ключевым словом
				if (lexTable.table[i + 1].lexema != LEX_ID && lexTable.table[i + 1].lexema != LEX_FUNCTION && lexTable.table[i + 1].lexema != LEX_RIGHTTHESIS)
					throw ERROR_THROW_IN(132, lexTable.table[i].sn, -1);
				break;
#pragma endregion
			}
			case LEX_FUNCTION:
			{
#pragma region 133 -  Тип функции и тип возвращаемого значения отличаются
				int p = i;
				bool isBooleanR = false;
				bool isIntR = false;
				if (lexTable.table[i - 1].lexema == LEX_INTEGER && lexTable.table[i + 1].lexema == LEX_ID && lexTable.table[i + 2].lexema == LEX_LEFTTHESIS)
				{
					isFunction = true;
					isReturn = true;
				}
				while (lexTable.table[p].lexema != LEX_RETURN)
				{
					p++;
				}
				if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::BOOL)
				{
					for (int iter = p + 1; lexTable.table[iter].lexema != LEX_SEMICOLON; iter++)
					{
						if (lexTable.table[iter].lexema == LEX_EQUALITY_SIGN ||
							lexTable.table[iter].lexema == LEX_MORE_SIGN ||
							lexTable.table[iter].lexema == LEX_LESS_SIGN ||
							lexTable.table[iter].lexema == LEX_NOTEQUALITY_SIGN)
						{
							isBooleanR = true; continue;
						}
						if (lexTable.table[iter].idxTI != -1)
						{
							if (idTable.table[lexTable.table[iter].idxTI].iddatatype = IT::IDDATATYPE::BOOL)
							{
								isBooleanR = true;
								break;
							}
						}
						if ((lexTable.table[iter].lexema == LEX_EQUALITY_SIGN ||
							lexTable.table[iter].lexema == LEX_MORE_SIGN ||
							lexTable.table[iter].lexema == LEX_LESS_SIGN ||
							lexTable.table[iter].lexema == LEX_NOTEQUALITY_SIGN) && isBooleanR)
						{
							throw ERROR_THROW_IN(149, lexTable.table[i].sn, -1);
							break;
						}
					}
					if (!isBooleanR)
					{
						throw ERROR_THROW_IN(133, lexTable.table[i].sn, -1);
					}
					break;
				}
					for (int iter = p + 1; lexTable.table[iter].lexema != LEX_SEMICOLON; iter++)
					{
						if(lexTable.table[iter].idxTI != -1)
						if ((idTable.table[lexTable.table[iter].idxTI].idtype == IT::IDTYPE::V ||
							idTable.table[lexTable.table[iter].idxTI].idtype == IT::IDTYPE::L ||
							idTable.table[lexTable.table[iter].idxTI].idtype == IT::IDTYPE::VF) &&
							(idTable.table[lexTable.table[iter].idxTI].iddatatype != idTable.table[lexTable.table[i + 1].idxTI].iddatatype))

						{
							throw ERROR_THROW_IN(133, lexTable.table[i].sn, -1);
						}
					}
				break;
#pragma endregion
			}
			case LEX_RETURN:
			{
#pragma region 141 -функция ничего не возвращает (main)
				if (isFunction == true)
				{
					isReturn = false;
					isFunction = false;
					break;
				}
				else
				{
					if (isMain == 0)
						throw ERROR_THROW_IN(141, lexTable.table[i].sn, -1);
					isReturn = false;
					break;
				}
				break;
#pragma endregion
			}
			case LEX_ID:
			{
#pragma region 136 - нельзя присваивать значение функции	
				if (idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) != -1 && idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id)].idtype == IT::IDTYPE::F && lexTable.table[i + 1].lexema == LEX_EQUAL_SIGN)
				{
					throw ERROR_THROW_IN(136, lexTable.table[i].sn, -1);
					choiсe = false;
				}
#pragma endregion

#pragma region 134 - Несоответствие присваиваемого типа типу переменной

				if (lexTable.GetEntry(i + 1).lexema == '=')
				{
					//bool str_in = false;
					int j = i;
					bool func_check = true;
					IT::IDDATATYPE idtu = IT::IDDATATYPE::DEF;
					IT::IDDATATYPE idti = IT::IDDATATYPE::DEF;
					if (idTable.GetEntry(lexTable.GetEntry(i + 3).idxTI).value.operation == 'u')
						idtu = IT::IDDATATYPE::UINT;
					else if (idTable.GetEntry(lexTable.GetEntry(i + 3).idxTI).value.operation == 'i')
						idti = IT::IDDATATYPE::INT;
					if (idtu == IT::IDDATATYPE::DEF && idti == IT::IDDATATYPE::DEF)break;
					if (idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) != -1 &&
						idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id)].iddatatype ==
						idtu)
					{
						break;
					}
					if (idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) != -1 &&
						idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id)].iddatatype ==
						idti)
					{
						break;
					}
					throw ERROR_THROW_IN(134, lexTable.table[i].sn, -1);
					while (lexTable.GetEntry(j).lexema != LEX_SEMICOLON)
					{
						j++;
						func_check = true;

						if (lexTable.GetEntry(j).idxTI != -1)
						{
							if (idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::F ||
								idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::V ||
								idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::P ||
								idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::L)
							{
								if (idTable.table[lexTable.GetEntry(j).idxTI].iddatatype != idTable.table[lexTable.GetEntry(i).idxTI].iddatatype)
								{
									if ((idTable.table[lexTable.GetEntry(j).idxTI].iddatatype != IT::UINT &&
										idTable.table[lexTable.GetEntry(j).idxTI].value.vint >= 0) &&
										idTable.table[lexTable.GetEntry(i).idxTI].iddatatype == IT::UINT)
									{
										idTable.table[lexTable.GetEntry(j).idxTI].iddatatype = IT::UINT;
										idTable.table[lexTable.GetEntry(j).idxTI].value.vuint = idTable.table[lexTable.GetEntry(j).idxTI].value.vint;
										break;
									}
									int l = j;
									while (lexTable.GetEntry(l).lexema != LEX_SEMICOLON)
									{
										if (lexTable.GetEntry(l).lexema == '@')
										{
											func_check = false;
											break;
										}
										l++;
									}
									if (!func_check)continue;
									throw ERROR_THROW_IN(134, lexTable.table[i].sn, -1);
									choiсe = false;
									break;
								}
							}
						}
					}
					
				}
				break;
#pragma endregion
			}

#pragma region 137,138 - несоответствие или неверное кол-во параметров вызываемой функции
			case '@':
			{
				int int_p = 0;
				int str_p = 0;
				int uint_p = 0;
				int char_p = 0;
				int bool_p = 0;

				int int_p2 = 0;
				int str_p2 = 0;
				int uint_p2 = 0;
				int char_p2 = 0;
				int bool_p2 = 0;
				int a = 0;
				for (int iter = 0; iter < lexTable.size; iter++)
				{
					if (strcmp(idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(i).idxTI).id)].id, idTable.table[idTable.IsId(idTable.GetEntry(lexTable.GetEntry(iter).idxTI).id)].id) == 0)
					{
						a = iter ;
						break;
					}
				}
				while (lexTable.table[a].lexema != LEX_RIGHTTHESIS)
				{
					if (lexTable.GetEntry(a).idxTI != -1)
					{
						if (idTable.table[lexTable.GetEntry(a).idxTI].idtype == IT::IDDATATYPE::STR)
							str_p++;
						else if (idTable.table[lexTable.GetEntry(a).idxTI].idtype == IT::IDDATATYPE::INT)
							int_p++;
						else if (idTable.table[lexTable.GetEntry(a).idxTI].idtype == IT::IDDATATYPE::UINT)
							uint_p++;
						else if (idTable.table[lexTable.GetEntry(a).idxTI].idtype == IT::IDDATATYPE::CHAR)
							char_p++;
						else if (idTable.table[lexTable.GetEntry(a).idxTI].idtype == IT::IDDATATYPE::BOOL)
							bool_p++;
					}
					a++;
				}
				int parm_lexema = 0;
				while ((lexTable.table[i - 1].lexema == LEX_ID || lexTable.table[i - 1].lexema == LEX_LITERAL) && parm_lexema < idTable.table[lexTable.GetEntry(a).idxTI].parmQuantity)
				{
					if (idTable.table[lexTable.GetEntry(i).idxTI].idtype == IT::IDDATATYPE::STR)
						str_p2++;
					else if (idTable.table[lexTable.GetEntry(i).idxTI].idtype == IT::IDDATATYPE::INT)
						int_p2++;
					else if (idTable.table[lexTable.GetEntry(i).idxTI].idtype == IT::IDDATATYPE::UINT)
						uint_p2++;
					else if (idTable.table[lexTable.GetEntry(i).idxTI].idtype == IT::IDDATATYPE::CHAR)
						char_p2++;
					else if (idTable.table[lexTable.GetEntry(i).idxTI].idtype == IT::IDDATATYPE::BOOL)
						bool_p2++;
					i--;
					parm_lexema++;
				}
				if ((lexTable.table[i + 1].lexema & 0x0f) != idTable.table[lexTable.GetEntry(i).idxTI].parmQuantity)
				{
					throw ERROR_THROW_IN(137, lexTable.table[i].sn, -1);
					choiсe = false;
				}
				if (int_p != int_p2 && str_p != str_p2 && uint_p != uint_p2 && char_p != char_p2 && bool_p != bool_p2)
					throw ERROR_THROW_IN(138, lexTable.table[i].sn, -1);
				break;
			}
#pragma endregion
			case LEX_LESS_SIGN:
			case LEX_MORE_SIGN:
			case LEX_EQUALITY_SIGN:
			case LEX_NOTEQUALITY_SIGN:
			{
#pragma region 149 - нарушение формы логического выражения
				for (int iter = i + 1; lexTable.table[iter].lexema != LEX_SEMICOLON; iter++)
				{
					if (lexTable.table[iter].lexema == LEX_EQUALITY_SIGN ||
						lexTable.table[iter].lexema == LEX_MORE_SIGN ||
						lexTable.table[iter].lexema == LEX_LESS_SIGN ||
						lexTable.table[iter].lexema == LEX_NOTEQUALITY_SIGN)
					{
						throw ERROR_THROW_IN(149, lexTable.table[i].sn, -1);
						break;
					}
				}
				for (int iter = i - 1; lexTable.table[iter].lexema != LEX_SEMICOLON; iter--)
				{
					if (lexTable.table[iter].lexema == LEX_EQUALITY_SIGN ||
						lexTable.table[iter].lexema == LEX_MORE_SIGN ||
						lexTable.table[iter].lexema == LEX_LESS_SIGN ||
						lexTable.table[iter].lexema == LEX_NOTEQUALITY_SIGN)
					{
						throw ERROR_THROW_IN(149, lexTable.table[i].sn, -1);
						break;
					}
				}
#pragma endregion 

#pragma region 144 - недопустимая операция над данным типом
				for (int iter = i + 1; lexTable.table[iter].lexema != LEX_SEMICOLON; iter++)
				{
					if (lexTable.table[iter].idxTI != -1 && lexTable.table[iter].lexema != 'v')
					if (idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::INT &&
						idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::UINT &&
						idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::BOOL)
					{
						throw ERROR_THROW_IN(144, lexTable.table[i].sn, -1);
						break;
					}
				}
				for (int iter = i - 1; lexTable.table[iter].lexema != LEX_SEMICOLON && lexTable.table[iter].lexema != LEX_EQUAL_SIGN; iter--)
				{
					if(lexTable.table[iter].idxTI != -1 && lexTable.table[iter].lexema != 'v')
					if (idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::INT &&
						idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::UINT &&
						idTable.table[lexTable.table[iter].idxTI].iddatatype != IT::IDDATATYPE::BOOL)
					{
						throw ERROR_THROW_IN(144, lexTable.table[i].sn, -1);
						break;
					}
				}
#pragma endregion 

#pragma region 134 - Несоответствие присваиваемого типа типу переменной
				i++;
				int j = i;
				bool func_check = true;
				while (lexTable.GetEntry(j).lexema != LEX_SEMICOLON)
				{
					j++;
					func_check = true;

					if (lexTable.GetEntry(j).idxTI != -1)
					{
						if (idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::F ||
							idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::V ||
							idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::P ||
							idTable.table[lexTable.GetEntry(j).idxTI].idtype == IT::IDTYPE::L)
						{
							if(lexTable.GetEntry(i).idxTI != -1)
							if (idTable.table[lexTable.GetEntry(j).idxTI].iddatatype != idTable.table[lexTable.GetEntry(i).idxTI].iddatatype)
							{
								if ((idTable.table[lexTable.GetEntry(j).idxTI].iddatatype != IT::UINT &&
									idTable.table[lexTable.GetEntry(j).idxTI].value.vint >= 0) &&
									idTable.table[lexTable.GetEntry(i).idxTI].iddatatype == IT::UINT)
								{
									idTable.table[lexTable.GetEntry(j).idxTI].iddatatype = IT::UINT;
									idTable.table[lexTable.GetEntry(j).idxTI].value.vuint = idTable.table[lexTable.GetEntry(j).idxTI].value.vint;
									break;
								}
								int l = j;
								while (lexTable.GetEntry(l).lexema != LEX_SEMICOLON)
								{
									if (lexTable.GetEntry(l).lexema == '@')
									{
										func_check = false;
										break;
									}
									l++;
								}
								if (!func_check)continue;
								throw ERROR_THROW_IN(134, lexTable.table[i].sn, -1);
								choiсe = false;
								break;
							}
						}
					}
				}
				break;
#pragma endregion
			}
#pragma region 142 - нарушена структура программного блока
			case LEX_LEFTBRACE:
			{
				isBrace++;
				if (isBrace == 2 + isFor)
					throw ERROR_THROW_IN(142, lexTable.GetEntry(i).sn, -1);
				break;
			}
#pragma endregion 
			case LEX_FOR:
			{
				isFor++;
				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (isFor)
				{
					isFor--;
					isBrace--;
					break;
				}
				isBrace--;
				break;
			}
		}

	}
#pragma region 141 - функция не возвращает значение
	if (isReturn == true)
	{
		throw ERROR_THROW(141);
		choiсe = false;
	}
	if (isBrace != 0)
	{
		throw ERROR_THROW_IN(142, -1, -1);
		choiсe = false;
	}
#pragma endregion
	return choiсe;
}



