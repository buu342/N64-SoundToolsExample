::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                         Sexy Makefile Executor                               ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@echo off
@chcp 1252


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                               Change Here                                    ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

set ROOT=D:\N64\ultra
set ROMFOLDER="D:\Documents and Settings\Lourenço\Desktop\N64\Roms"


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                          Color Function Setup                                ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

cls && color 07
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (set "DEL=%%a")


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                Setup Make                                    ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

call :PainText 09 "Setting up make for the N64"
set gccdir=%ROOT%\gcc
set PATH=%ROOT%\gcc\mipse\bin;%ROOT%\usr\sbin
set gccsw=-mips3 -mgp32 -mfp32 -funsigned-char -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
set GCC_CELF=ON


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                           Cleanup Old Files                                  ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

echo.
echo.
call :PainText 02 "Moving to the compilation directory"
echo.
call :PainText 02 "Cleaning up old files"
echo.
call :PainText 02 "Creating Out Folder"
@mkdir out 2>nul
cd out
del /q *
echo.
call :PainText 02 "Creating Bin Folder"
@mkdir bin 2>nul
cd bin
del /q *
cd..
cd..


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                Run Make                                      ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

echo.
echo.
call :PainText 0C "Running Make"
echo.
make

echo.
call :PainText 0C "Running makemask"
echo.
for /R "%~dp0" %%f in (*.n64) do makemask "%%f"


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                       Move files to output folder                            ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

echo.
call :PainText 02 "Moving Object files"
move /-y *.o "out\bin\" >nul
move /-y *.out "out\bin\" >nul
move /-y *.n64 "out\" >nul
echo.

echo.
call :PainText 0E "Compilation finished!"
echo.


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                       Ask to move file to ROM folder                         ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:choice
set /P c=Move the ROM to the Project64 ROM Folder[Y/N]?
if /I "%c%" EQU "Y" goto :move
if /I "%c%" EQU "N" call :PainText 0E "Done!" & echo. & echo. & pause & exit
goto :choice

:move
for /R "%~dp0out" %%f in (*.n64) do copy /y "%%f" %ROMFOLDER%
call :PainText 0E "Done!"
echo.
echo.
pause
exit


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                Color Function                                ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:PainText
<nul set /p=". ."
<nul set /p "=%DEL%" > "%~2"
\Windows\system32\findstr /v /a:%1 /R "+" "%~2" nul
del "%~2" > nul
<nul set /p=""
goto :eof