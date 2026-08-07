# createQtAppImage
Create a Linux AppImage of a Qt Application with CMake

This project is a proof of concept and a recipe for the creation of an AppImage for Qt applications using CMake <= 4.2. 
Since CMake 4.2 there is an AppImage CPack generator, so this is not needed anymore. But if your CMake version is older, 
like in the ubuntu-22.04 GitHub action runner, then you need to use something like this in order to generate your AppImage.

You may use some bash script like this to automate the construction process...

```bash
#!/bin/bash
CMAKE="${HOME}/Qt/Tools/CMake/bin/cmake"
QTD="$HOME/Qt/6.11.1/gcc_64"
SRC="$HOME/Projects/createQtAppImage"
BLD=${SRC}/build
APPDIR=${BLD}/createQtAppImage-v0.0.1-x86_64.AppDir
mkdir -p ${APPDIR}
export DESTDIR=${APPDIR}

read -p "Press <Enter> to configure..."
${CMAKE} -S ${SRC} -B ${BLD} \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/usr \
  -DCMAKE_INSTALL_LIBDIR=lib \
  -DCMAKE_PREFIX_PATH="${QTD}" \
  -DCMAKE_INSTALL_RPATH="\$ORIGIN/../lib" \
  $*

read -p "Press <Enter> to build..."
${CMAKE} --build ${BLD}

read -p "Press <Enter> to install and create the AppImage..."
echo "DESTDIR=${DESTDIR}"
${CMAKE} --install ${BLD}
```

But you can also automate the AppImage creation on your CI/CD. See this project's GitHub actions.

## License

Copyright (c) 2026 Pedro López-Cabanillas  
SPDX-License-Identifier: BSD-3-Clause  