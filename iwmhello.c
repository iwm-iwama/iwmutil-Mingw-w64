//------------------------------------------------------------------------------
#define   IWM_VERSION         "iwmhello_20210319"
#define   IWM_COPYRIGHT       "Copyright (C)2021 iwm-iwama"
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
#define   COLOR01             (15 + ( 9 * 16))
// 入力例／注
#define   COLOR11             (15 + (12 * 16))
#define   COLOR12             (13 + ( 0 * 16))
#define   COLOR13             (12 + ( 0 * 16))
// 引数
#define   COLOR21             (14 + ( 0 * 16))
#define   COLOR22             (11 + ( 0 * 16))
// 説明
#define   COLOR91             (15 + ( 0 * 16))
#define   COLOR92             ( 7 + ( 0 * 16))

#define   DATE_FORMAT         "%g%y-%m-%d" // (注)%g付けないと全て正数表示

//
// 停止時間
// -sleep=NUM
//
UINT _Sleep = 0;

INT
main()
{
	// lib_iwmutil 初期化
	iCLI_getCmd();       //=> $IWM_Cmd
	iCLI_getCmdOpt();    //=> $IWM_CmdOption, $IWM_CmdOptionSize
	iConsole_getColor(); //=> $IWM_ColorDefault, $IWM_StdoutHandle
	iExecSec_init();     //=> $IWM_ExecSecBgn

	// -h | -help
	if($IWM_CmdOptionSize == 0 || imb_cmpp($IWM_CmdOption[0], "-h") || imb_cmpp($IWM_CmdOption[0], "-help"))
	{
		print_help();
		imain_end();
	}

	// -v | -version
	if(imb_cmpp($IWM_CmdOption[0], "-v") || imb_cmpp($IWM_CmdOption[0], "-version"))
	{
		print_version();
		LN();
		imain_end();
	}

	// Msg
	P("%s", $IWM_CmdOption[0]);

	// Opt
	for(INT _i1 = 1; _i1 < $IWM_CmdOptionSize; _i1++)
	{
		MBS **_as1 = ija_split($IWM_CmdOption[_i1], "=", "\"\"\'\'", FALSE);
		MBS **_as2 = ija_split(_as1[1], ",", "\"\"\'\'", TRUE);

		// -sleep
		if(imb_cmpp(_as1[0], "-sleep"))
		{
			_Sleep = inum_atoi(_as2[0]);
		}

		ifree(_as2);
		ifree(_as1);
	}

	Sleep(_Sleep);
	NL();

	// 処理時間
	P("-- %.3fsec\n\n", iExecSec_next());

	// Debug
	icalloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	LN();
	P (" %s\n", IWM_COPYRIGHT);
	P ("   Ver.%s+%s\n", IWM_VERSION, LIB_IWMUTIL_VERSION);
	LN();
}

VOID
print_help()
{
	PZ(COLOR92, NULL);
		print_version();
	PZ(COLOR01, " サンプル \n\n");
	PZ(COLOR11, " %s [文字列] [オプション] \n\n", $IWM_Cmd);
	PZ(COLOR12, " (使用例)\n");
	PZ(COLOR91, "   %s \"Hello World!\" -sleep=5000\n\n", $IWM_Cmd);
	PZ(COLOR21, " [オプション]\n");
	PZ(COLOR22, "   -sleep=NUM\n");
	PZ(COLOR91, "       NUMマイクロ秒停止\n\n");
	PZ(COLOR92, NULL);
		LN();
	PZ(-1, NULL);
}
