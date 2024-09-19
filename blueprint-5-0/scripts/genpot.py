# python genpot.py locale_dir sources_list

import os
import sys

locale_dir = sys.argv[1]
sources_list = sys.argv[2:]

project_dir = os.path.dirname(locale_dir)
saved_cwd = os.getcwd()
os.chdir(locale_dir)

# leeemos langs en linguas:
with open('LINGUAS', 'r') as lf:
	langs = lf.read().strip().split(' ')

# Generamos lang.po
for lang in langs:
	lang_po = lang + '.po'
	if os.path.exists(lang + '.po'):
		print(f'{lang_po}: skipped.')
	else:
		with open(lang_po, 'w') as lp:
			pass
		print(f'{lang_po}: created.')

# Finalmente, generamos POTFILES
with open('POTFILES', 'w') as pf:
	for src in sources_list:
		src_rel = os.path.relpath(src, project_dir)
		pf.write(f'{src_rel}\n')

os.chdir(saved_cwd)

