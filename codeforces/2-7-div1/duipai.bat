:loop
data.exe > in.txt  
C.exe < in.txt > C-ans.txt  
baoli.exe < in.txt > C-baoli.txt 
fc /A C-ans.txt C-baoli.txt
if not errorlevel 1 goto loop
pause
:end