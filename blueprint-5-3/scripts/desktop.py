# python desktop.py file_in "gtk4_ver" "meson_ver" file_out

import sys

def reemplazar_en_archivo(nombre_archivo, gtk4_ver, meson_ver, nuevo_nombre_archivo):
	with open(nombre_archivo, 'r') as archivo_original, open(nuevo_nombre_archivo, 'w') as archivo_nuevo:
		for linea in archivo_original:
			nueva_linea = linea.replace("@0@", gtk4_ver, 1).replace("@1@", meson_ver, 1)
			archivo_nuevo.write(nueva_linea)

reemplazar_en_archivo(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
