//------------------------------------------------------------------------------
#define  IWM_VERSION         "iwmhello_20211112"
#define  IWM_COPYRIGHT       "Copyright (C)2021 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil.h"

INT  main();
VOID print_version();
VOID print_help();

// [文字色] + ([背景色] * 16)
//  0 = Black    1 = Navy     2 = Green    3 = Teal
//  4 = Maroon   5 = Purple   6 = Olive    7 = Silver
//  8 = Gray     9 = Blue    10 = Lime    11 = Aqua
// 12 = Red     13 = Fuchsia 14 = Yellow  15 = White

// タイトル
#define  COLOR01             (15 + ( 9 * 16))
// 入力例／注
#define  COLOR11             (15 + (12 * 16))
#define  COLOR12             (13 + ( 0 * 16))
#define  COLOR13             (12 + ( 0 * 16))
// 引数
#define  COLOR21             (14 + ( 0 * 16))
#define  COLOR22             (11 + ( 0 * 16))
// 説明
#define  COLOR91             (15 + ( 0 * 16))
#define  COLOR92             ( 7 + ( 0 * 16))

#define  DATE_FORMAT         "%g%y-%m-%d" // (注)%g付けないと全て正数表示

INT
main()
{
	// lib_iwmutil 初期化
	iCLI_getARGV();      //=> $CMD, $ARGV, $ARGC
	iConsole_getColor(); //=> $ColorDefault, $StdoutHandle
	iExecSec_init();     //=> $ExecSecBgn

	// -h | -help
	if(! $ARGC || iCLI_getOptMatch(0, "-h", "-help"))
	{
		print_help();
		imain_end();
	}

	// -v | -version
	if(iCLI_getOptMatch(0, "-v", "-version"))
	{
		print_version();
		imain_end();
	}

	MBS *p1 = 0;

	for(INT _i1 = 0; _i1 < $ARGC; _i1++)
	{
		// -sleep
		if((p1 = iCLI_getOptValue(_i1, "-sleep=", NULL)))
		{
			Sleep(inum_atoi(p1));
		}
		// print
		else
		{
			P2($ARGV[_i1]);
		}
	}

	// 処理時間
	/// P("-- %.3fsec\n\n", iExecSec_next());

	// Debug
	/// icalloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	PZ(COLOR92, NULL);
	LN();
	P(" %s\n", IWM_COPYRIGHT);
	P("   Ver.%s+%s\n", IWM_VERSION, LIB_IWMUTIL_VERSION);
	LN();
	PZ(-1, NULL);
}

VOID
print_help()
{
	print_version();
	PZ(COLOR01, " サンプル \n\n");
	PZ(COLOR11, " %s [文字列] [オプション] \n\n", $CMD);
	PZ(COLOR12, " (使用例)\n");
	PZ(COLOR91, "   %s \"Hello\" -sleep=2000 \"World!\" -sleep=500\n\n", $CMD);
	PZ(COLOR21, " [オプション]\n");
	PZ(COLOR22, "   -sleep=NUM\n");
	PZ(COLOR91, "       NUMマイクロ秒停止\n\n");
	PZ(COLOR92, NULL);
	LN();
	PZ(-1, NULL);
}
