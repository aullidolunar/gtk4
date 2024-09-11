# python init-locales.py  "outdir_po" "dummy_pofile"

import os
import sys
import shutil
import datetime

def initlocales(carpeta_respaldo, outdir_po, dummy_pofile):
	
	po_filename = os.path.basename(dummy_pofile)
	
	if os.path.exists(carpeta_respaldo):
		po_lookup = os.path.join(carpeta_respaldo, po_filename)
		if os.path.exists(po_lookup):
			shutil.copy2(po_lookup, outdir_po)
	else:
		po_lookup = os.path.join(outdir_po, po_filename)
		with open(po_lookup, 'w+') as p: pass
	
	with open(po_lookup, 'w+') as p: pass
	with open(dummy_pofile, 'w+') as d:
		d.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n'.format(datetime.datetime.now()))
		d.write(f'Stored: {po_lookup}\n')

outdir_po = sys.argv[1]
dummy_pofile = sys.argv[2]

initlocales('backup-locales', outdir_po, dummy_pofile)