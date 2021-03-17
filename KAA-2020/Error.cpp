#pragma once
#include "Error.h"
namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,	"Недопустимый код ошибки"),
		ERROR_ENTRY(1,	"Cистемный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100,	"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,	"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110,	"Ошибка при открытии файла с исходным кодом (-in) или файла библиотеки"),
		ERROR_ENTRY(111,	"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,	"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,	"Ошибка при создании файла выхода (-out)"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120,	"[Лексическая]Таблица лексем переполнена"),
		ERROR_ENTRY(121,	"[Лексическая] Cлишком большое имя переменной или недопустимое имя переменной"),
		ERROR_ENTRY(122,	"[Лексическая]Таблица идентификаторов переполнена."),
		ERROR_ENTRY(123,	"[Лексическая] Нераспознанная лексема"),
		ERROR_ENTRY(124,	"[Лексическая] Нарушен формат строкового литерала"),
		ERROR_ENTRY(125,	"[Лексическая] Перезапись идентификатора"),
		ERROR_ENTRY(126,	"[Лексическая] Неизвестная переменная или неверное ключевое слово"),
		ERROR_ENTRY(127,	"[Лексическая] Превышена длина строкового литерала"),
		ERROR_ENTRY(128,	"[Лексическая]Не удалось создать файл с лексемами или идентификаторами"),
		ERROR_ENTRY(129,	"[Лексическая] Повторное объявление main"),

		ERROR_ENTRY(130, "[Лексическая] Превышена длина символьного литерала"),
		ERROR_ENTRY(131, "[Лексическая] Отсутствие входной точки программы функции main"),
		ERROR_ENTRY(132, "[Cемантическая] Имя идентификатора не может быть ключевым словом"),
		ERROR_ENTRY(133, "[Cемантическая] Тип функции и тип возвращаемого значения отличаются"),
		ERROR_ENTRY(134, "[Cемантическая] Несоответствие присваиваемого типа типу переменной"),
		ERROR_ENTRY(135, "[Cемантическая] Наличие идентификатора строкового типа в целочисленном выражении"),
		ERROR_ENTRY(136, "[Cемантическая] Запрещено присваивать значение функции"),
		ERROR_ENTRY(137, "[Cемантическая] Неверное количество параметров вызываемой функции"),
		ERROR_ENTRY(138, "[Cемантическая] Несоответствие параметров в вызываемой функции"),
		ERROR_ENTRY(139, "[Cемантическая] Функция strlen должна принимать параметр типа string"),
		ERROR_ENTRY(140, "[Cемантическая] Функция random должна принимать параметр типа uint"),
		ERROR_ENTRY(141, "[Cемантическая] Функция ничего не возвращает"),
		ERROR_ENTRY(142, "[Cемантическая] Нарушена структура программного блока"),
		ERROR_ENTRY(143, "[Лексическая] Недопустимая операция над данным типом"),
		ERROR_ENTRY(144, "[Cемантическая] Недопустимая операция над данным типом"),
		ERROR_ENTRY(145, "[Лексическая] Деление на ноль"),
		ERROR_ENTRY(146, "[Cемантическая] Недопустимое значение переменной типа INT"),
		ERROR_ENTRY(147, "[Cемантическая] Недопустимое значение переменной типа UINT"),
		ERROR_ENTRY(148, "[Cемантическая] Недопустимое значение переменной типа CHAR"),
		ERROR_ENTRY(149, "[Cемантическая] Нарушена форма логического выражения"),

		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600,"[Cинтаксическая] Неверная структура программы"),
		ERROR_ENTRY(601,"[Cинтаксическая] Ошибочный оператор"),
		ERROR_ENTRY(602,"[Cинтаксическая] Ошибка в выражении"),
		ERROR_ENTRY(603,"[Cинтаксическая] Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"[Cинтаксическая] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605,"[Cинтаксическая] Ошибочное определение логического условия"),
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