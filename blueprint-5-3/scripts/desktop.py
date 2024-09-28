# python desktop.py desktop_file_in toolkit_version meson_version desktop_file_out

import sys

def reemplazar_en_archivo(desktop_file_in, toolkit_version, meson_version, desktop_file_out):
	with open(desktop_file_in, 'r') as archivo_original, open(desktop_file_out, 'w') as archivo_nuevo:
		for linea in archivo_original:
			nueva_linea = linea.replace("@0@", toolkit_version, 1).replace("@1@", meson_version, 1)
			archivo_nuevo.write(nueva_linea)

reemplazar_en_archivo(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
