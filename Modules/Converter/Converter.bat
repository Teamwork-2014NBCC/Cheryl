ECHO
pushd "%~dp0" 
FOR %%f IN (In\*.obj) DO (call Executables\FileConverter In\%%~nf.obj Converted\%%~nf.s3d)
FOR %%f IN (Converted\*.s3d) DO (CALL Executables\DupeRemover Converted\%%~nf.s3d DeDuped\%%~nf.s3d)
FOR %%f IN (DeDuped\*.s3d) DO (CALL Executables\Strips DeDuped\%%~nf.s3d Out\%%~nf.s3d)

pause