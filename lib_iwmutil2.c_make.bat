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
set op_link=-Os -Wall -Wextra

:: BackUp
	cp -f %fn%.s %fn%.s.old
	cp -f %fn%.objdump %fn%.objdump.old
	cls

:: C++
	echo --- Syntax Check g++ ----------------------------------------
	for %%s in (%src%) do (
		g++.exe -std=c++23 %%s -S %op_link%
	)
	if "%errorlevel%" == "0" (
		echo OK!
	)
	echo.

:: Assembler
	echo --- Compile gcc -S ------------------------------------------
	for %%s in (%src%) do (
		%cc% %%s -S %op_link%
	)
	ls -la *.s
	echo.

:: Make
	echo --- Make ----------------------------------------------------
	%cc% %src% %op_link% -g -c
	cp -f %fn_a% %fn_a%.old
	ar rv %fn_a% %fn%.o
	strip -S %fn_a%
	rm -f %fn%.o
	ls -la *.a
	ls -la *.a.old
	echo.

:: Dump
	echo --- Dump ----------------------------------------------------
	objdump -d -s %fn_a% > %fn%.objdump
	ls -la *.objdump
	echo.

:: Quit
	echo.
	pause
	exit
