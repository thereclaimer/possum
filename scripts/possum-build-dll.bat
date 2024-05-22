
::renderer
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\library\\possum-win32.cpp /Fd: bin\\Possum.pdb /Fo: bin\\Possum.obj /Fe: bin\\Possum.dll /link user32.lib
