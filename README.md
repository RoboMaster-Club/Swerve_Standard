# Repository Initialization Guide
``` bash
git clone https://github.com/RoboMaster-Club/Control_Base_Template.git
cd Control_Base_Template
git submodule update --init
```

# vscode MAKEFILE env setup guide
### install env tools
- download msys2 from [here] (https://www.msys2.org/)

- the default installation path is `C:\msys64`, run `C:\msys64\msys2.exe`.

- install openocd, gdb-multiarch

``` bash
pacman -S mingw-w64-x86_64-openocd
pacman -S mingw-w64-x86_64-gdb-multiarch
```

- install vscode extension `Cortex-Debug`

- Open json file of the extension, and add `"cortex-debug.gdbPath": "c:/msys64/mingw64/bin/gdb-multiarch.exe"` to the end of 'setting.json' of Cortex-Debug extension setting.

### how to use
- build: [Termimal]->[Run Task...]->[build task]. ShortCut [Ctrl+Shift+B]
- debug: navigate to Run and Debug in vscode with [Strl+Shift+D], select the launch task, and run debug. Shortcut [F5].