@echo off
cd %~dp0
%~d0
cls

set fn=%~n0
set cc=gcc.exe
set op_link=-Os -lgdi32 -luser32 -lshlwapi

if exist %fn%.a (
	cp -f %fn%.a %fn%.a.old
	cls
)

set src=%fn%.c

:: make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	echo --- Compile -S -----------------------------------
		for %%s in (%src%) do (
		%cc% %%s -S
		wc -l %%~ns.s
	)
	echo.

	echo --- Make -----------------------------------------
		%cc% %src% -Wall -Wextra %op_link% -c
		ar rv %fn%.a %fn%.o
		strip -S %fn%.a
		rm -f %fn%.o
	echo.

dir /od %fn%.a*
echo.

pause
