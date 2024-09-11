# python locales_backup.py "backup_dir" "po_files"

import os
import sys
import shutil

def copiar_archivo_a_backup(archivo_origen, carpeta_destino="backup"):
	if os.path.isfile(archivo_origen):
		if not os.path.exists(carpeta_destino):
			os.makedirs(carpeta_destino)

	shutil.copy2(archivo_origen, carpeta_destino)


backup_dir = sys.argv[1]
po_files = sys.argv[2:]
for po_file in po_files:
	copiar_archivo_a_backup(po_file, backup_dir[1:])
	
with open(backup_dir, "w") as d:
	pass
