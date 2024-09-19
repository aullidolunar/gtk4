# python desktop_build_sys.py "desktop_file_pre" "build_sys" "desktop_file_out"

import sys

def sed_desktop(df_pre, build_sys, df_out):
	with open(df_pre, 'r') as df:
		contenido = df.read()
	nuevo_contenido = contenido.replace('%s', build_sys)
	with open(df_out, 'w') as df:
		df.write(nuevo_contenido)
	
desktop_file_pre = sys.argv[1]
build_sys = sys.argv[2]
desktop_file_out = sys.argv[3]

sed_desktop(desktop_file_pre, build_sys, desktop_file_out)
