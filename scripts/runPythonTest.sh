#!/bin/bash

cd ../build/pyclient || exit 1
export PYTHONPATH="$PWD:$PYTHONPATH"

tmpfile=$(mktemp)
cat > "$tmpfile" <<EOF

from pyclient import ClientBal, ServerBal

s = ServerBal(8080)
# import threading
# threading.Thread(target=s.run, daemon=True).start()
s.startAsync()

c = ClientBal("localhost",8080)
print(c.add(1, 2).get())

EOF

python3 -i "$tmpfile"

rm "$tmpfile"