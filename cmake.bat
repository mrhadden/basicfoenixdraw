@echo off

REM REMOVE THIS LINE IF YOU HAVE TROUBLE WITH JAVA OR CHANGE IT
SET JAVA_HOME=

SET BUILD=Y
SET VERBOSE=
SET TRANSFER=
SET CLEAN=

set argCount=0
for %%x in (%*) do (
   set /A argCount+=1
)


REM IF %argCount% == 0 GOTO usage

for %%x in (%*) do (
	IF [%%x] == [-n] SET BUILD=
	IF [%%x] == [-v] SET VERBOSE=Y
	IF [%%x] == [-t] SET TRANSFER=Y
	IF [%%x] == [-c] SET CLEAN=Y
)

IF [%JAVA_HOME%] == [] ( 
SET JAVABIN=java.exe
) else (
SET JAVABIN="%JAVA_HOME%\bin\java.exe"
)

REM set JAVA_HOME=G:\devtools\java\jdk1.8.0_211\jre

SET CCTEMP=%TEMP%
SET WDC_INC_65816=G:\devtools\WDCTools\wdc\Tools\include
SET WDC_INC_6502=G:\devtools\WDCTools\wdc\Tools\include
SET WDC_LIB=G:\devtools\WDCTools\wdc\Tools\lib

SET SREC_DIR=G:\devprojects\c256feonix\tools

SET COMPILER=G:\devtools\WDCTools\wdc\Tools\bin\wdc816cc.exe

SET ASSEMBLER=G:\devtools\WDCTools\wdc\Tools\bin\wdc816AS.exe

SET LINKER=G:\devtools\WDCTools\wdc\Tools\bin\wdcln.exe
SET INCLUDES=-IG:\devprojects\6502
SET OPTIONS=-DUSING_816 -ML -MT -LT -PX -WO -A -BS
SET ASM_OPT=-G -V -L -W
SET LINK_OPT=-C1A0000,1A0000 -D190000,190000 -T -G -B
SET LIBS=-LG:\devtools\WDCTools\wdc\Tools\lib

SET TASSDIR=G:\devprojects\c256feonix\Neo\Kernel-master\
SET CURDIR=%~dp0

IF [%CLEAN%] == [Y] ( 
	del /q srec.out
	del /q myprog.hex
	del /q myprog.s28.hex
	
	del /q *.obj
	del /q *.o
	del /q *.bnk	
	del /q *.sym	
	del /q *.lst
	del /q *.hex
	del /q *.map
	del /q *.bin
)


IF [%VERBOSE%] == [Y] ( 

echo Build Settings:
echo WDC 65816 Includes:%WDC_INC_65816%
echo WDC  6502 Includes:%WDC_INC_6502%
echo WDC LIB:%WDC_LIB%
echo SREC DIR:%SREC_DIR%
echo COMPILER:%COMPILER%
echo ASSEMBLER:%ASSEMBLER%
echo LINKER:%LINKER%
echo INCLUDES:%INCLUDES%
echo OPTIONS:%OPTIONS%
echo LINK OPTIONS:%LINK_OPT%
echo LIBS:%LIBS%
echo TASSDIR:%TASSDIR%
echo CURRENT DIR:%CURDIR%

)

IF [%BUILD%] == [Y] (
del /Q basic.s
%COMPILER% %INCLUDES% %OPTIONS% -Obasic.s basic.c
%ASSEMBLER% -V -l basic.s -o basic.obj

%LINKER% %LINK_OPT% -HB   basic.obj basicentry.obj basicreset.obj -LCL -O myprog.bin
%LINKER% %LINK_OPT% -HM28 basic.obj basicentry.obj basicreset.obj -LCL -O myprog.s28.hex

IF [%VERBOSE%] == [Y] ( 
	srec_cat.exe myprog.s28.hex -output myprog.hex -intel -address-length=3 > srec.out
) else (
	srec_cat.exe myprog.s28.hex -output myprog.hex -intel -address-length=3 > NUL
)

) else (
echo Skipping Build
)

copy /Y *.hex .\dist
copy /Y *.bin .\dist

IF [%TRANSFER%] == [Y] (
c256serial.bat -s28 myprog.hex -p XR21B1411
)
