@ECHO OFF

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

cl.exe .\main.cpp Mf.lib Mfplat.lib mfuuid.lib mfplay.lib mfreadwrite.lib wmcodecdspuuid.lib ole32.lib

:: cmake.exe -DCMAKE_BUILD_TYPE=Debug ninja.exe -G Ninja -S D:\Coding\LoginSnapshot -B D:\Coding\LoginSnapshot\cmake-build-debug-visual-studio
:: add_executable(LoginSnapshot main.cpp utility.h)
:: target_link_libraries(LoginSnapshot Mf.lib)
:: target_link_libraries(LoginSnapshot Mfplat.lib)
:: target_link_libraries(LoginSnapshot mfuuid.lib)
::
:: target_link_libraries(LoginSnapshot mf.lib)
:: target_link_libraries(LoginSnapshot mfplat.lib)
:: target_link_libraries(LoginSnapshot mfplay.lib)
:: target_link_libraries(LoginSnapshot mfreadwrite.lib)
:: target_link_libraries(LoginSnapshot mfuuid.lib)
:: target_link_libraries(LoginSnapshot wmcodecdspuuid.lib)
