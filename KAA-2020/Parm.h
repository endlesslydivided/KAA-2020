#pragma once

#define PARM_IN		L"-in:"
#define	PARM_OUT	L"-out:"
#define	PARM_LOG	L"-log:"
#define	PARM_MAX_SIZE	300
#define	PARM_OUT_DEFAULT_EXIT	L".asm"
#define	PARM_LOG_DEFAULT_EXIT	L".log"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
		bool printPath = false;
		bool printPN = false;
		bool print—T = false;
	};
	PARM getparm(int argc, wchar_t* argv[]);
}