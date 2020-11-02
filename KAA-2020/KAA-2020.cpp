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
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		in = ImportLibraries(in);
		Log::WriteIn(log, in);

		LT::LexTable lextable;
		IT::IdTable	idTable;

		token_divivison(in, lextable, idTable);

		lextable.PrintLexTable(parm.in, L".lex_ver_0.txt");
		MFST_TRACE_START										//отладка
			MFST::Mfst mfst(lextable, GRB::getGreibach());		//автомат
		mfst.start();											// старт синтаксического анализа

		mfst.savededucation();									//сохранить правила вывода

		mfst.printrules();										//отладка: вывести правила вывода	


		for (int iter = 0, lt_position; iter < lextable.size; iter++)
		{
			if (lextable.table[iter - 1].lexema == LEX_EQUAL_SIGN)
			{
				if (PN::PolishNotation(iter, lextable, idTable))
				{
					std::cout << iter << ": польская запись построена;строка: " << lextable.table[iter].sn << std::endl;
				}
				else
					std::cout << iter << ": польская запись не построена;строка: " << lextable.table[iter].sn << std::endl;
			}
		}

		lextable.PrintLexTable(parm.in, L".lex_ver_PN.txt");
		lextable.PrintLexTableControle(parm.in, L".lex_ver_Control.txt", idTable);
		idTable.PrintIdTable(parm.in);

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