@echo OFF

call ".\build.bat"
Remove-Item -Recurse -Force images
MkDir images
.\main.exe
ffmpeg -s 640x480 -pix_fmt yuyv422 -i output.yuv images/image-%3d.png
