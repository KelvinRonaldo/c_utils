@echo off
del *.exe
del *.o
del *.exe.stackdump
cls
gcc *.c *.h -o c.exe
c.exe
