#!/bin/bash

cd ../build/pyclient || exit 1
export PYTHONPATH="$PWD:$PYTHONPATH"

tmpfile=$(mktemp)
cat > "$tmpfile" <<EOF

from pyclient import ClientBal, ServerBal

#s = ServerBal(8080)
#s.startAsync()

# import threading
# threading.Thread(target=s.run, daemon=True).start()


c = ClientBal("localhost",8080)
print(c.add(1, 2).get())

def run_once():
    a = c.getCounterExample(2)
    a.add(20)
    print(a.get())
run_once()

## test exception
# a = c.getCounterExample(2)
# a.setExpiredAt(0)
# c.sessionStateCleanup()
# a.get()

EOF

python3 -i "$tmpfile"

rm "$tmpfile"