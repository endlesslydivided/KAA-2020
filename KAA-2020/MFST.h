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
	using std::stack<short>::c; // ���� ��������
};
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
static int FST_TRACE_n = -1;
static char rbuf[205], sbuf[205], lbuf[1024];


#define MFST_TRACE_START if(parm.printPath)\
{\
	cout<< setw(4) << left << "���" << ":"\
		<< setw(20) << left << " �������"\
		<< setw(30) << left << " ������� �����"\
		<< setw(20) << left << " C���"\
		<< endl;\
};\
*log.stream << setw(4) << left << "���" << ":"\
		<< setw(20) << left << " �������"\
		<< setw(30) << left << " ������� �����"\
		<< setw(20) << left << " C���"\
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
	struct MfstState					//��������� �������� ��� ����������
	{
		short lenta_position;			//��������� �������� ��� ����������
		short nrule;					//����� �������� �������
		short nrulechain;				//����� ������� ������, �������� �������
		MFSTSTSTACK st;					//���� ��������
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);	//(������� �� �����;���� ��������; ����� ������� ������� �������� �������)
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);//(������� �� �����;���� ��������; ����� �������� �������; ����� ������� ������� �������� �������)

	};
	class my_stack_MfstState :public std::stack<MfstState> {
	public:
		using  std::stack<MfstState>::c;
	};
	struct Mfst							//���������� �������
	{
		//node* PrintTree(node* NODE, int level);
		enum RC_STEP {					//��� �������� ������� step
			NS_OK,					//������� ������� � �������, ������� �������� � ����
			NS_NORULE,				//�� ������� ������� ����������(������ � ����������)
			NS_NORULECHAIN,			//�� ������� ���������� ������� �������(������ � �������� ����)
			NS_ERROR,				//������������ �������������� ������ ����������
			TS_OK,					//���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,					//���. ������ ����� != ������� �����, ������������ �����, pop �����
			LENTA_END,				//������� ������� ����� >= lenta_size
			SURPRISE,				//����������� ��� �������� (������ � step)
		};
		struct MfstDiagnosis		//�����������
		{
			short lenta_position;		//������� �� �����
			RC_STEP rc_step;			//��� ���������� ����
			short nrule;				//����� �������
			short nrule_chain;			//����� ������� �������
			MfstDiagnosis();			//==
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
			
		}diagnosis[MFST_DIAGN_NUMBER]; 		// ��������� ����� �������� ���������

		GRBALPHABET* lenta;					//���������������� (TN/NS) ����� (�� LEX)
		short lenta_position;				//������� ������� �� �����
		short nrule;						//����� �������� �������
		short nrulechain;					//����� ������� �������,�������� �������
		short lenta_size;					//������ �����
		GRB::Greibach grebach;				//���������� �������
		LT::LexTable lex;					//��������� ������ ������������ �����������
		MFSTSTSTACK st;						//���� ��������
		my_stack_MfstState storestate;		//���� ��� �������� ���������
		Mfst();
		Mfst(LT::LexTable& plex, GRB::Greibach pgrebach);
		char* getCSt(char* buf);			//�������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	//�����: n �������� � pos
		char* getDiagnosis(short n, char* buf);					//�������� n-� ������ ����������� ��� 0�00
		bool savestate(Parm::PARM parm, Log::LOG log);					//��������� ��������� ��������
		bool resetstate(Parm::PARM parm, Log::LOG log);					//������������ ��������� ��������
		bool push_chain(GRB::Rule::Chain chain);		//��������� ������� ������� � ����
		RC_STEP step(Parm::PARM parm, Log::LOG log);						//��������� ��� ��������
		bool start(Parm::PARM parm, Log::LOG log);						//��������� �������
		bool savediagnosis(RC_STEP pprc_step);			//��� ���������� ����
		void printrules(Parm::PARM parm,Log::LOG log);					//������� ������������������ ������
		
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
