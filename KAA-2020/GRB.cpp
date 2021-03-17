#pragma once
#include "GRB.h"
#include "string.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
namespace GRB
{
#pragma region CONSTRUCTORS
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		this->nt = new GRBALPHABET[this->size = psize];

		int* ptr = (int*)&s;
		for (int i = 0; i < psize; i++)
			this->nt[i] = (short)ptr[i];
	}

	Rule::Rule(GRBALPHABET pnn, int iderroe, short psize, Chain c, ...)
	{
		this->nn = pnn;
		this->iderror = iderroe;
		this->chains = new Chain[this->size = psize];
		Chain* ptr = &c;
		for (int i = 0; i < psize; i++)
			this->chains[i] = ptr[i];
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
	{
		this->startN = pstartN;
		this->stbottomT = pstbottomT;
		this->rules = new Rule[this->size = psize];
		Rule* ptr = &r;
		for (int i = 0; i < psize; i++)
			rules[i] = ptr[i];
	}
#pragma endregion
#pragma region METHODS
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < this->size && rules[k].nn != pnn)
			k++;
		if (k < this->size)
			prule = rules[rc = k];
		return rc;
	}
	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
			rc = rules[n];
		return rc;
	}
	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0;
		this->chains[nchain].getCChain(buf);
		strcat_s(b, sizeof(buf) + 5, buf);

		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;

		while (j < this->size && this->chains[j].nt[0] != t)
			j++;

		rc = (j < this->size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->size; i++)
			b[i] = Chain::alphabet_to_char(this->nt[i]);
		b[this->size] = 0;
		return b;
	}
#pragma endregion
#pragma region GRB_rules
	Greibach greibach(NS('S'), TS('$'),				//стартовый символ, дно стека
		7,											//количество правил
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			//Неверная структура программы
			3,		//S →	tfi(F){rE;};S	| 	tfi(F){NrE;};S | i{NrE;}
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(8, TS('i'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			//Ошибочный оператор
			17,		//N	→	ti; | ti;N | rE; | i = E; | i=E;N  | oE; | oE;N  |c(ti=E;EC;i=E){N}N | c(ti=E;EC;i=E;){N} | ti = E;| ti = E;N |   i = (t)E; | i = (t)E;N | ti = EC;|ti = EC;N | i = EC;|i = EC;N

			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')), 
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')), 
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),  
			Rule::Chain(3, TS('r'), NS('E'), TS(';')), 			
			Rule::Chain(3, TS('t'), TS('i'), TS(';')), 
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')), 
			Rule::Chain(3, TS('o'), NS('E'), TS(';')), 
			Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N')), 
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')), 
			Rule::Chain(7, TS('i'), TS('='), TS('('), TS('t'), TS(')'), NS('E'), TS(';')), 
			Rule::Chain(8, TS('i'), TS('='), TS('('), TS('t'), TS(')'), NS('E'), TS(';'), NS('N')), 
			Rule::Chain(18, TS('c'), TS('('), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('E'), NS('C'), TS(';'), TS('i'), TS('='), NS('E'), TS(';'),  TS(')'), TS('{'), NS('N'), TS('}')), 
			Rule::Chain(19, TS('c'), TS('('), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('E'), NS('C'), TS(';'), TS('i'), TS('='), NS('E'), TS(';'), TS(')'), TS('{'), NS('N'), TS('}'),  NS('N')), 
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), NS('C'), TS(';')),
			Rule::Chain(7, TS('t'), TS('i'), TS('='), NS('E'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), NS('C'), TS(';')),
			Rule::Chain(6, TS('i'), TS('='), NS('E'), NS('C'), TS(';'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,			//Ошибка в выражении
			11,		//E →	i	|	l	|	(E)	|	(EC)	| i(W)	|	iM	|	lM	|	(E)M	|	i(W)M	|	i() |i()M
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), NS('C'), TS(')'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 3,			//Ошибка в параметрах функции
			4,		//W	→	i	|	l	|	i,W	|	l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(1, TS('l'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,			//Ошибка в параметрах вызываемой функции
			2,		//F	→	ti	|	ti,F
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
			Rule::Chain(2, TS('t'), TS('i'))	
		),
		Rule(NS('C'), GRB_ERROR_SERIES + 5,			//Ошибочное определение логического условия
			4,		//C	→		<E		|	>E		|	 ~E	|	 !E
			Rule::Chain(2,  TS('<'), NS('E')),
			Rule::Chain(2,  TS('>'), NS('E')),
			Rule::Chain(2,  TS('~'), NS('E')),
			Rule::Chain(2,  TS('!'), NS('E'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,			//Ошибка в выражении
			2,		//M→		vE	|	vEM
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		)
	);
#pragma endregion

	Greibach getGreibach() { return greibach; }
}