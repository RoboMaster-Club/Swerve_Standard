# Purdue Robomasters Control Base Template
This repository contains the shared control code between Purdue Robomasters robots.

# Repository Initialization Guide
``` bash
git clone https://github.com/RoboMaster-Club/Control_Base_Template.git
cd Control_Base_Template
git submodule update --init
```

## VSCode MAKEFILE environment setup guide
### Install environment tools
**Windows**
- Download MSYS2 from [here](https://www.msys2.org/)
- The default installation path is `C:\msys64`, run `C:\msys64\msys2.exe`.
- Install OpenOCD, arm-none-eabi-gcc, and gdb-multiarch from [here](https://packages.msys2.org/package/)
```bash
pacman -S mingw-w64-x86_64-openocd
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
pacman -S mingw-w64-x86_64-gdb-multiarch
```

**MacOS - Apple Silicon**
 - Install arm-none-eabi-gcc (darwin-arm64) from [here](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) into your `usr/local/` directory. (homebrew does not install all the necessary files)
 - Install OpenOCD using [homebrew](https://docs.brew.sh/Installation)
```zsh
brew install openocd
```
- GDB is not currently supported on apple silicon
## Common Issues

- add tool path for openocd and make tool
- install vscode extension `Cortex-Debug`

- Open json file of the extension, and add `"cortex-debug.gdbPath": "c:/msys64/mingw64/bin/gdb-multiarch.exe"` to the end of 'setting.json' of Cortex-Debug extension setting.

### How to use
- build: [Termimal]->[Run Task...]->[build task]. ShortCut [Ctrl+Shift+B]
- debug: navigate to Run and Debug in vscode with [Strl+Shift+D], select the launch task, and run debug. Shortcut [F5].

## Common Issues
### 1. Windows fails to initializing cmsis-dap debugger. 
Solution: Go to device manager and uninstall the usb device (probably having some error message in the list). Unplug and plug in the debugger again.

### 2.  Tools (OpenOCD, make tools) not found
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

## Tips
### VSCode IntelliSense Configuration
```
"C_Cpp.default.compilerPath": "C:/msys64/mingw64/bin/arm-none-eabi-gcc.exe"
```
adding this would link the standard library header files, such as `stdint.h`, `stdlib.h`, `math.h`.

# Development Conventions
**All names must use snake_case.**

Variable names are all lowercase.
```c
 float example_float = 1.5f;
```

Macros should be all UPPERCASE.
```c
 #define EXAMPLE_MACRO 3.14f 
```

Function names should capitalize the first letter of each word.
```c
 float Example_Function() {}
```

Wrapper functions should capitalize the first word.
```c
 float MOTOR_Example_Function() {}
```

Struct names should capitalize the first letter of each word and end in _t. 
```c
 struct Example_Struct_t {} 
```

When using struct pointers, don't put a space between the arrow.
```c
 struct Example_Struct_t {
    int example_struct_member;
 } example_struct;
 // access member
 example_struct->example_struct_member;
```

Enum names should capitalized the first letter of each word and end in _e.
```c
 enum Example_Enum_e {};
```

In general, indent code blocks for functions and if statments as such, but for switches put cases in the same line.
```c
void Example_Func()
{
   if (some_condition)
   {
      switch(some_num)
      {
      case 0:
         break;
      default:
         break;
      }
   }
}
```

For multiline macros, indent as such:
```c
#define YOUR_MACRO        \
   {                      \
      FIRST_LINE = 0,     \
         SECOND_LINE = 1, \
         THIRD_LINE = 2,  \
   }
```
