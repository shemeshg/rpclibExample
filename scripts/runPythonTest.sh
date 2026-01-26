#!/bin/bash

cd ../build/pyclient || exit 1
export PYTHONPATH="$PWD:$PYTHONPATH"

tmpfile=$(mktemp)
cat > "$tmpfile" <<EOF
import pyclient
print(pyclient.add(1, 2))
EOF

python3 -i "$tmpfile"

rm "$tmpfile"