:loop
data.exe > in.txt  
dsu-kcjh.exe < in.txt > kcjh.txt  
dsu-chehui.exe < in.txt > chehui.txt 
fc /A kcjh.txt chehui.txt
if not errorlevel 1 goto loop
pause
:end