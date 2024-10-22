@echo off
setlocal enabledelayedexpansion

set "VCPKG_PATH_FILE=.vcpkg_path"

:show_help
echo Usage: build.bat [rule]
echo Rules:
echo   setup_vcpkg - Setup vcpkg
echo   init        - Initialize build directory and setup CMake
echo   reset       - Delete build directory and reinitialize
echo   release     - Configure CMake in Release mode
echo   debug       - Configure CMake in Debug mode
echo   build       - Build the project
echo   test        - Test the project
echo   lint        - Run Clang-Tidy on the project
echo   help        - Show this help message
echo   clean       - Clean binaries, testing folder, and Debug folders
echo   full_build  - Run setup_vcpkg, init, release, and build in sequence
goto :eof

:check_vcpkg_setup
if not exist "%VCPKG_PATH_FILE%" (
    echo Error: vcpkg path not set. Please run 'build.bat setup_vcpkg' first.
    exit /b 1
)
goto :eof

:setup_vcpkg
echo Starting vcpkg setup...
if not exist "vcpkg" (
    echo vcpkg directory not found. Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
    if errorlevel 1 (
        echo Error: Failed to clone vcpkg repository.
        exit /b 1
    )
)

set "vcpkg_cmake_path=vcpkg\scripts\buildsystems\vcpkg.cmake"

if exist "%vcpkg_cmake_path%" (
    echo %vcpkg_cmake_path% > "%VCPKG_PATH_FILE%"
    echo vcpkg path set successfully to: %vcpkg_cmake_path%
) else (
    echo Error: vcpkg.cmake not found at: %vcpkg_cmake_path%
    exit /b 1
)
echo vcpkg setup completed.
goto :eof

:init_project
echo Initializing project...
call :check_vcpkg_setup
set /p vcpkg_path=<"%VCPKG_PATH_FILE%"
echo Creating build directory...
mkdir build
cd build
echo Running CMake...
cmake .. -DCMAKE_TOOLCHAIN_FILE="%vcpkg_path%" -DVCPKG_MANIFEST_MODE=ON
if errorlevel 1 (
    echo Error: CMake configuration failed.
    exit /b 1
)
cd ..
echo Project initialized successfully.
goto :eof

:reset_project
echo Resetting project...
echo Removing build directory...
rmdir /s /q build
echo Reinitializing project...
call :init_project
echo Project reset completed.
goto :eof

:configure_release
echo Configuring project in Release mode...
call :check_vcpkg_setup
set /p vcpkg_path=<"%VCPKG_PATH_FILE%"
cd build
echo Running CMake in Release mode...
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="%vcpkg_path%" -DVCPKG_MANIFEST_MODE=ON ..
if errorlevel 1 (
    echo Error: CMake configuration in Release mode failed.
    exit /b 1
)
cd ..
echo Project configured in Release mode.
goto :eof

:configure_debug
echo Configuring project in Debug mode...
call :check_vcpkg_setup
set /p vcpkg_path=<"%VCPKG_PATH_FILE%"
cd build
echo Running CMake in Debug mode...
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="%vcpkg_path%" -DVCPKG_MANIFEST_MODE=ON ..
if errorlevel 1 (
    echo Error: CMake configuration in Debug mode failed.
    exit /b 1
)
cd ..
echo Project configured in Debug mode.
goto :eof

:build_project
echo Building project...
call :check_vcpkg_setup
cd build
echo Running CMake build...
cmake --build .
if errorlevel 1 (
    echo Error: Build failed.
    exit /b 1
)
cd ..
echo Project build completed.
goto :eof

:test_project
echo Testing project...
call :check_vcpkg_setup
cd build
echo Running CMake build...
cmake --build .
if errorlevel 1 (
    echo Error: Build failed.
    exit /b 1
)
cd ..
echo Testing project...
cd build
ctest --rerun-failed --output-on-failure
if errorlevel 1 (
    echo Error: Testing failed.
    exit /b 1
)
echo Testing project completed.
goto :eof

:clean_project
echo Cleaning project...
echo Removing testing directory...
rmdir /s /q Testing
echo Removing Debug folders in src...
for /r src %%d in (Debug) do if exist "%%d" rmdir /s /q "%%d"
echo Removing specific binaries...
del /q r-type_client.exe
del /q r-type_server.exe
del /q /s /f /q lib\*
echo Project cleaned successfully.
goto :eof

:run_clang_tidy
echo Running Clang-Tidy...
call :check_vcpkg_setup
cd build
echo Running Clang-Tidy on source files...
cmake --build . --target clang-tidy
if errorlevel 1 (
    echo Error: Clang-Tidy failed.
    exit /b 1
)
cd ..
echo Clang-Tidy completed successfully.
goto :eof

:full_build
echo Starting full build process...
call :setup_vcpkg
call :init_project
call :configure_release
call :build_project
echo Full build process completed successfully.
goto :eof

if "%~1"=="" (
    echo Error: No rule specified.
    call :show_help
    exit /b 1
)

if "%~1"=="setup_vcpkg" goto :setup_vcpkg
if "%~1"=="init" goto :init_project
if "%~1"=="reset" goto :reset_project
if "%~1"=="release" goto :configure_release
if "%~1"=="debug" goto :configure_debug
if "%~1"=="build" goto :build_project
if "%~1"=="test" goto :test_project
if "%~1"=="lint" goto :run_clang_tidy
if "%~1"=="clean" goto :clean_project
if "%~1"=="full_build" goto :full_build
if "%~1"=="help" goto :show_help

echo Error: Unknown rule '%~1'
call :show_help
exit /b 1
