@echo off
IF EXIST C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE SET PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE
devenv Rocket3d/Rocket3d.vcxproj  /build
