#pragma once
#include "Error.h"
namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,	"������������ ��� ������"),
		ERROR_ENTRY(1,	"C�������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100,	"�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,	"��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110,	"������ ��� �������� ����� � �������� ����� (-in) ��� ����� ����������"),
		ERROR_ENTRY(111,	"������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,	"������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113,	"������ ��� �������� ����� ������ (-out)"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120,	"[�����������]������� ������ �����������"),
		ERROR_ENTRY(121,	"[�����������] C������ ������� ��� ���������� ��� ������������ ��� ����������"),
		ERROR_ENTRY(122,	"[�����������]������� ��������������� �����������."),
		ERROR_ENTRY(123,	"[�����������] �������������� �������"),
		ERROR_ENTRY(124,	"[�����������] ������� ������ ���������� ��������"),
		ERROR_ENTRY(125,	"[�����������] ���������� ��������������"),
		ERROR_ENTRY(126,	"[�����������] ����������� ���������� ��� �������� �������� �����"),
		ERROR_ENTRY(127,	"[�����������] ��������� ����� ���������� ��������"),
		ERROR_ENTRY(128,	"[�����������]�� ������� ������� ���� � ��������� ��� ����������������"),
		ERROR_ENTRY(129,	"[�����������] ��������� ���������� main"),

		ERROR_ENTRY(130, "[�����������] ��������� ����� ����������� ��������"),
		ERROR_ENTRY(131, "[�����������] ���������� ������� ����� ��������� ������� main"),
		ERROR_ENTRY(132, "[C������������] ��� �������������� �� ����� ���� �������� ������"),
		ERROR_ENTRY(133, "[C������������] ��� ������� � ��� ������������� �������� ����������"),
		ERROR_ENTRY(134, "[C������������] �������������� �������������� ���� ���� ����������"),
		ERROR_ENTRY(135, "[C������������] ������� �������������� ���������� ���� � ������������� ���������"),
		ERROR_ENTRY(136, "[C������������] ��������� ����������� �������� �������"),
		ERROR_ENTRY(137, "[C������������] �������� ���������� ���������� ���������� �������"),
		ERROR_ENTRY(138, "[C������������] �������������� ���������� � ���������� �������"),
		ERROR_ENTRY(139, "[C������������] ������� strlen ������ ��������� �������� ���� string"),
		ERROR_ENTRY(140, "[C������������] ������� random ������ ��������� �������� ���� uint"),
		ERROR_ENTRY(141, "[C������������] ������� ������ �� ����������"),
		ERROR_ENTRY(142, "[C������������] �������� ��������� ������������ �����"),
		ERROR_ENTRY(143, "[�����������] ������������ �������� ��� ������ �����"),
		ERROR_ENTRY(144, "[C������������] ������������ �������� ��� ������ �����"),
		ERROR_ENTRY(145, "[�����������] ������� �� ����"),
		ERROR_ENTRY(146, "[C������������] ������������ �������� ���������� ���� INT"),
		ERROR_ENTRY(147, "[C������������] ������������ �������� ���������� ���� UINT"),
		ERROR_ENTRY(148, "[C������������] ������������ �������� ���������� ���� CHAR"),
		ERROR_ENTRY(149, "[C������������] �������� ����� ����������� ���������"),

		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600,"[C�������������] �������� ��������� ���������"),
		ERROR_ENTRY(601,"[C�������������] ��������� ��������"),
		ERROR_ENTRY(602,"[C�������������] ������ � ���������"),
		ERROR_ENTRY(603,"[C�������������] ������ � ���������� �������"),
		ERROR_ENTRY(604,"[C�������������] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(605,"[C�������������] ��������� ����������� ����������� �������"),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			er = error[0];
		else
			er = error[id];
		return er;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			er = error[0];
		else
		{
			er = error[id];
			er.inext.line = line;
			er.inext.col = col;
		}
		return er;
	}
};