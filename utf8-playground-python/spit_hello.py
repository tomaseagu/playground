# https://www.charset.org/utf-8

with open('hello.c', 'rb') as f:
    contenido = f.read()
    
    binario_completo = " ".join(f"{b:08b}" for b in contenido)

    print(binario_completo)
    
    print(list(contenido))

# Los caracteres se representan con numeros binarios, los binarios tienen su representación en decimal, Hexadecimal y PointCode.
# Hasta el valor decimal 127 se utiliza 1 byte para representar caracteres
# manteniendo retrocompatibilidad con ASCII que tenia 128 caracteres (del 0 al 127)

# El valor binario del primer caracter "#" es 
# 0 0 1 0 0 0 1 1 
# Siendo sus posiciones:
# 7 6 5 4 3 2 1 0 
# Elevamos a la 2 cada posición:
# 128, 64, 32, 16, 8, 4, 2, 1
# Sumamos solo las posiciones con valor 1
# Y Obtenemos su representación en decimal "35"

# El hexadecimal es un sistema de 16 digitos distintos
# 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F:
# El valor binario del primer caracter "#" es:
# 0 0 1 0 0 0 1 1
# Dividimos el binario en 2 grupos de 4 bits:
# (0 0 1 0) (0 0 1 1)
# Siendo sus posiciones:
# (3 2 1 0) (3 2 1 0)
# Elevamos a la 2 cada posición:
# (8, 4, 2, 1) (8, 4, 2, 1)
# Sumamos solo las posiciones con valor 1 de cada grupo:
# Y Obtenemos su representación en hexadecimal "23"

# El PointCode es un numero unico asignado para representar un caracter o simbolo.
# Hasta el numero 127 utilizamos solo 1 byte para representar caracteres.
# Si bien es cierto que con 1 byte podemos representar hasta 255 numeros, utf-8 utiliza el primer caracter como caracter de control
# Si comienza con 1 tiene retrocompatibilidad con ASCII, si comienza con 0 no. Esto acorta la cantidad de valores que podemos representar con 1 byte.

# Para calcular el PointCode de valores representados con 1 byte
# necesitamos el valor Hexadecimal, para este caso "23" y rellanar con ceros a la izquierda hasta completar 4 caracteres:
# U+0023

# Ejemplo de un simbolo representado con 3 grupos de bytes, dado el hexadecimal:
# EO AO 80
# 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F:
# Calculamos los valores decimales de cada grupo
# E = 14, 0 = 0
# A = 10, 0 = 0
# 8 = 8, 0 = 0
# Obtenemos la repsentacion en binario de cada grupo:

# E0
# 14            0
# (8, 4, 2, 1) (8, 4, 2, 1)
#  1  1  1  0   0  0  0  0 
# Bits de control: 1110 -> soy una secuencia de 3 bytes (el 0 indica no sigas leyendo, 1100 "soy una secuencia de 2 bytes, 0 detente")

# AO
# 10            0
# (8, 4, 2, 1) (8, 4, 2, 1)
#  1  0  1  0   0  0  0  0
# Bits de control: 10 -> soy un bit de continuacion 

# 80
# 8            0
# (8, 4, 2, 1) (8, 4, 2, 1)
#  1  0  0  0   0  0  0  0
# Bits de control: 10 -> soy un bit de continuacion 

# Quitamos los bits de control de cada grupo bytes:
# 0000100000000000
# Eliminamos los ceros de la izquierda:
# 100000000000
# Creamos 3 grupos de 4 bits:
#  1  0  0  0   0  0  0  0   0  0  0  0
# (8, 4, 2, 1) (8, 4, 2, 1) (8, 4, 2, 1)
#  8                0            0
# Su Point Code es U+0800 (rellenamos a la izquierda para completar los 4 digitos)
# Tomamos el binario puro
# 100000000000
# La unica posicion que tiene un 1 es la 11, la elevamos a la 2 
# y obtenemos su representacion en decimmal 20448
