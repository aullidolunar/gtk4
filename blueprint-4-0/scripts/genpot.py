# python genpot.py locale_dir sources_list

import os
import sys

locale_dir = sys.argv[1]
sources_list = sys.argv[2:]

project_dir = os.path.dirname(locale_dir)
saved_cwd = os.getcwd()
potfiles_nfo_file = os.path.join(saved_cwd, 'POTFILES.nfo')
os.chdir(locale_dir)

# leeemos langs en linguas:
with open('LINGUAS', 'r') as lf:
	langs = lf.read().strip().split(' ')

# Generamos lang.po y guardamos la bitácora en el .nfo
with open(potfiles_nfo_file, 'w') as pi:
	for lang in langs:
		lang_po = lang + '.po'
		if os.path.exists(lang + '.po'):
			print(f'{lang_po}: skipped.')
			pi.write(f'{lang_po}: exists and no need to be created.\n')
		else:
			with open(lang_po, 'w') as pf:
				pass
			print(f'{lang_po}: created.')
			pi.write(f'{lang_po}: not found and was created.\n')

# Finalmente, generamos POTFILES
with open('POTFILES', 'w') as pf:
	for src in sources_list:
		src_rel = os.path.relpath(src, project_dir)
		src_rel = src_rel.replace("locale", "build")
		pf.write(f'{src_rel}\n')

os.chdir(saved_cwd)

