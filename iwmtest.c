//------------------------------------------------------------------------------
#define   IWM_VERSION         "iwmtest_20230623"
#define   IWM_COPYRIGHT       "Copyright (C)2023 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil2.h"

VOID
irand_init()
{
	srand((UINT)time(NULL));
}

INT
irand_INT(
	INT min,
	INT max
)
{
	return (min + (INT)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)));
}

INT
main()
{
	//---------------------
	// lib_iwmutil 初期化
	//---------------------
	iExecSec_init();       //=> $ExecSecBgn
	iCLI_getCommandLine(); //=> $CMD, $ARGC, $ARGV
	iConsole_EscOn();

	LN();
	iCLI_VarList();

	//-------------
	// RGB カラー
	//-------------
	LN();
	irand_init();
	for(INT _i1 = 0; _i1 < 10; _i1++)
	{
		for(INT _i2 = 0; _i2 < 10; _i2++)
		{
			P("\033[38;2;%d;%d;%dm%s", irand_INT(0, 255), irand_INT(0, 255), irand_INT(0, 255), "★");
		}
		NL();
	}
	P2("\033[0m");

	//---------
	// 数値型
	//---------
	LN();
	P2("INT");
	P ("  (MAX) %d\n", INT_MAX);
	P ("  (MIN) %d\n", INT_MIN);
	LN();
	P2("UINT");
	P ("  (MAX) %u\n", UINT_MAX);
	P ("  (MIN) %u\n", 0);
	LN();
	P2("INT64");
	P ("  (MAX) %lld\n", _I64_MAX);
	P ("  (MIN) %lld\n", _I64_MIN);
	LN();
	P2("DOUBLE");
	P ("  (MAX) %.8lf\n", DBL_MAX);
	P ("  (MIN) %.8lf\n", -DBL_MAX);
	LN();

	//---------
	// 処理時間
	//---------
	P("-- %.3fsec\n\n", iExecSec_next());

	//---------
	// Debug
	//---------
	icalloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	//---------
	// 最終処理
	//---------
	imain_end();
}
