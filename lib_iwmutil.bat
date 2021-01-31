@echo off
cd %~dp0
%~d0
cls

set fn=%~n0
set cc=gcc.exe
set option=-Os -Wall -Wextra -Wimplicit-fallthrough=3

if exist %fn%.a (
	cp -f %fn%.a %fn%.a.old
	cp -f %fn%.s %fn%.s.old
	cls
)

set src=%fn%.c

:: make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	echo --- Compile -S ------------------------------------
		for %%s in (%src%) do (
			%cc% %%s -S %option%
			wc -l %%~ns.s
		)
	echo.

	echo --- Make ------------------------------------------
		%cc% %src% -g -c %option%
		objdump -S -d %fn%.o > %fn%.objdump.txt
		ar rv %fn%.a %fn%.o
		strip -S %fn%.a
		rm -f %fn%.o
	echo.

dir /od %fn%.a
echo.

pause
