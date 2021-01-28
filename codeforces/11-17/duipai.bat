:loop
data.exe > in.txt  
E_baoli.exe < in.txt > baoli.txt  
E.exe < in.txt > ans.txt 
fc /A baoli.txt ans.txt
if not errorlevel 1 goto loop
pause
:end