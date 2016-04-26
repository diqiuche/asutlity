rem ----------清理文件----------
del /q/a/f/s *.ncb
del /q/a/f/s *.suo
del /q/a/f/s *.user
del /q/a/f/s *.sdf
del /q/a/f/s *.ipch
del /q/a/f/s *.aps
del /q/a/f/s *.ldb
del /q/a/f/s *.db
del /q/a/f/s *.pdb

del /q/a/f/s *.obj
del /q/a/f/s *.exp
del /q/a/f/s *.pch
del /q/a/f/s *.res
del /q/a/f/s *.dep
del /q/a/f/s *.idb
del /q/a/f/s *.embed.manifest
del /q/a/f/s *.intermediate.manifest
del /q/a/f/s *.ilk
del /q/a/f/s *.sbr
del /q/a/f/s *.bsc
del /q/a/f/s *.tli
del /q/a/f/s *.tlh
del /q/a/f/s *.log
del /q/a/f/s BuildLog.htm
del /q/a/f/s captcha.jpeg
del /q/a/f/s cookie.txt



rem ----------清理空文件夹----------
for /f "delims=" %%i in ('dir /s/b/ad ^|sort /r') do rd /q "%%i" 2 > nul