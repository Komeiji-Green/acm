:loop
data.exe > in.txt  
K.exe < in.txt > ans.txt  
K-baoli.exe < in.txt > baoli.txt 
fc /A ans.txt baoli.txt
if not errorlevel 1 goto loop
pause
:end