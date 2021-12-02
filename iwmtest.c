//------------------------------------------------------------------------------
#define  IWM_VERSION         "iwmtest_20211201"
#define  IWM_COPYRIGHT       "Copyright (C)2021 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil.h"

INT
main()
{
	//---------------------
	// lib_iwmutil 初期化
	//---------------------
	iCLI_getARGV();      //=> $CMD, $ARGV, $ARGC
	iConsole_getColor(); //=> $ColorDefault, $StdoutHandle
	iExecSec_init();     //=> $ExecSecBgn

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
	// ESC カラー
	//-------------
	LN();
	P0("   ");
	for(INT _i1 = 0; _i1 < 16; _i1++)
	{
		P(" %3d ", _i1);
	}
	NL();

	for(INT _i1 = 0; _i1 < 16; _i1++)
	{
		PZ(-1, "%2d ", _i1);
		for(INT _i2 = 0; _i2 < 16; _i2++)
		{
			INT _i3 = _i2 + (_i1 * 16);
			PZ(_i3, " %3d ", _i3);
		}
		NL();
	}
	PZ(-1, "\n");

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
