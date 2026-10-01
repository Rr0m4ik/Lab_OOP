@echo off

echo Test 1: Basic argument mode 
calcbits.exe 5 > out.txt
if errorlevel 1 goto err
findstr /R "^2$" out.txt > nul
if errorlevel 1 goto err

echo Test 2: Border value 0
calcbits.exe 0 > out.txt
if errorlevel 1 goto err
findstr /R "^0$" out.txt > nul
if errorlevel 1 goto err

echo Test 3: Border value 255
calcbits.exe 255 > out.txt
if errorlevel 1 goto err
findstr /R "^8$" out.txt > nul
if errorlevel 1 goto err

echo Test 4: Help option 
calcbits.exe -h > out.txt
if errorlevel 1 goto err
findstr /C:"Usage:" out.txt > nul
if errorlevel 1 goto err

echo Test 5: Invalid argument string 
calcbits.exe abc > out.txt
if not errorlevel 1 goto err
findstr /C:"Invalid argument" out.txt > nul
if errorlevel 1 goto err

echo Test 6: Argument out of bounds 
calcbits.exe 256 > out.txt
if not errorlevel 1 goto err
findstr /C:"Invalid argument" out.txt > nul
if errorlevel 1 goto err

echo Test 7: Too many arguments 
calcbits.exe 5 10 > out.txt
if not errorlevel 1 goto err
findstr /C:"Invalid argument" out.txt > nul
if errorlevel 1 goto err

echo Test 8: Stdin mode valid data 
echo 5 | calcbits.exe > out.txt
if errorlevel 1 goto err
findstr /R "^2$" out.txt > nul
if errorlevel 1 goto err

echo Test 9: Stdin mode invalid data string 
echo abc | calcbits.exe > out.txt
if errorlevel 1 goto err
findstr /C:"Invalid argument" out.txt > nul
if errorlevel 1 goto err

echo Test 10: Stdin mode boundary violation 300 
echo 300 | calcbits.exe > out.txt
if errorlevel 1 goto err
findstr /C:"Invalid argument" out.txt > nul
if errorlevel 1 goto err

del out.txt

echo All tests passed successfully.
exit /b 0

:err
if exist out.txt del out.txt
echo Program testing failed
exit /b 1