:loop
data.exe > in.txt  
C.exe < in.txt > C.txt  
C-baoli.exe < in.txt > C-baoli.txt 
fc /A C.txt C-baoli.txt
if not errorlevel 1 goto loop
pause
:end