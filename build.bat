@echo off
setlocal enabledelayedexpansion

:: Fichier pour stocker le chemin vcpkg
set VCPKG_PATH_FILE=.vcpkg_path

:: Fonction pour afficher l'aide
:show_help
echo Usage: build.bat [Rule]
echo Rules:
echo   SETUP_VCPKG - Setup vcpkg path
echo   Init        - Initialize build directory and setup CMake
echo   Reset       - Delete build directory and reinitialize
echo   Release     - Configure CMake in Release mode
echo   Debug       - Configure CMake in Debug mode
echo   Build       - Build the project
echo   Help        - Show this help message
goto :eof

:: Fonction pour vérifier si vcpkg est configuré
:check_vcpkg_setup
if not exist "%VCPKG_PATH_FILE%" (
    echo Error: vcpkg path not set. Please run 'build.bat SETUP_VCPKG' first.
    exit /b 1
)
goto :eof

:: Fonction pour configurer vcpkg
:setup_vcpkg
echo Starting vcpkg setup...
set /p vcpkg_dir=Please enter the path to your vcpkg directory:
set vcpkg_cmake_path=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake
if exist "%vcpkg_cmake_path%" (
    echo %vcpkg_cmake_path%> "%VCPKG_PATH_FILE%"
    echo vcpkg path set successfully to: %vcpkg_cmake_path%
) else (
    echo Error: vcpkg.cmake not found at: %vcpkg_cmake_path%
    exit /b 1
)
echo vcpkg setup completed.
goto :eof

:: Fonction pour initialiser le projet
:init_project
echo Initializing project...
call :check_vcpkg_setup
set /p VCPKG_PATH=<"%VCPKG_PATH_FILE%"
echo Creating build directory...
if not exist build mkdir build
cd build
echo Running CMake...
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%" -DVCPKG_MANIFEST_MODE=ON
cd ..
echo Project initialized successfully.
goto :eof

:: Fonction pour réinitialiser le projet
:reset_project
echo Resetting project...
echo Removing build directory...
if exist build rmdir /s /q build
echo Reinitializing project...
call :init_project
echo Project reset completed.
goto :eof

:: Fonction pour configurer en mode Release
:configure_release
echo Configuring project in Release mode...
call :check_vcpkg_setup
set /p VCPKG_PATH=<"%VCPKG_PATH_FILE%"
cd build
echo Running CMake in Release mode...
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%" -DVCPKG_MANIFEST_MODE=ON ..
cd ..
echo Project configured in Release mode.
goto :eof

:: Fonction pour configurer en mode Debug
:configure_debug
echo Configuring project in Debug mode...
call :check_vcpkg_setup
set /p VCPKG_PATH=<"%VCPKG_PATH_FILE%"
cd build
echo Running CMake in Debug mode...
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%" -DVCPKG_MANIFEST_MODE=ON ..
cd ..
echo Project configured in Debug mode.
goto :eof

:: Fonction pour builder le projet
:build_project
echo Building project...
call :check_vcpkg_setup
cd build
echo Running CMake build...
cmake --build .
cd ..
echo Project build completed.
goto :eof

:: Vérification des arguments
if "%~1"=="" (
    echo Error: No rule specified.
    call :show_help
    exit /b 1
)

:: Traitement de la règle spécifiée
if "%~1"=="SETUP_VCPKG" goto setup_vcpkg
if "%~1"=="Init" goto init_project
if "%~1"=="Reset" goto reset_project
if "%~1"=="Release" goto configure_release
if "%~1"=="Debug" goto configure_debug
if "%~1"=="Build" goto build_project
if "%~1"=="Help" goto show_help

echo Error: Unknown rule '%~1'
call :show_help
exit /b 1
