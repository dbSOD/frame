REM  清理项目垃圾文件 //
del *.sdf  *.log *.user  *.ipch *.aps  /s
del *.exe *.dll /s
del *.sdf /s
del *.ilk *.pdb *.exp *.lib *.tlog *.manifest *.res *.lastbuildstate /s
del *.obj *.pch *.idb  /s
del *.suo /s /a h 
pause 

REM 项目配置信息在里边 *.filters 文件夹