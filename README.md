# [Diep-Clone](https://discord.gg/V8G9XPYHSd)

while cloning, make sure to include submodules with --recursive when using the git cli

dependancies are

cmake >= 3.16
make


## building the client
```
mkdir build-client && cd build-client
cmake ../Client
make -j`nproc`
```
## building the server
```
mkdir build-server && cd build-server
cmake ../Server
make -j`nproc`
```
 
