@echo off
ml.exe /c /Zi in.txt.asm
link.exe /LTCG  /OPT:NOREF /DEBUG /SUBSYSTEM:CONSOLE  in.txt.obj userlib.lib 
ASM.exe
pause 
TASKKILL /IM cmd.exe