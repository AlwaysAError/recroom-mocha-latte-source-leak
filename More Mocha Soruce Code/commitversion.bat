@echo off
cd %1
git rev-parse --short HEAD > temp.txt
set /p SHORT_HASH=<temp.txt
echo #define GIT_COMMIT_HASH %SHORT_HASH% > version.h
del temp.txt