# libgeoda_static
static library of libgeoda


# Compileing instructions:

## libgeoda for R on Windows using Mingw-32/64

Install R devtools for windows:  <https://www.r-project.org/nosvn/pandoc/devtools.html>

### MingW

Add the paths of mingw and rtools to system environment:

* for mingw-32
```
c:\Rtools\mingw_32/64\bin
c:\Rtools\bin
```

* for mingw-64
```
c:\Rtools\mingw_64\bin
c:\Rtools\bin
```

### Compile libgeoda using cmake

Using Vs code (optional)

* for i386 build
Change the Cmakefile.txt line: set (DEP_OS_SUB "i386")
```
elseif (MINGW)
    # i386 or x64
    set (DEP_OS_SUB "i386")
```

Choose Release build

GCC for Rtool mingw32 
  * C = C:\Rtools\mingw_32\bin\gcc.exe
  * C++  = C:\Rtools\mingw_32\bin\g++.exe
  
Target: geoda

* for x64 build
Change the Cmakefile.txt line: set (DEP_OS_SUB "x64")
```
elseif (MINGW)
    # i386 or x64
    set (DEP_OS_SUB "x64")
```

Choose Release build

GCC for Rtool mingw64 
  * C = C:\Rtools\mingw_64\bin\gcc.exe
  * C++  = C:\Rtools\mingw_64\bin\g++.exe
  
Target: geoda


If compiled successfully, you will see the libgeoda.a under 3rd_party/libgeoda_static/lib/x64 and  3rd_party/libgeoda_static/lib/i386

Commit the new libraries and header files to `rgeoda/libgeoda_static` repo.



