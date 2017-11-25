MyAWK [Version 1.0.0]
2017 Jose Luis Castro Garcia.
Sintaxis: myawk.exe <archivo-fuente> <comando> <parametros> [archivo-destino]

El comando puede ser algunos de los siguientes:
    S str1 str2		Remplaza la cadena str1 por la cadena str2 a lo largo de todo el archivo.
    SmM			Remplaza todas las letras minusculas por mayusculas.
    SMm			Remplaza todas las letras mayusculas por minusculas.
    Lnd1nd2nd3n...	(n es el separador de digitos) Imprime las lineas indicadas por d1, d2 d3, ...
    Cnd1nd2nd3n...	(n es el separador de digitos) Imprime las columnas indicadas por d1, d2 d3, ...
    ILnd1nd2nd3n...	(n es el separador de digitos) Mete un salto de linea en las lineas indicadas por d1, d2 d3, ...
    ICnd1nd2nd3n...	(n es el separador de digitos) Mete un tabulador las en columnas indicadas por d1, d2 d3, ...
    INC			Imprime una columna indicando el numero de linea de cada renglon.
    CC str		Cuenta e imprime el numero de currencias de la cadena str por linea.
    CP str		Cuenta e imprime el numero de currencias del prefijo str por linea.
    CS str		Cuenta e imprime el numero de currencias del sufijo str por linea.

Notas:
	* El atributo archivo-destino es opcional, si se omite, el archivo del destino sera la salida estandar (comunmente el monitor).
	* Los comandos CC, CP y CS ignoran los signos de puntuación , . ; : - _ ( ) [ ] { } < > ' ¡ ! ¿ ? / " \ asi como los espacion en 
	blanco y las tabulaciones.
	* Si alguno de los atributos del comando S es una cadena, la busqueda se ara entre cadenas, si ambos son solo caracteres, la busqueda
	sera caracter por caracter.
	* El comando S no ignora las tabulaciones y los signos de puntuacion antes mencionados, pero si ignora los saltos de linea.