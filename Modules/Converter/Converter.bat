ECHO
pushd "%~dp0" 
FOR %%f IN (In\*.obj) DO (call FileConverter In\%%~nf.obj Converted\%%~nf.s3d)
FOR %%f IN (Converted\*.s3d) DO (CALL DupeRemover Converted\%%~nf.s3d DeDuped\%%~nf.s3d)
FOR %%f IN (DeDuped\*.s3d) DO (CALL Strips DeDuped\%%~nf.s3d Out\%%~nf.s3d)

pause