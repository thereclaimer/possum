
::arena
cl.exe /I dependencies /I src\\include /I src\\examples\\win32\\arena /Zi /Fe: bin\\Possum.Example.Arena.exe src\\examples\\win32\\arena\\possum-example-win32-arena.cpp /Fd: bin\\Possum.Example.Arena.pdb /Fo: bin\\Possum.Example.Arena.obj /link user32.lib bin\\Possum.lib 
