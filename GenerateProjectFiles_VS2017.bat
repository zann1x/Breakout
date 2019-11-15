@echo off
call ThirdParty\bin\premake5.exe vs2017
if %errorlevel% neq 0 (
  pause
)
