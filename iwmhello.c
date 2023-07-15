//------------------------------------------------------------------------------
#define   IWM_VERSION         "iwmhello_20230711"
#define   IWM_COPYRIGHT       "Copyright (C)2023 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil2.h"

INT  main();
VOID print_version();
VOID print_help();

#define   CLR_RESET           "\033[0m"
#define   CLR_TITLE1          "\033[38;2;250;250;250m\033[104m" // 白／青
#define   CLR_OPT1            "\033[38;2;250;150;150m"          // 赤
#define   CLR_OPT2            "\033[38;2;150;150;250m"          // 青
#define   CLR_OPT21           "\033[38;2;80;250;250m"           // 水
#define   CLR_OPT22           "\033[38;2;250;100;250m"          // 紅紫
#define   CLR_LBL1            "\033[38;2;250;250;100m"          // 黄
#define   CLR_LBL2            "\033[38;2;100;100;250m"          // 青
#define   CLR_STR1            "\033[38;2;225;225;225m"          // 白
#define   CLR_STR2            "\033[38;2;175;175;175m"          // 銀

INT
main()
{
	// lib_iwmutil 初期化
	iExecSec_init();       //=> $ExecSecBgn
	iCLI_getCommandLine(); //=> $CMD, $ARGC, $ARGV
	iConsole_EscOn();

	// -h | -help
	if(! $ARGC || iCLI_getOptMatch(0, L"-h", L"--help"))
	{
		print_help();
		imain_end();
	}

	// -v | -version
	if(iCLI_getOptMatch(0, L"-v", L"--version"))
	{
		print_version();
		imain_end();
	}

	WCS *wp1 = 0;

	for(INT _i1 = 0; _i1 < $ARGC; _i1++)
	{
		// -sleep
		if((wp1 = iCLI_getOptValue(_i1, L"-sleep=", NULL)))
		{
			Sleep(_wtoi(wp1));
		}
		// print
		else
		{
			P2W($ARGV[_i1]);
		}
	}
	NL();

	// 処理時間
	/// P("-- %.3fsec\n\n", iExecSec_next());

	// Debug
	/// calloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	P(CLR_STR2);
	LN();
	P(" %s\n", IWM_COPYRIGHT);
	P("    Ver.%s+%s\n", IWM_VERSION, LIB_IWMUTIL_VERSION);
	LN();
	P(CLR_RESET);
}

VOID
print_help()
{
	MBS *_cmd = W2M($CMD);

	print_version();
	P("%s サンプル %s\n", CLR_TITLE1, CLR_RESET);
	P("%s    %s %s[STR] %s[Option]\n", CLR_STR1, _cmd, CLR_OPT1, CLR_OPT2);
	P("\n");
	P("%s (例)\n", CLR_LBL1);
	P("%s    %s %s\"Hello\" %s-sleep=2000 %s\"World!\" %s-sleep=500\n", CLR_STR1, _cmd, CLR_OPT1, CLR_OPT2, CLR_OPT1, CLR_OPT2);
	P("\n");
	P("%s [Option]\n", CLR_OPT2);
	P("%s    -sleep=NUM\n", CLR_OPT21);
	P("%s        NUMマイクロ秒停止\n", CLR_STR1);
	P("\n");
	P(CLR_STR2);
	LN();
	P(CLR_RESET);

	ifree(_cmd);
}
