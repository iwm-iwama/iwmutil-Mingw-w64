//------------------------------------------------------------------------------
#define   IWM_COPYRIGHT       "(C)2025 iwm-iwama"
#define   IWM_FILENAME        "iwmhello"
#define   IWM_UPDATE          "20250324"
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

	///
	iCLI_VarList();

	// -h | --help
	if(! $ARGC || iCLI_getOptMatch(0, L"-h", L"--help"))
	{
		print_version();
		print_help();
		imain_end();
	}

	// -v | --version
	if(iCLI_getOptMatch(0, L"-v", L"--version"))
	{
		print_version();
		imain_end();
	}

	WS *wp1 = 0;
	WS *wp2 = 0;

	for(UINT _u1 = 0; _u1 < $ARGC; _u1++)
	{
		// -s | -sleep
		if((wp1 = iCLI_getOptValue(_u1, L"-s=", L"-sleep=")))
		{
			Sleep(_wtoi(wp1));
		}
		// print
		else
		{
			wp2 = iws_cnv_escape($ARGV[_u1]);
				P1W(wp2);
			ifree(wp2);
		}
	}
	NL();

	// 処理時間
	///
	P("-- %.3fsec\n\n", iExecSec_next());

	// Debug
	///
	idebug_map();
	ifree_all();
	idebug_map();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	P1(IESC_STR2);
	LN(60);
	P1(
		"\033[2G"	IWM_COPYRIGHT	"\n"
		"\033[5G"	IWM_FILENAME	"_"	IWM_UPDATE	" + "	LIB_IWMUTIL_FILENAME	"\n"
	);
	LN(60);
	P1(IESC_RESET);
}

VOID
print_help()
{
	P1(
		"\033[1G"	IESC_TITLE1 " サンプル "	IESC_RESET	"\n"
		"\n"
		"\033[5G"	IESC_STR1	IWM_FILENAME	IESC_OPT1	" [STR]"	IESC_OPT2	" [Option]"	"\n"
		"\n"
		"\033[2G"	IESC_LBL1	"(例)"	"\n"
		"\033[5G"	IESC_STR1	IWM_FILENAME	IESC_OPT1	" \"Hello\\n\""	IESC_OPT2	" -sleep=2000"	IESC_OPT1	" \"World!\""	IESC_OPT2	" -sleep=500"	"\n"
		"\n"
		"\033[2G"	IESC_OPT2	"[Option]"	"\n"
		"\033[5G"	IESC_OPT21	"-sleep=NUM | -s=NUM"	"\n"
		"\033[9G"	IESC_STR1	"NUMミリ秒停止"	"\n"
		"\n"
	);
	P1(IESC_STR2);
	LN(60);
	P1(IESC_RESET);
}
