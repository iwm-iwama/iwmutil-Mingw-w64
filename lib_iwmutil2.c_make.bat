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

::-----------------------------------------------------------------------------
:: 事前処理
::-----------------------------------------------------------------------------
:: C++
:R00
	echo --- Syntax check for g++ ------------------------------------
	for %%s in (%src%) do (
		g++.exe -fsyntax-only -std=c++23 %%s %op_link%
	)
	echo.
:R09

::-----------------------------------------------------------------------------
:: 本処理
::-----------------------------------------------------------------------------
:: Assembler
:R10
	if exist "%fn%.s.old" (
		rm "%fn%.s.old"
	)
	if exist "%fn%.s" (
		mv "%fn%.s" "%fn%.s.old"
	)

::	echo --- Compile gcc -S ------------------------------------------
::	for %%s in (%src%) do (
::		%cc% %%s -S %op_link%
::	)
::	ls -la *.s
::	echo.
:R19

:: Make
:R20
	echo --- Make ----------------------------------------------------
	%cc% %src% %op_link% -g -c
	cp -f %fn_a% %fn_a%.old
	ar rv %fn_a% %fn%.o
	strip -S %fn_a%
	rm -f %fn%.o
	ls -la *.a
	ls -la *.a.old
	echo.
:R29

:: Dump
:R30
	if exist "%fn%.objdump.old" (
		rm "%fn%.objdump.old"
	)
	if exist "%fn%.objdump" (
		mv "%fn%.objdump" "%fn%.objdump.old"
	)

::	echo --- Dump ----------------------------------------------------
::	objdump -d -s %fn_a% > %fn%.objdump
::	ls -la *.objdump
::	echo.
:R39

::-----------------------------------------------------------------------------
:: 終処理
::-----------------------------------------------------------------------------
:: Quit
:R99
	echo.
	pause
	exit
