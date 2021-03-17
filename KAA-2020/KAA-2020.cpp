#pragma once
#include "stdafx.h"

#define FILE_PATH_ASM L"ASM"


int wmain(int argc, wchar_t* argv[])
{	
	clock_t start, stop,lex,sint,sem,pn,GC;
	start = clock();
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

		printf("���������� ������������ �������.\n");

		token_divivison(in, lextable, idTable);
		lextable.PrintLexTable(parm.in, L".lex_beforePN.txt");
		idTable.PrintIdTable(parm.in);

		printf("����������� ������ �������� ��� ������.\n");

		*log.stream <<"------����������� ������ �������� ��� ������------" <<std::endl;

		lex = clock();
		if(parm.print�T)
		printf("������ ������������ ����������� ������ �������� %d �����������\n", (lex - start));
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
		printf("���������� ��������������� �������.\n");

		*log.stream << "------�������������� ������------." << std::endl;
		MFST_TRACE_START;
		MFST::Mfst mfst(lextable, GRB::getGreibach());		
		bool syntright = mfst.start(parm,log);						
		if (syntright)
		{
		mfst.savededucation();									
		mfst.printrules(parm,log);	

		*log.stream << "------�������������� ������ �������� ��� ������------" << std::endl;

		sint = clock();
		if (parm.print�T)
		printf("������ ��������������� ����������� ������ �������� %d �����������\n", (sint - lex));
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
		printf("���������� ��������� � ������ � �������� �������.\n");

		*log.stream << "------�������� �������------" << std::endl;
		
		int PNnumberGenerated = 0;
		for (int iter = 0, lt_position; iter < lextable.size; iter++)
		{
			if (lextable.table[iter - 1].lexema == LEX_EQUAL_SIGN || 
				lextable.table[iter - 1].lexema == LEX_MORE_SIGN || 
				lextable.table[iter - 1].lexema == LEX_LESS_SIGN||
				lextable.table[iter - 1].lexema == LEX_NOTEQUALITY_SIGN ||
				lextable.table[iter - 1].lexema == LEX_EQUALITY_SIGN ||
				lextable.table[iter - 1].lexema == LEX_RETURN  ||
				lextable.table[iter - 1].lexema == LEX_OUT ||
				(lextable.table[iter - 3].lexema == LEX_LEFTTHESIS && 
					lextable.table[iter - 2].lexema == LEX_INTEGER && 
					lextable.table[iter - 1].lexema == LEX_RIGHTTHESIS))
			{
				if (PN::PolishNotation(iter, lextable, idTable))
				{
					PNnumberGenerated++;
				}
			}
		}
		*log.stream << "��������� ���������� �������: " << PNnumberGenerated << std::endl;

		std::cout << "��������� ���������� �������: " << PNnumberGenerated << std::endl;
		pn = clock();
		if (parm.print�T)
		printf("�������������� ��������� � �������� ������� ������ %d �����������\n", (pn - sint));
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

		printf("���������� �������������� �������.\n");
		*log.stream << "------������������� ������------" << std::endl;
		SemanticAnalyze(lextable, idTable);
		if (parm.printPN)
		{
			lextable.PrintLexTable(parm.in, L".lex_PN.txt");
			lextable.PrintLexTableControle(parm.in, L".lex_PN_CONTROL.txt", idTable);
		}
		printf("������������� ������ �������� ��� ������.\n");
		sem = clock();
		if (parm.print�T)
		printf("������ ������������ ����������� ������ �������� %d �����������\n", (sem - pn));
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
		printf("���������� ��������� ����.\n");

		CG::ConstSegment CnstS(idTable.size);
		CG::DataSegment Data(idTable.size);
		CG::CodeSegment Code;
		CG::add(idTable, CnstS);
		CG::add(idTable, Data);
		CG::CodeSegmentGeneration(Code, lextable, idTable);
		CG::startGeneration(parm.out, CnstS, Data, Code);

		std::cout << "��������������� ��� ��������� � ����� :" <<  std::endl;
		wcout << parm.out << std::endl;
		GC = clock();
		if (parm.print�T)
		printf("������ ���������� ���� ������ �������� %d �����������\n", (GC - sem));
		}
		Delete(lextable);
		Delete(idTable);
		Log::Close(log);

		stop = clock();
		if (parm.print�T)
		printf("������ ����������� ������ �������� %d �����������\n", (stop - start));
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}