//----------------------------------------------
#define IWM_VERSION   "iwmhello_20190711"
#define IWM_COPYRIGHT "(C)2008-2019 iwm-iwama"
//----------------------------------------------
/*
	include
*/
#include "lib_iwmutil.h"

/*
	関数
*/
VOID version();
VOID help();

/*
	共有変数
*/
MBS  *_program = 0;
UINT _exec_cjd = 0;

INT
main()
{
	// 実行時間
	_exec_cjd = iExecSec_init();

	// コマンド名／引数配列
	_program = iCmdline_getCmd();
	MBS **args = iCmdline_getArgs();

	MBS **ap1 = {0};

	// -help, -h
	ap1 = iargs_option(args, "-help", "-h");
		if($IWM_bSuccess || !**args)
		{
			help();
			imain_end();
		}
	ifree(ap1);

	// -version, -v
	ap1 = iargs_option(args, "-version", "-v");
		if($IWM_bSuccess)
		{
			version();
			LN();
			imain_end();
		}
	ifree(ap1);

	// 本処理
	P8();
		P2(_program);
		NL();
	P8();
		iary_print(args);
		NL();
	P8();
		ap1 = ija_token(*args, ",  ");
			iary_print(ap1);
		ifree(ap1);
		NL();

	// 処理時間
	LN();
	P("-- %.3fsec\n\n", iExecSec_next(_exec_cjd));

	// Debug
	icalloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	// 最終処理
	imain_end();
}

VOID
version()
{
	LN();
	P ("  %s\n", IWM_COPYRIGHT);
	P ("    Ver.%s+%s\n", IWM_VERSION, LIB_IWMUTIL_VERSION);
}

VOID
help()
{
	version();
	LN();
	P2("＜使用法＞");
	P ("  %s [文字列] [オプション]\n", _program);
	NL();
	P2("＜オプション＞");
	P2("  -help, -h");
	P2("      ヘルプ");
	P2("  -version, -v");
	P2("      バージョン情報");
	NL();
	P2("＜使用例＞");
	P ("  %s \"Hello World!\"\n", _program);
	LN();
}
