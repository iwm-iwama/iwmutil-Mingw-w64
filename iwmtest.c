//------------------------------------------------------------------------------
#define  IWM_VERSION         "iwmtest_20220312"
#define  IWM_COPYRIGHT       "Copyright (C)2022 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil.h"

INT
main()
{
	//---------------------
	// lib_iwmutil 初期化
	//---------------------
	iExecSec_init();  //=> $ExecSecBgn
	iCLI_getARGV();   //=> $CMD, $ARGV, $ARGC
	iConsole_EscOn();

	LN();
	P22("$CMD:  ", $CMD);
	P23("$ARGC: ", $ARGC);
	P0("$ARGV:");
	for(INT _i1 = 0; _i1 < $ARGC; _i1++)
	{
		P(" [%d]%s", _i1, $ARGV[_i1]);
	}
	NL();

	//-------------
	// RGB カラー
	//-------------
	LN();
	for(INT _i1 = 0; _i1 < 10; _i1++)
	{
		MT_init(TRUE);
		for(INT _i2 = 0; _i2 < 10; _i2++)
		{
			P("\033[48;2;%d;%d;%dm", MT_irand_INT(0, 255), MT_irand_INT(0, 255), MT_irand_INT(0, 255));
			P("  ");
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
			P("\033[38;2;%d;%d;%dm", MT_irand_INT(0, 255), MT_irand_INT(0, 255), MT_irand_INT(0, 255));
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
	P2("[INT]");
	P23("(MAX)\t", INT_MAX);
	P23("(MIN)\t", INT_MIN);
	LN();
	P2("[UINT]");
	P23("(MAX)\t", UINT_MAX);
	P23("(MIN)\t", 0);
	LN();
	P2("[INT64]");
	P23("(MAX)\t", _I64_MAX);
	P23("(MIN)\t", _I64_MIN);
	LN();
	P2("[DOUBLE]");
	P24("(MAX)\t", DBL_MAX);
	P24("(MIN)\t", -DBL_MAX);
	LN();
/*
	P2("[long double]");
	P24("(MAX)\t", LDBL_MAX);
	P24("(MIN)\t", -LDBL_MAX);
	LN();
*/
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
