@echo off

set "back=%~dp0"

for /F "delims=" %%i in ('dir /s /b Makefile') do (
	cd "%%~dpi"
	make all
)

cd "%back%"