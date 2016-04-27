@echo off

if %1.==. goto end

echo Reinstalling %1...
rm -r             ..\%1
mkdir             ..\%1
copy buttons.map  ..\%1>nul
copy default.htm  ..\%1>nul
copy mapfail.htm  ..\%1>nul
copy windows.htm  ..\%1>nul
copy testssi.ssi  ..\%1>nul
copy testssi.inc  ..\%1>nul

mkdir             ..\%1\images
copy buttons.gif  ..\%1\images>nul
copy im0096c.gif  ..\%1\images>nul
copy xitami1.gif  ..\%1\images>nul
copy powered1.gif ..\%1\images>nul
copy powered2.gif ..\%1\images>nul
copy powered3.gif ..\%1\images>nul
copy powered4.gif ..\%1\images>nul
copy powered5.gif ..\%1\images>nul

mkdir             ..\%1\xitami
copy index*.htm   ..\%1\xitami>nul
copy license.htm  ..\%1\xitami>nul

mkdir             ..\%1\private
copy private.htm  ..\%1\private>nul

:end
