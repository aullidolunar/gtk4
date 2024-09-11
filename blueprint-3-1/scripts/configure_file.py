# python configure_file.py "input_file" "output_file" key value .. ..

import sys

def argumentos_a_diccionario(args):
	if len(args) % 2 != 0:
		raise ValueError("Pair Key value order expected.")

	resultado = {}

	for i in range(0, len(args), 2):
		clave = args[i]
		valor = args[i+1]

		if valor.lower() == "true": valor = True
		elif valor.lower() == "false": valor = False

		resultado[clave] = valor	
	return resultado

def configure_file(input_file, output_file, replacements):
	with open(input_file, 'r') as file:
		filedata = file.read()
	
	for key, value in replacements.items():
		filedata = filedata.replace(f'@{key}@', str(value))
	
	with open(output_file, 'w') as file:
		file.write(filedata)

input_file = sys.argv[1]
output_file = sys.argv[2]

replacements = argumentos_a_diccionario(sys.argv[3:])

configure_file(input_file, output_file, replacements)

print(f"configure_file.py: '{output_file}' was generated from '{input_file}'.")