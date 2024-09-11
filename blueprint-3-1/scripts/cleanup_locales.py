# python cleanup_locales.py "clean_dirs"

import os
import sys
import shutil

clean_dirs = sys.argv[1:]

def op_clean(directorios):
	for nombre in os.listdir(directorios):
		ruta_completa = os.path.join(directorios, nombre)
		if os.path.isdir(ruta_completa):
			try:
				shutil.rmtree(ruta_completa)
			except OSError:
				pass
		elif os.path.isfile(ruta_completa):
			extensiones_validas = ('.po', '.mo')
			if ruta_completa.endswith(extensiones_validas):
				try:
					os.remove(ruta_completa)
				except OSError:
					pass

for clean_dir in clean_dirs:
	op_clean(clean_dir)