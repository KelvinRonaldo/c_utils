@echo off
del c.exe
del c.o
del c.stackdump
cls
gcc c.c utils.c utils.h -o c.exe
c.exe
