:loop
data.exe > in.txt  
std.exe < in.txt > std.txt  
baoli.exe < in.txt > baoli.txt 
fc /A std.txt baoli.txt
if not errorlevel 1 goto loop
pause
:end