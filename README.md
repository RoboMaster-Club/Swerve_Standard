

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

- install openocd, arm-none-eabi-gcc, gdb-multiarch from [mingw64 packages](https://packages.msys2.org/package/)

``` bash
pacman -S mingw-w64-x86_64-openocd
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
pacman -S mingw-w64-x86_64-gdb-multiarch
```

- add tool path for openocd and make tool

- install vscode extension `Cortex-Debug`

- Open json file of the extension, and add `"cortex-debug.gdbPath": "c:/msys64/mingw64/bin/gdb-multiarch.exe"` to the end of 'setting.json' of Cortex-Debug extension setting.

### how to use
- build: [Termimal]->[Run Task...]->[build task]. ShortCut [Ctrl+Shift+B]
- debug: navigate to Run and Debug in vscode with [Strl+Shift+D], select the launch task, and run debug. Shortcut [F5].

# Common Issue
### 1. windows fails to initializing cmsis-dap debugger. 
Solution: Go to device manager and uninstall the usb device (probably having some error message in the list). Unplug and plug in the debugger again.

### 2.  tools (OpenOCD, make tools) not found
```
Failed to launch OpenOCD GDB Server:...
```
or
```
mingw32-make: The term 'mingw32-make' is not recognized as a name of a cmdlet, function, script file, or executable program.
Check the spelling of the name, or if a path was included, verify that the path is correct and try again.
```
Solution1:
Add openocd.exe to system environmental variable. If you followed the installation instruction in this README file, then OpenOCD should be install at default location `C:\msys64\mingw64\bin\openocd.exe`, for windows user. Add `C:\msys64\mingw64\bin` to system executable path.

Solution2:
If you don't want to mess with the system path, you could also add local openocd path in `.vscode/launch.json`. Add attribute `serverpath` by adding `"serverpath": "C:\\msys64\\mingw64\\bin\\openocd.exe"` in configuration.

**Note**
restarting vscode might be needed for new environment variable to take effect.

# Tips
## vscode IntelliSense Configuration
```
"C_Cpp.default.compilerPath": "C:/msys64/mingw64/bin/arm-none-eabi-gcc.exe"
```
adding this would link the standard library header files, such as `stdint.h`, `stdlib.h`, `math.h`.
