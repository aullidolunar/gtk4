# python backup_locales.py "po_dir"

import os
import sys
import glob
import shutil
import datetime

po_dir = sys.argv[1]
build_dir = os.getcwd()
backup_dir = os.path.join(build_dir, 'backup-locales')

if not os.path.exists(backup_dir):
	os.makedirs(backup_dir)

with open('.backup-locales', "w") as d:
	d.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n\n'.format(datetime.datetime.now()))
	for po_file in glob.glob(po_dir + '/*.po'):
		shutil.copy2(po_file, backup_dir)
		og = os.path.join(po_dir, po_file)
		bp = os.path.join(build_dir, os.path.basename(po_file))
		d.write(f'Original: {og}\n')
		d.write(f'Backup: {bp}\n\n')

