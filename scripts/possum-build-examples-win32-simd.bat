
::simd
cl.exe /I dependencies /I src\\include /I src\\examples\\win32\\math /Zi /Fe: bin\\Possum.Example.Simd.exe src\\examples\\win32\\math\\possum-example-win32-simd.cpp /Fd: bin\\Possum.Example.Simd.pdb /Fo: bin\\Possum.Example.Simd.obj /link user32.lib bin\\Possum.lib 
