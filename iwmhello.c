//------------------------------------------------------------------------------
#define   IWM_COPYRIGHT       "(C)2024 iwm-iwama"
#define   IWM_VERSION         "iwmhello_20240226"
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
	///P("-- %.3fsec\n\n", iExecSec_next());

	///
	idebug_map(); ifree_all(); idebug_map();

	// 最終処理
	imain_end();
}

VOID
print_version()
{
	P1(IESC_STR2);
	LN(80);
	P(
		" %s\n"
		"    %s+%s\n"
		,
		IWM_COPYRIGHT,
		IWM_VERSION,
		LIB_IWMUTIL_VERSION
	);
	LN(80);
	P1(IESC_RESET);
}

VOID
print_help()
{
	MS *_cmd = "iwmhello.exe";

	print_version();
	P(
		IESC_TITLE1	" サンプル "	IESC_RESET	"\n\n"
		IESC_STR1	"   %s"
		IESC_OPT1	" [STR]"
		IESC_OPT2	" [Option]\n\n\n"
		IESC_LBL1	" (例)\n"
		IESC_STR1	"    %s"
		IESC_OPT1	" \"Hello\\n\""
		IESC_OPT2	" -sleep=2000"
		IESC_OPT1	" \"World!\""
		IESC_OPT2	" -sleep=500\n\n\n"
		,
		_cmd,
		_cmd
	);
	P1(
		IESC_OPT2	" [Option]\n"
		IESC_OPT21	"    -sleep=NUM | -s=NUM\n"
		IESC_STR1	"        NUMミリ秒停止\n\n"
	);
	P1(IESC_STR2);
	LN(80);
	P1(IESC_RESET);
}
