### IMPORTANTE ###

Este projeto esta com a linkagem das libraries e src de GLFW, GLAD, e STB da seguinte forma:

"C:\GL\glad\include"
"C:\GL\glad\src"

"C:\GLFW\glfw-3.4.bin.WIN64\include"
"C:\GLFW\glfw-3.4.bin.WIN64\lib-vc2022'

DENTRO DO LINKER:

glfw3.lib
opengl32.lib
user32.lib
gdi32.lib
shell32.lib

POR FIM 

stb_image.h e futuros headers serao colocados em "C:\GL\glad\include" (o stb estara presente no repositorio)
