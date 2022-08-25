@echo off

ver | find "6.0." > nul
if %errorlevel% == 0 goto win7_or_older

set ARCH=%PROCESSOR_ARCHITECTURE%
if [%ARCH%] == [AMD64] set ARCH=x64
:: reg add "HKEY_CLASSES_ROOT\*\shell\Open with MDK D3D11\command" /ve /t REG_SZ /d """"%~dp0bin\glfwplay.exe""" """-logfile""" """%~dp0glfwplay.log"""  """-c:v""" """MFT:d3d=11:pool=1,D3D11,FFmpeg""" """-es""" """-gfxthread""" """%%1"""" /f
:: d3d11 may be not available on win8
reg add "HKEY_CURRENT_USER\SOFTWARE\Classes\*\shell\Open with MDK\command" /ve /t REG_SZ /d """"%~dp0bin\%ARCH%\glfwplay.exe""" """-logfile""" """%~dp0glfwplay.log"""  """-c:v""" """MFT:d3d=11,D3D11,DXVA,NVDEC,FFmpeg""" """-d3d11""" """-gfxthread""" """%%1"""" /f
goto :checkCrt

:win7_or_older
reg add "HKEY_CURRENT_USER\SOFTWARE\Classes\*\shell\Open with MDK\command" /ve /t REG_SZ /d """"%~dp0bin\%ARCH%\glfwplay.exe""" """-logfile""" """%~dp0glfwplay.log"""  """-c:v""" """D3D11,MFT:d3d=9,NVDEC,FFmpeg""" """-d3d11""" """-gfxthread""" """%%1"""" /f
goto :checkCrt

:checkCrt
:: vcruntime140_1.dll is required by x64 for now
if not EXIST "C:\Windows\System32\vcruntime140_1.dll" (
@echo downloading vc and urct runtime %ARCH%...
cscript /nologo %~dp0\get.js https://aka.ms/vs/16/release/VC_redist.%ARCH%.exe vc_redist.%ARCH%.exe
@echo installing vc and urct runtime %ARCH%...
vc_redist.%ARCH%.exe /install /passive
)
goto :end

:end
@echo Right click an video/music file, choose "Open with MDK" to play
call bin\%ARCH%\glfwplay.exe
pause
