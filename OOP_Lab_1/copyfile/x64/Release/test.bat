@echo off

echo Hello World > one-line.txt
echo Line 1 > multiline.txt
echo Line 2 >> multiline.txt
type nul > empty.txt
echo 1234567890 > numbers.txt

echo Test 1: Copy empty file
copyfile.exe empty.txt %TEMP%\empty.txt
if errorlevel 1 goto err
fc.exe /w %TEMP%\empty.txt empty.txt > nul
if errorlevel 1 goto err

echo Test 2: Copy single-line file
copyfile.exe one-line.txt %TEMP%\one-line.txt
if errorlevel 1 goto err
fc.exe /w %TEMP%\one-line.txt one-line.txt > nul
if errorlevel 1 goto err

echo Test 3: Copy standard multiline file
copyfile.exe multiline.txt %TEMP%\multiline.txt
if errorlevel 1 goto err
fc.exe /w %TEMP%\multiline.txt multiline.txt > nul
if errorlevel 1 goto err

echo Test 4: Missing arguments
copyfile.exe
if not errorlevel 1 goto err

echo Test 5: Insufficient arguments
copyfile.exe multiline.txt
if not errorlevel 1 goto err

echo Test 6: Copy file with numeric data
copyfile.exe numbers.txt %TEMP%\numbers.txt
if errorlevel 1 goto err
fc.exe /w %TEMP%\numbers.txt numbers.txt > nul
if errorlevel 1 goto err

echo Test 7: Non-existing input file 
copyfile.exe non-existent-file.txt %TEMP%\out.txt
if not errorlevel 1 goto err

echo Test 8: Too many arguments (4 arguments)
copyfile.exe multiline.txt %TEMP%\out.txt extra_arg
if not errorlevel 1 goto err

echo Test 9: Same paths
copyfile.exe multiline.txt multiline.txt
if not errorlevel 1 goto err

echo Test 10: Copying file with spaces in names
echo Space Test > "file with spaces.txt"
copyfile.exe "file with spaces.txt" "%TEMP%\file with spaces.txt"
if errorlevel 1 goto err
fc.exe /w "%TEMP%\file with spaces.txt" "file with spaces.txt" > nul
if errorlevel 1 goto err

del empty.txt one-line.txt multiline.txt numbers.txt "file with spaces.txt"
del %TEMP%\empty.txt %TEMP%\one-line.txt %TEMP%\multiline.txt %TEMP%\numbers.txt %TEMP%\out.txt "%TEMP%\file with spaces.txt" 2> nul

echo All tests passed successfully.
exit /b 0

:err
if exist empty.txt del empty.txt
if exist one-line.txt del one-line.txt
if exist multiline.txt del multiline.txt
if exist numbers.txt del numbers.txt
if exist "file with spaces.txt" del "file with spaces.txt"
echo Program testing failed
exit /b 1