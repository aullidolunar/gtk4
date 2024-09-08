# python gen_mo_files.py "msgfmt_executable" "po_file" "mo_path" "dummy_depfile"

import os
import glob
import sys
import subprocess
from pathlib import Path

msgfmt_executable = sys.argv[1]
po_file = sys.argv[2]
mo_path = sys.argv[3]
dummy_depfile = sys.argv[4]

saved_cwd = os.getcwd()

mo_file = Path(mo_path)
mo_file.parent.mkdir(exist_ok=True, parents=True)
	
subprocess.call([
	msgfmt_executable,
	po_file,
	'-o',
	mo_path
])

os.chdir(saved_cwd)

dummy_file = Path(dummy_depfile)
dummy_file.write_text(f"File saved at\n{mo_path}")