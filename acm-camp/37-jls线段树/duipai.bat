:loop
data.exe > in.txt  
baoli.exe < in.txt > baoli.txt  
tplt.exe < in.txt > ans.txt 
fc /A baoli.txt ans.txt
if not errorlevel 1 goto loop
pause
:end