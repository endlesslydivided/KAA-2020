#pragma once
#define ID_MAXSIZE		255					// ������������ ���������� �������� � �������������� 
#define TI_MAXSIZE		4096				// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT  0x00000000			// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT  0x00				// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff			// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255					// ������������ ����� ������
#define TI_CHAR_MAXSIZE  1					// ������������ ����� ����������� ��������
struct Flag_type_variable
{
	int LT_posititon = -1;
	enum { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5 }type = DEF;
};
#define PARM_ID L".id.txt"
namespace IT								// ������� ��������������� 
{
	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5};				// ���� ������ ���������������: integer, string
	enum IDTYPE { D = 0, V = 1, F = 2, P = 3, L = 4,VF = 5 };			// ���� ���������������: ����������, �������, ��������, �������

	struct Entry							// ������ ������� ���������������
	{
		char parent_function[ID_MAXSIZE];
		int parent_function_num;
		char id[ID_MAXSIZE];							// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype;							// ��� ������
		IDTYPE idtype;									// ��� ��������������
		union
		{
			int vint;							
			char operation = '\0';					
			char vchar;
			bool vbool;
			unsigned int vuint;
			struct
			{
				unsigned char len;							// ���������� �������� � string
				char str[TI_STR_MAXSIZE];					// ������� string
			}vstr;						// �������� string
		}value;	// �������� ��������������
		int parmQuantity;
		Entry();
		Entry(const char* parentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
		Entry(const char* parentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int it);
		Entry(const char* parentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, char* str);
		Entry(const char* parentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, const char* str);
		Entry(char* parent_function, int parent_function_number, char* id, IDDATATYPE iddatatype, IDTYPE idtype);
		Entry(const char* parent_function, char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable							// ��������� ������� ���������������
	{
		int noname_lexema_count = 0;
		int for_count = 0 ;
		int maxsize;									// ������� ������� ��������������� < TI_MAXSIZE
		int size;										// ������� ������ ������� ��������������� < maxsize
		Entry* table;									// ������ ����� ������� ���������������
		Entry GetEntry(							// �������� ������ ������� ���������������
			int n											// ����� ���������� ������
		);
	
		void Add(								// ������� ������ � ������� ��������������� 
			Entry entry										// ������ ������� ��������������
		);
		int IsId(const char id[ID_MAXSIZE], Entry ide, int parent_function_number);
		int IsId(const char id[ID_MAXSIZE]);
		int IsId(const char id[ID_MAXSIZE], const char parent_function[ID_MAXSIZE + 5], int parent_function_number);
		void PrintIdTable(const wchar_t* in);
		IdTable();
		char* GetLexemaName();
		char* GetForName(char* id, Flag_type_variable Type);
	};


	void Delete(IdTable& idtable);			// ������� ������� ������ (���������� ������)
};

