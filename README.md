- misc

# Play! #
Play! is a PlayStation 2 emulator for Windows, macOS, UNIX, Android & iOS platforms.

Compatibility information is available on the official [Compatibility Tracker](https://github.com/jpd002/Play-Compatibility).
If a specific game doesn't work with the emulator, please create a new issue there.

For more information, please visit [purei.org](https://purei.org).

## Building ##

### Getting Started ###
First you'll need to clone this repo which contains the emulator source code, alongside the submodules required to build Play!:
 ```
 git clone --recurse-submodules https://github.com/jpd002/Play-.git
 cd Play-
 ```

### Building for Windows ###
The easiest way to build the project on Windows is to open Qt Creator and direct it to the Cmake file in `/project/dir/Play-/CMakeLists.txt`.
You can also build the project using Visual Studio or cmdline, for that you must follow these instructions:

To build for Windows you will need to have CMake installed on your system.
 ```cmd
 mkdir build
 cd build
 ```
 ```
 # Not specifying -G will automatically generate 32-bit projects.
 cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH="C:\Qt\5.10.1\msvc2017_64" -DUSE_QT=YES
 ```
You can now build the project by opening the generated Visual Studio Solution or continue through cmdline:
 ```cmd
 cmake --build . --config Release
 ```
Note: `--config` can be `Release`, `Debug`, or `RelWithDebInfo`.

### Building for macOS & iOS ###
If you don't have CMake installed, you can install it using [Homebrew](https://brew.sh) with the following command:
 ```bash
 brew install cmake
 ```

There are two ways to generate a build for macOS. Either by using Makefiles, or Xcode:
 ```bash
 mkdir build
 cd build
 ```
 ```
 # Not specifying -G will automatically pick Makefiles
 cmake .. -G Xcode -DCMAKE_PREFIX_PATH=~/Qt/5.1.0/clang_64/
 cmake --build . --config Release
 # OR
 cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=~/Qt/5.1.0/clang_64/
 cmake --build .
 ```
To generate a build for iOS, you will need to add the following parameters to the CMake invocation:
 ```bash
 -DCMAKE_TOOLCHAIN_FILE=../../../Dependencies/cmake-ios/ios.cmake -DTARGET_IOS=ON
 ```

iOS build doesn't use Qt, so omit `-DCMAKE_PREFIX_PATH=...`

Example:
 ```bash
 cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../deps/Dependencies/cmake-ios/ios.cmake -DTARGET_IOS=ON
 ```

Note: iOS builds generated with Makefiles will not be FAT binaries.

To test your iOS builds on a device, you will need to setup code signing:
- Set `CODE_SIGNING_ALLOWED` to `YES` on the `Play` target.
- Set your code signing parameters in Signing & Capabilities tab in Xcode.

To build with Vulkan on macOS, just make sure the `$VULKAN_SDK` environment variable is set with the proper path.

On iOS, you will need to add this to your CMake command line:
 ```bash
 -DCMAKE_PREFIX_PATH=$VULKAN_SDK
 ```

### Building for UNIX ###
if you don't have Cmake or OpenAL lib installed, you'll also require Qt. (preferably version 5.6)
You can install it using your OS packaging tool, e.g Ubuntu: `apt install cmake libalut-dev qt5-default libevdev-dev libqt5x11extras5-dev libsqlite3-dev`

On UNIX systems there are 3 ways to setup a build. Using Qt creator, makefile or Ninja:
 - QT Creator
    - Open Project -> `Play/CMakeLists.txt`

 - Makefile/Ninja:
   ```bash
   mkdir build
   cd build
   ```
   ```
   # Not specifying -G will automatically pick Makefiles
   cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/opt/qt56/
   cmake --build .
   # OR
   cmake .. -G Ninja -DCMAKE_PREFIX_PATH=/opt/qt56/
   cmake --build . --config Release
   ```
The above example uses a backport repo to install Qt5.6 on Ubuntu Trusty.

Note: `CMAKE_PREFIX_PATH` refers to the Qt directory containing bin/libs folder. If you install Qt from their official website, your `CMAKE_PREFIX_PATH` might look like this: `~/Qt5.6.0/5.6/gcc_64/`

### Building for Android ###
Building for Android has been tested on macOS and UNIX environments.

Android can be built using Android Studio, or Gradle:
 - Android Studio:
   - Files-> Open Projects-> Directory To `Play/build_android`
   - Install NDK using SDK manager
     - Edit/create `Play/build_android/local.properties`
     - OSX: Add a new line: `ndk.dir=/Users/USER_NAME/Library/Android/sdk/ndk-bundle` replacing `USER_NAME` with your macOS username
     - UNIX: Add a new line: `ndk.dir=~/Android/Sdk/ndk-bundle`
     - Windows: Add a new line: `C:\Users\USER_NAME\AppData\Local\Android\sdk\ndk-bundle`
     - Please leave an empty new line at the end of the file.

Note: These examples are only valid if you installed NDK through Android Studio's SDK manager.
Otherwise, you must specify the correct location to the Android NDK.

Once this is done, you can start the build:
 - Gradle: Prerequisite Android SDK & NDK (Both can be installed through Android Studio)
   - edit/create `Play/build_android/local.properties`
     - OSX:
       - Add a new line: `sdk.dir=/Users/USER_NAME/Library/Android/sdk` replacing `USER_NAME` with your macOS username
       - Add a new line: `ndk.dir=/Users/USER_NAME/Library/Android/sdk/ndk-bundle` replacing `USER_NAME` with your macOS username
     - UNIX:
       - Add a new line: `sdk.dir=~/Android/Sdk`
       - Add a new line: `ndk.dir=~/Android/Sdk/ndk-bundle`
     - Windows:
       - Add a new line: `sdk.dir=C:\Users\USER_NAME\AppData\Local\Android\sdk`
       - Add a new line: `ndk.dir=C:\Users\USER_NAME\AppData\Local\Android\sdk\ndk-bundle`
     - Please leave an empty new line at the end of the file.

Note: These examples are only valid if you installed NDK through Android Studio's SDK manager.
Otherwise you must specify the correct location to Android NDK.
Once this is done, you can start the build:
 ```bash
 cd Play/build_android
 sh gradlew assembleDebug
 ```

##### About Release/Signed builds #####
Building through Android Studio, you have the option to “Generate Signed APK”.

When building through Gradle, you must create a text file called `Play/build_android/keystore.properties` and add the following properties to it: `storeFile`, `storePassword`, `keyAlias`, and `keyPassword`.

E.g for `keystore.properties`:
 ```
 storeFile=/location/to/my/key.jks
 storePassword=mysuperhardpassword
 keyAlias=myalias
 keyPassword=myevenharderpassword
 ```
Please leave an empty new line at the end of the file.
 ```
 cd Play/build_android
 sh gradlew assembleRelease
 # or on Windows
 gradlew.bat assembleRelease
 ```
