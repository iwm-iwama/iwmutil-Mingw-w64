:: Ini ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	@echo off
	cd %~dp0
	%~d0
	cls

	:: �t�@�C�����̓\�[�X�Ɠ���
	set fn=%~n0
	set fn_exe=%fn%.exe
	set cc=gcc.exe
	set op_link=-Os -lgdi32 -luser32 -lshlwapi -lpsapi
	set src=%fn%.c
	set lib=lib_iwmutil.a lib_iwmutil_stack.a

:: Make ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	echo --- Compile -S ------------------------------------
	for %%s in (%src%) do (
		%cc% %%s -S %op_link%
		echo %%~ns.s
	)
	echo.

	:: Make
	echo --- Make ------------------------------------------
	for %%s in (%src%) do (
		echo %%s
		%cc% %%s -c -Wall %op_link%
	)
	%cc% *.o %lib% -o %fn_exe% %op_link%
	echo.

	:: �㏈��
	strip %fn_exe%
	rm *.o

	:: ���s
	if not exist "%fn_exe%" goto end

	:: ����
	echo.
	pause

:: Test ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	cls
	set t=%time%
	echo [%t%]

	%fn%.exe "����1" "����2" "����3"

	echo [%t%]
	echo [%time%]

:: Quit ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:end
	echo.
	pause
	exit