:loop
data.exe > in.txt  
baoli.exe < in.txt > baoli.txt  
B.exe < in.txt > B.txt 
fc /A baoli.txt B.txt
if not errorlevel 1 goto loop
pause
:end