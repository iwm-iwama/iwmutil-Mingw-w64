:: Ini ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	@echo off
	cd %~dp0
	%~d0
	cls
	::
	:: ファイル名はソースと同じ
	::
	set fn=%~n0
	set src=%fn%.c
	set exec=%fn%.exe
	set lib=lib_iwmutil.a
	set option=-Os -lgdi32 -luser32 -lshlwapi

:: Make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	echo --- Compile -S ------------------------------------
	for %%s in (%src%) do (
		gcc.exe %%s -S %option%
		echo %%~ns.s
	)
	echo.

	echo --- Make ------------------------------------------
	for %%s in (%src%) do (
		gcc.exe %%s -g -c -Wall %option%
		objdump -S -d %%~ns.o > %%~ns.objdump.txt
	)
	gcc.exe *.o %lib% -o %exec% %option%
	echo %exec%

	:: 後処理
	strip -s %exec%
	rm *.o

	:: 失敗
	if not exist "%exec%" goto end

	:: 成功
	echo.
	pause

:: Test ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	cls
	set tm1=%time%
	echo [%tm1%]

	set s="Hello, World!"

	%exec%
	%exec% %s% -sleep=1000

	echo [%tm1%]
	echo [%time%]

:: Quit ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:end
	echo.
	pause
	exit
0