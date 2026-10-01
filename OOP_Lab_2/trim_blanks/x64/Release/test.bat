@echo off

echo Test 1: Standard 
echo hello| trim_blanks.exe > out1.txt
if errorlevel 1 goto err
findstr /R "^hello$" out1.txt > nul
if errorlevel 1 goto err

echo Test 2: Blanks on left
echo  hello| trim_blanks.exe > out2.txt
if errorlevel 1 goto err
findstr /R "^hello$" out2.txt > nul
if errorlevel 1 goto err

echo Test 3: Blanks on both sides
echo  hello | trim_blanks.exe > out3.txt
if errorlevel 1 goto err
findstr /R "^hello$" out3.txt > nul
if errorlevel 1 goto err

echo Test 4: Blanks on right 
echo hello   | trim_blanks.exe > out4.txt
if errorlevel 1 goto err
findstr /R "^hello$" out4.txt > nul
if errorlevel 1 goto err

echo Test 5: Internal blanks 
echo hello   world| trim_blanks.exe > out5.txt
if errorlevel 1 goto err
findstr /R "^hello   world$" out5.txt > nul
if errorlevel 1 goto err

echo Test 6: String with only spaces 
echo        | trim_blanks.exe > out6.txt
if errorlevel 1 goto err
findstr /R "[^  ]" out6.txt > nul
if not errorlevel 1 goto err

echo Test 7: Empty string input 
echo.| trim_blanks.exe > out7.txt
if errorlevel 1 goto err
findstr /R "[^  ]" out7.txt > nul
if not errorlevel 1 goto err

echo Test 8: Multiple lines 
(
echo   first line  
echo     second line
) | trim_blanks.exe > out8.txt
if errorlevel 1 goto err
findstr /C:"first line" out8.txt > nul
if errorlevel 1 goto err
findstr /C:"second line" out8.txt > nul
if errorlevel 1 goto err

echo Test 9: Handling tabulations 
echo 	hello	| trim_blanks.exe > out9.txt
if errorlevel 1 goto err
findstr /R "^hello$" out9.txt > nul
if errorlevel 1 goto err

echo Test 10: Numbers and special chars 
echo   123-abc #!   | trim_blanks.exe > out10.txt
if errorlevel 1 goto err
findstr /R "^123-abc #!$" out10.txt > nul
if errorlevel 1 goto err

echo All tests passed successfully.
exit /b 0

:err
echo Program testing failed
exit /b 1
