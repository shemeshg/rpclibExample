# using xdrpp

example for simple xdrpp hellow world

## prepair environment 

<https://github.com/xdrpp/xdrpp>

on macos 

      ```
      brew install automake pandoc
      ./configure
      make
      make install
      ```

## compile with `CMAKE`

```bash
mkdir build
cd build
cmake ..
make
```

## compile with `pkg-config`



### compile server

```bash
c++ -std=c++11 `pkg-config --cflags xdrpp` -c ../server.cc ../myprog.server.cc
c++ -std=c++11 -o server server.o myprog.server.o `pkg-config --libs xdrpp`
```

### compile client
```bash
c++ -std=c++11 `pkg-config --cflags xdrpp` -c ../client.cc
c++ -std=c++11 -o client client.o `pkg-config --libs xdrpp`
```

## interface files were generated with `xdrc`
```
usage: xdrc MODE [OPTIONAL] [-DVAR=VALUE...] [-o OUTFILE] INPUT.x
where MODE is one of:
      -hh           To generate header with XDR and RPC program definitions
      -serverhh     To generate scaffolding for server header file
      -servercc     To generate scaffolding for server cc
```

```
xdrc -serverhh myprog.x 
```

## forwarding local socket over ssh

```
ssh -L /tmp/myrpc_local.sock:/tmp/myrpc.sock user@remotehost
```