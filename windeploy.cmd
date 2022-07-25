
@set DISTR_DIR="D:\distrib\gtss"
@set QML_DIR=%~dp0 

"D:\Qt\6.3.1\mingw_64\bin\windeployqt.exe" --verbose 1 --compiler-runtime  --qmldir %QML_DIR%  --no-system-d3d-compiler --no-virtualkeyboard  --dir %DISTR_DIR% app_poligon.exe


