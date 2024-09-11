# python backup_locales_no_more.py

import os
import shutil

build_dir = os.getcwd()

dot_backup = os.path.join(build_dir, '.backup-locales')
if os.path.isfile(dot_backup):
	try:
		os.remove(dot_backup)
	except OSError: pass
else:
	print(f'backup_locales_no_more.py: "{dot_backup}" not found.')

backup_dir = os.path.join(build_dir, 'backup-locales')
if os.path.isdir(build_dir):
	try:
		shutil.rmtree(backup_dir)
	except OSError: pass
else:
	print(f'backup_locales_no_more.py: "{backup_dir}" not found.')

