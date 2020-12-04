@echo off
del c.exe
del c.o
del c.stackdump
cls
gcc *.c *.h -o c.exe
c.exe
