# Datenverarbeitung für TPH

This repository contains all my current homework for this course. You may use it to compare my work or take inspiration from it, if you are stuck but please don't just copy paste anything. It won't do any good for neither you, nor me. I trust you :)

I will try to upload all the homework as fast as possible while also keeping it clean. If something is not up it's not quite ready yet :)

## Tips

### Editor

If you use VS Code (like me) to develop on the remote server, don't forget to always close the SSH connection.

In order to avoid running out of disk space it's best to also remove the VS Code server folder `~/.vscode-server`, as it uses up the limited space quickly.

```
rm -rf ~/.vscode-server
```

You can run this command using any terminal with ssh connectivity like Putty and so on... after you closed the connection with VS Code (I like to use cygwin... :).

As an alternative VSCode also has a command `Remote-SSH: Uninstall VS Code Server from Host...` if you would like to try that instead.

### Compiling

In order to compile my work make sure to install CMake (minimum version required is 3.13) and g++ (assume the minimum version to be 8.3.0). It will compile on linux, never tested it on windows (maybe with MSYS2 it will work, no guarantees though).

Now that you have CMake and g++ installed, create a build folder and generate the cmake code there:

`>READ UNTIL THE END!<`

```
mkdir -p ueXX/build && \
cd ueXX/build && \
cmake -G "Unix Makefiles" ..
```

After that you just need to build the executable

```
cmake --build .
```

Now you can execute it with

```
./aufgabe
```

I also wrote a bash script to automate this process:

```
rm -r ueXX/build
mkdir -p ueXX/build
cd ueXX/build
cmake -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe
```

Notice that these are relative paths, so run this script in it's specified location only.
`>REPLACE EVERY<` keyword `ueXX` with the right folder (for e.g. `ue02, ue03, ...`). Mind that there is no CMake build system for `ue01`, you have to compile it by hand.

### Issues

If there is any issue with compiling the privided files with the build script, make sure to make an issue request, as I only took them over from my dev setup and never tested if it works >.<