@echo off
cls

:: "ベースファイル名" + "_make.bat"
set batch=%~nx0
set src=%batch:_make.bat=%
set fn=
for /f "delims=. tokens=1,2" %%i in ("%src%") do (
	set fn=%%i%
)
set fn_a=%fn%.a
set cc=gcc.exe -std=c2x
:::Debug => set cc=g++.exe -std=c++23
set op_link=-Os -Wall -Wextra

:: Assembler
	echo --- Compile -S ------------------------------------
	cp -f %fn%.s %fn%.s.old
	for %%s in (%src%) do (
		%cc% %%s -S %op_link%
		echo %%~ns.s
	)
	echo.

:: Make
	echo --- Make ------------------------------------------
	%cc% %src% %op_link% -g -c
	cp -f %fn_a% %fn_a%.old
	ar rv %fn_a% %fn%.o
	strip -S %fn_a%
	rm -f %fn%.o

:: Dump
::	cp -f %fn%.objdump %fn%.objdump.old
::	objdump -d -s %fn_a% > %fn%.objdump
::	echo.

:: Quit
	dir %fn_a%*
	echo.
	pause
	exit
