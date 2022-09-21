//------------------------------------------------------------------------------
#define   IWM_VERSION         "iwmtest_20220912"
#define   IWM_COPYRIGHT       "Copyright (C)2022 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil2.h"

INT
main()
{
	//---------------------
	// lib_iwmutil 初期化
	//---------------------
	iExecSec_init();       //=> $ExecSecBgn
	iCLI_getCommandLine(); //=> $CMD, $ARG, $ARGC, $ARGV
	iConsole_EscOn();

	LN();
	iCLI_VarList();

	//-------------
	// RGB カラー
	//-------------
	LN();
	for(INT _i1 = 0; _i1 < 10; _i1++)
	{
		MT_init(TRUE);
		for(INT _i2 = 0; _i2 < 10; _i2++)
		{
			P("\033[48;2;%lld;%lld;%lldm", MT_irand_INT64(0, 255), MT_irand_INT64(0, 255), MT_irand_INT64(0, 255));
			P("□");
		}
		P2("\033[49m");
		MT_free();
	}
	NL();
	for(INT _i1 = 0; _i1 < 10; _i1++)
	{
		MT_init(TRUE);
		for(INT _i2 = 0; _i2 < 10; _i2++)
		{
			P("\033[38;2;%lld;%lld;%lldm", MT_irand_INT64(0, 255), MT_irand_INT64(0, 255), MT_irand_INT64(0, 255));
			P("★");
		}
		P2("\033[39m");
		MT_free();
	}
	NL();

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
