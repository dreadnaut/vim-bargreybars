bargreybars.dll: bargreybars.c
	cl.exe /LD bargreybars.c Gdi32.lib User32.lib

clean: clean-unused
	del *.dll

clean-unused:
	del *.exp
	del *.lib
	del *.obj

