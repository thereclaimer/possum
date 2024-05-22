
::renderer
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\library\\possum.cpp /Fd: bin\\Possum.pdb /Fo: bin\\Possum.obj /Fe: bin\\Possum.dll /link
