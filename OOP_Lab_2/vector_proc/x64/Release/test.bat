@echo off

echo Test 1: Standard 
echo 1.0 2 3.659512 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"3.220 4.220 5.879" out.txt > nul
if errorlevel 1 goto err

echo Test 2: with negative number
echo 4 16 -30 10 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"-20.000 14.000 20.000 26.000" out.txt > nul
if errorlevel 1 goto err

echo Test 3: all negative numbers
echo -1.0004000 -703 -3.659512 -11 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"-703.000 -11.000 -3.660 -1.000" out.txt > nul
if errorlevel 1 goto err

echo Test 4: invalid character error handling
echo - 2 3 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"ERROR" out.txt > nul
if errorlevel 1 goto err

echo Test 5: input handling 
echo. | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"ERROR" out.txt > nul
if not errorlevel 1 goto err

echo Test 6: Text characters 
echo 1.5 abc 3.4 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"ERROR" out.txt > nul
if errorlevel 1 goto err

echo Test 7: Multi-line and tab separation format check
(
echo 2.0
echo 4.0	6.0
) | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"6.000 8.000 10.000" out.txt > nul
if errorlevel 1 goto err

echo Test 8: Single positive number processing
echo 5.5 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"11.000" out.txt > nul
if errorlevel 1 goto err

echo Test 9: Zero value 
echo 0 2 4 | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"3.000 5.000 7.000" out.txt > nul
if errorlevel 1 goto err

echo Test 10: multiple spaces 
echo   10.0       20.0   | vector_proc.exe > out.txt
if errorlevel 1 goto err
findstr /C:"25.000 35.000" out.txt > nul
if errorlevel 1 goto err

del out.txt

echo All tests passed successfully.
exit /b 0

:err
if exist out.txt del out.txt
echo Program testing failed
exit /b 1