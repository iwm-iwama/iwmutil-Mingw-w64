@echo off
cd %~dp0
%~d0
cls

set fn=%~n0
set op_link=-Os -lgdi32 -luser32 -lshlwapi

if exist %fn%.a (
	cp -f %fn%.a %fn%.a.old
	cp -f %fn%.s %fn%.s.old
	cls
)

set src=%fn%.c

:: make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	echo --- Compile -S ------------------------------------
		for %%s in (%src%) do (
			gcc.exe %%s -S %op_link%
			wc -l %%~ns.s
		)
	echo.

	echo --- Make ------------------------------------------
		gcc.exe %src% -c -Wall -Wextra %op_link%
		ar rv %fn%.a %fn%.o
		strip -S %fn%.a
		rm -f %fn%.o
	echo.

dir /od %fn%.a
echo.

pause
