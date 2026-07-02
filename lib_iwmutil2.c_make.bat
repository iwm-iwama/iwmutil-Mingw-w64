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
set cc=gcc.exe -std=c23
set op_link=-O2 -Wall -Wextra

::-----------------------------------------------------------------------------
:: 事前処理
::-----------------------------------------------------------------------------
:R00
:: C++
	echo --- Syntax check for g++ ------------------------------------
	for %%s in (%src%) do (
		g++.exe -fsyntax-only -std=c++23 %%s %op_link%
	)
	echo.
:R09

::-----------------------------------------------------------------------------
:: 本処理
::-----------------------------------------------------------------------------
:R10
:: Assembler
	if exist "%fn%_old.s" (
		rm "%fn%_old.s"
	)
	if exist "%fn%.s" (
		mv "%fn%.s" "%fn%_old.s"
	)
	for %%s in (%src%) do (
		%cc% %%s -S %op_link%
	)
	echo --- -S ------------------------------------------------------
	ls -la %fn%.s
	echo.

:R20
:: Make
	echo --- Make ----------------------------------------------------
	%cc% %src% %op_link% -g -c
	cp -f %fn_a% %fn_a%.old
	ar rv %fn_a% %fn%.o
	strip -S %fn_a%
	rm -f %fn%.o
	ls -la %fn%.a
	echo.

goto R90
:R30
:: Dump
	if exist "%fn%.objdump.old" (
		rm "%fn%.objdump.old"
	)
	if exist "%fn%.objdump" (
		mv "%fn%.objdump" "%fn%.objdump.old"
	)
	echo --- Dump ----------------------------------------------------
	objdump -d -s %fn_a% > %fn%.objdump
	ls -la %fn%.objdump
	echo.

::-----------------------------------------------------------------------------
:: 終処理
::-----------------------------------------------------------------------------
:R90
:R99
:: Quit
	echo.
	pause
	exit
