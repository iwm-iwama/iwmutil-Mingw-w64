//----------------------------------------------
#define IWM_VERSION   "iwmhello_20191121"
#define IWM_COPYRIGHT "(C)2008-2019 iwm-iwama"
//----------------------------------------------
#include "lib_iwmutil.h"

//-------
// 関数
//-------
VOID version();
VOID help();

//-----------
// 共有変数
//-----------
UINT $execMS   = 0;
MBS  *$program = NULL;
MBS  **$args   = {NULL};
UINT $argsSize = 0;
MBS  *$stdout  = NULL;
INT  $iRepeat  = 0;

INT
main()
{
	// 実行開始時間
	$execMS = iExecSec_init();

	// コマンド名／引数
	$program = iCmdline_getCmd();
	$args = iCmdline_getArgs();
	$argsSize = $IWM_uAryUsed;

	// "-help"
	if($argsSize == 0)
	{
		help();
		imain_end();
	}

	MBS **as1 = {NULL};
	MBS **as2 = {NULL};

	for(INT _i1 = 0; _i1 < $argsSize; _i1++)
	{
		if(_i1 == 0)
		{
			MBS *s1 = $args[0];
		
			// "-help", "-h"
			if(imb_cmpp(s1, "-help") || imb_cmpp(s1, "-h"))
			{
				help();
				imain_end();
			}

			// "-version", "-v"
			if(imb_cmpp(s1, "-version") || imb_cmpp(s1, "-v"))
			{
				version();
				LN();
				imain_end();
			}

			// Stdout
			$stdout = s1;
		}
		else
		{
			// (例) -sleep=5000,sec
			// (例) "=" => {"-sleep", "5000,sec"}
			as1 = ija_split($args[_i1], "=", "", FALSE);
			INT _i11 = $IWM_uAryUsed;

			MBS *sLabel = as1[0];

			for(INT _i2 = 1; _i2 < _i11; _i2++)
			{
				// (例) "," => {"5000", "sec"}
				as2 = ija_split(as1[_i2], ",", "\"\"\'\'", TRUE);

				// "-sleep"
				if(imb_cmpp(sLabel, "-sleep"))
				{
					$iRepeat = inum_atoi(as2[0]);
				}

				ifree(as2);
			}
			ifree(as1);
		}
	}

	P("%s", $stdout);
	Sleep($iRepeat);
	NL();

	// 処理時間
	P("-- %.3fsec\n\n", iExecSec_next($execMS));

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
	LN();
}

VOID
help()
{
	version();
	P2("＜使用法＞");
	P ("  %s [文字列] [オプション]\n", $program);
	NL();
	P2("＜オプション＞");
	P2("  -help, -h");
	P2("      ヘルプ");
	P2("  -version, -v");
	P2("      バージョン情報");
	NL();
	P2("  -sleep=[NUM]");
	P2("      [NUM]マイクロ秒停止");
	NL();
	P2("＜使用例＞");
	P ("  %s \"Hello World!\" -sleep=5000\n", $program);
	LN();
}
