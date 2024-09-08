# python touch_me.py  "outdir_po" "dummy_pofile"

import sys
import os
from pathlib import Path

outdir_po = sys.argv[1]
po_file = sys.argv[2]

po_filename = Path(po_file).name
source_po = os.path.join(outdir_po, po_filename)

Path(source_po).touch(exist_ok=True)
Path(po_file).touch(exist_ok=True)
