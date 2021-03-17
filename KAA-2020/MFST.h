#pragma once
#include <stack>
#include "GRB.h"
#include "LT.h"
#include "Parm.h"
#include "Log.h"
#include <iomanip>
using namespace std;
class my_stack_SHORT :public std::stack<short> {
public:
	using std::stack<short>::c; // стек автомата
};
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
static int FST_TRACE_n = -1;
static char rbuf[205], sbuf[205], lbuf[1024];


#define MFST_TRACE_START if(parm.printPath)\
{\
	cout<< setw(4) << left << "Шаг" << ":"\
		<< setw(20) << left << " Правило"\
		<< setw(30) << left << " Входная лента"\
		<< setw(20) << left << " Cтек"\
		<< endl;\
};\
*log.stream << setw(4) << left << "Шаг" << ":"\
		<< setw(20) << left << " Правило"\
		<< setw(30) << left << " Входная лента"\
		<< setw(20) << left << " Cтек"\
		<< endl;

#define MFST_TRACE1		 if(parm.printPath)\
{\
	cout<< setw(4)<<left<<++FST_TRACE_n<<": "\
		<< setw(20)<<left<<rule.getCRule(rbuf,nrulechain)\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;\
};\
*log.stream <<setw(4)<<left<<++FST_TRACE_n<<": "\
		<< setw(20)<<left<<rule.getCRule(rbuf,nrulechain)\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;

#define MFST_TRACE2		 if(parm.printPath)\
{\
	cout<< setw(4)<<left<<FST_TRACE_n<<": "\
		<< setw(20)<<left<<" "\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;\
};\
*log.stream<< setw(4)<<left<<FST_TRACE_n<<": "\
		<< setw(20)<<left<<" "\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;

#define MFST_TRACE3		 if(parm.printPath)\
{\
	cout<< setw(4)<<left<<++FST_TRACE_n<<": "\
		<< setw(20)<<left<<" "\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;\
};\
*log.stream <<setw(4)<<left<<++FST_TRACE_n<<": "\
		<< setw(20)<<left<<" "\
		<< setw(30)<<left<<getCLenta(lbuf,lenta_position)\
		<< setw(20)<<left<<getCSt(sbuf)\
		<< endl;

#define MFST_TRACE4(c)		if(parm.printPath)\
{\
cout<<setw(4)<<left << ++FST_TRACE_n << ": "<<setw(20)<< left <<c<<endl;\
};\
*log.stream <<setw(4)<<left << ++FST_TRACE_n << ": "<<setw(20)<< left <<c<<endl;

#define MFST_TRACE5(c)		if(parm.printPath)\
{\
cout<<setw(4)<<left << FST_TRACE_n << ": "<<setw(20)<< left <<c<<endl;\
};\
*log.stream <<setw(4)<<left << FST_TRACE_n << ": "<<setw(20)<< left <<c<<endl;

#define MFST_TRACE6(c,k)	if(parm.printPath)\
{\
cout<<setw(4)<<left << FST_TRACE_n << ": "<<setw(20)<< left << c << k <<endl;\
};\
*log.stream <<setw(4)<<left << FST_TRACE_n << ": "<<setw(20)<< left << c << k <<endl;

#define MFST_TRACE7			if(parm.printPath)\
{\
cout<<setw(4)<<left << state.lenta_position << ": "\
				<<setw(20)<< left << rule.getCRule(rbuf,state.nrulechain)\
				<<endl;\
};\
*log.stream <<setw(4)<<left << state.lenta_position << ": "\
				<<setw(20)<< left << rule.getCRule(rbuf,state.nrulechain)\
				<<endl;


typedef my_stack_SHORT MFSTSTSTACK;
namespace MFST
{
	/*struct node {
		int data;
		struct node* one;
		struct node* two;
		struct node* three;
		struct node* four;
		struct node* five;
		struct node* six;
		struct node* seven;
		struct node* eight;
	};*/

	//struct node* createNode(short);
	//struct node* insertNode(struct node* root, short value);
	struct MfstState					//состояние автомата для сохранения
	{
		short lenta_position;			//состояние автомата для сохранения
		short nrule;					//номер текущего правила
		short nrulechain;				//номер текущей цепчки, текущего правила
		MFSTSTSTACK st;					//стек автомата
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);	//(позиция на ленте;стек автомата; номер текущей цепочки текущего правила)
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);//(позиция на ленте;стек автомата; номер текущего правила; номер текущей цепочки текущего правила)

	};
	class my_stack_MfstState :public std::stack<MfstState> {
	public:
		using  std::stack<MfstState>::c;
	};
	struct Mfst							//магазинный автомат
	{
		//node* PrintTree(node* NODE, int level);
		enum RC_STEP {					//код вовзрата функции step
			NS_OK,					//найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,				//не найдено правило грамматики(ошибка в грамматике)
			NS_NORULECHAIN,			//не найдена подходящая цепочка правила(ошибка в исходном коде)
			NS_ERROR,				//неизвествный нетерминальный символ грамматики
			TS_OK,					//тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,					//тек. символ ленты != вершине стека, продвинулась лента, pop стека
			LENTA_END,				//текущая позиция ленты >= lenta_size
			SURPRISE,				//неожиданный код возврата (ошибка в step)
		};
		struct MfstDiagnosis		//диагностика
		{
			short lenta_position;		//позиция на ленте
			RC_STEP rc_step;			//код завершения шага
			short nrule;				//номер правила
			short nrule_chain;			//номер цепочки правила
			MfstDiagnosis();			//==
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
			
		}diagnosis[MFST_DIAGN_NUMBER]; 		// последние самые глубокие сообщения

		GRBALPHABET* lenta;					//перекодированныя (TN/NS) лента (из LEX)
		short lenta_position;				//текущая позиция на ленте
		short nrule;						//номер текущего правила
		short nrulechain;					//номер текущей цепочки,текущего правила
		short lenta_size;					//размер ленты
		GRB::Greibach grebach;				//грамматика Грейбах
		LT::LexTable lex;					//результат работы лексического анализатора
		MFSTSTSTACK st;						//стек автомата
		my_stack_MfstState storestate;		//стек для хранения состояний
		Mfst();
		Mfst(LT::LexTable& plex, GRB::Greibach pgrebach);
		char* getCSt(char* buf);			//получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	//лента: n символов с pos
		char* getDiagnosis(short n, char* buf);					//получить n-ю строку диагностики или 0х00
		bool savestate(Parm::PARM parm, Log::LOG log);					//сохранить состояние автомата
		bool resetstate(Parm::PARM parm, Log::LOG log);					//восстановить состояние автомата
		bool push_chain(GRB::Rule::Chain chain);		//поместить цепочку правила в стек
		RC_STEP step(Parm::PARM parm, Log::LOG log);						//выполнить шаг автомата
		bool start(Parm::PARM parm, Log::LOG log);						//запустить автомат
		bool savediagnosis(RC_STEP pprc_step);			//код завершения шага
		void printrules(Parm::PARM parm,Log::LOG log);					//вывести послдеовательность правил
		
		struct Deducation
		{
			GRB::Greibach grebach;
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() 
			{ 
				size = 0; 
				nrules = 0; 
				nrulechains = 0; 
			};
		}deducation;

		bool savededucation();
	};
}
