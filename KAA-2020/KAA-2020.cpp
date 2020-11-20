#pragma once
#include "stdafx.h"

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "����: ", "��� ������ ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		in = ImportLibraries(in);
		Log::WriteIn(log, in);

		LT::LexTable lextable;
		IT::IdTable	idTable;

		token_divivison(in, lextable, idTable);

		lextable.PrintLexTable(parm.in, L".lex_ver_0.txt");
		idTable.PrintIdTable(parm.in);
		
	
		//MFST_TRACE_START										//�������
		//	MFST::Mfst mfst(lextable, GRB::getGreibach());		//�������
		//mfst.start();											// ����� ��������������� �������

		//mfst.savededucation();									//��������� ������� ������

		//mfst.printrules();										//�������: ������� ������� ������	


		for (int iter = 0, lt_position; iter < lextable.size; iter++)
		{
			if (lextable.table[iter - 1].lexema == LEX_EQUAL_SIGN || 
				lextable.table[iter - 1].lexema == LEX_MORE_SIGN || 
				lextable.table[iter - 1].lexema == LEX_LESS_SIGN||
				lextable.table[iter - 1].lexema == LEX_RETURN  ||
				(lextable.table[iter - 3].lexema == LEX_LEFTTHESIS && lextable.table[iter - 2].lexema == LEX_INTEGER && lextable.table[iter - 1].lexema == LEX_RIGHTTHESIS))
			{
				if (PN::PolishNotation(iter, lextable, idTable))
				{
					std::cout << iter << ": �������� ������ ���������;������: " << lextable.table[iter].sn << std::endl;
				}
				else
					std::cout << iter << ": �������� ������ �� ���������;������: " << lextable.table[iter].sn << std::endl;
			}
		}

		SemanticAnalyze(lextable, idTable); //������ �������������� �������

		lextable.PrintLexTable(parm.in, L".lex_ver_PN.txt");
		lextable.PrintLexTableControle(parm.in, L".lex_ver_Control.txt", idTable);
		

		Delete(lextable);
		Delete(idTable);

		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}