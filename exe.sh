@Echo off
rm *.exe
rm *.o
rm *.exe.stackdump
clear
gcc *.c *.h -o c.exe
chmod 755 exe.sh
./c.exe
