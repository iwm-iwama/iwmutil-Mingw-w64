:: Ini ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	@echo off
	cls

	:: ファイル名はソースと同じ
	set fn=%~n0
	set src=%fn%.c
	set cc=gcc.exe

	:: 汎用指向のコードでは -Os で十分
	set option=-Os -Wall -Wextra

	:: 補足
	::   オプション -fanalyzer のとき、
	::       warning: leak of 'ai' [CWE-401] [-Wanalyzer-malloc-leak]
	::   のような警告が出るが無視してよい。

	if exist %fn%.a (
		cp -f %fn%.a %fn%.a.old
		cp -f %fn%.s %fn%.s.old
		cls
	)

:: Make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

::	echo --- Compile -S ------------------------------------
::	%cc% %src% -S %option%
::	echo %fn%.s
::	echo.

	echo --- Make ------------------------------------------
	%cc% %src% -g -c %option%
::	objdump -S -d %fn%.o > %fn%.objdump.txt
	ar rv %fn%.a %fn%.o
	strip -S %fn%.a
	rm -f %fn%.o
	echo %fn%.a
	echo.

:: Quit ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:end
	dir /od %fn%.a %fn%.a.old
	echo.
	pause
	exit
