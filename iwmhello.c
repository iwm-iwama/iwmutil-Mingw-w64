//------------------------------------------------------------------------------
#define   IWM_VERSION         "iwmhello_20230809"
#define   IWM_COPYRIGHT       "Copyright (C)2023 iwm-iwama"
//------------------------------------------------------------------------------
#include "lib_iwmutil2.h"

INT       main();
VOID      print_version();
VOID      print_help();

INT
main()
{
	// lib_iwmutil2 初期化
	imain_begin();

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

	WS *wp1 = 0;

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
	/// icalloc_mapPrint(); ifree_all(); icalloc_mapPrint();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	P(ICLR_STR2);
	LN(80);
	P(" %s\n", IWM_COPYRIGHT);
	P("    Ver.%s+%s\n", IWM_VERSION, LIB_IWMUTIL_VERSION);
	LN(80);
	P(ICLR_RESET);
}

VOID
print_help()
{
	MS *_cmd = W2M($CMD);

	print_version();
	P("%s サンプル %s\n", ICLR_TITLE1, ICLR_RESET);
	P("%s    %s %s[STR] %s[Option]\n", ICLR_STR1, _cmd, ICLR_OPT1, ICLR_OPT2);
	P("\n");
	P("%s (例)\n", ICLR_LBL1);
	P("%s    %s %s\"Hello\" %s-sleep=2000 %s\"World!\" %s-sleep=500\n", ICLR_STR1, _cmd, ICLR_OPT1, ICLR_OPT2, ICLR_OPT1, ICLR_OPT2);
	P("\n");
	P("%s [Option]\n", ICLR_OPT2);
	P("%s    -sleep=NUM\n", ICLR_OPT21);
	P("%s        NUMマイクロ秒停止\n", ICLR_STR1);
	P("\n");
	P(ICLR_STR2);
	LN(80);
	P(ICLR_RESET);

	ifree(_cmd);
}
