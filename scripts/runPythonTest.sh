#!/bin/bash

cd ../build/pyclient || exit 1
export PYTHONPATH="$PWD:$PYTHONPATH"

tmpfile=$(mktemp)
cat > "$tmpfile" <<EOF
from pyclient import ClientBal

c = ClientBal("localhost",8080)
print(c.add(1, 2))

EOF

python3 -i "$tmpfile"

rm "$tmpfile"