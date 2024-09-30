#!/bin/bash

# Couleurs pour les messages
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fichier pour stocker le chemin vcpkg
VCPKG_PATH_FILE=".vcpkg_path"

# Fonction pour afficher l'aide
show_help() {
    echo -e "${BLUE}Usage: ./build.sh [Rule]${NC}"
    echo "Rules:"
    echo -e "  ${YELLOW}SETUP_VCPKG${NC} - Setup vcpkg path"
    echo -e "  ${YELLOW}Init${NC}        - Initialize build directory and setup CMake"
    echo -e "  ${YELLOW}Reset${NC}       - Delete build directory and reinitialize"
    echo -e "  ${YELLOW}Release${NC}     - Configure CMake in Release mode"
    echo -e "  ${YELLOW}Debug${NC}       - Configure CMake in Debug mode"
    echo -e "  ${YELLOW}Build${NC}       - Build the project"
    echo -e "  ${YELLOW}Test${NC}        - Test the project"
    echo -e "  ${YELLOW}Help${NC}        - Show this help message"
    echo -e "  ${YELLOW}Clean${NC}       - Clean binaries, testing folder, and Debug folders"
}

# Fonction pour vérifier si vcpkg est configuré
check_vcpkg_setup() {
    if [ ! -f "$VCPKG_PATH_FILE" ]; then
        echo -e "${RED}Error: vcpkg path not set. Please run './build.sh SETUP_VCPKG' first.${NC}"
        exit 1
    fi
}

# Fonction pour configurer vcpkg
setup_vcpkg() {
    echo -e "${BLUE}Starting vcpkg setup...${NC}"
    echo -e "${YELLOW}Please enter the path to your vcpkg directory:${NC}"
    read vcpkg_dir
    vcpkg_cmake_path="${vcpkg_dir}/scripts/buildsystems/vcpkg.cmake"

    if [ -f "$vcpkg_cmake_path" ]; then
        echo "$vcpkg_cmake_path" > "$VCPKG_PATH_FILE"
        echo -e "${GREEN}vcpkg path set successfully to: ${vcpkg_cmake_path}${NC}"
    else
        echo -e "${RED}Error: vcpkg.cmake not found at: ${vcpkg_cmake_path}${NC}"
        exit 1
    fi
    echo -e "${BLUE}vcpkg setup completed.${NC}"
}

# Fonction pour initialiser le projet
init_project() {
    echo -e "${BLUE}Initializing project...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir -p build
    cd build
    echo -e "${YELLOW}Running CMake...${NC}"
    cmake .. -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON
    cd ..
    echo -e "${GREEN}Project initialized successfully.${NC}"
}

# Fonction pour réinitialiser le projet
reset_project() {
    echo -e "${BLUE}Resetting project...${NC}"
    echo -e "${YELLOW}Removing build directory...${NC}"
    rm -rf build
    echo -e "${YELLOW}Reinitializing project...${NC}"
    init_project
    echo -e "${GREEN}Project reset completed.${NC}"
}

# Fonction pour configurer en mode Release
configure_release() {
    echo -e "${BLUE}Configuring project in Release mode...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    cd build
    echo -e "${YELLOW}Running CMake in Release mode...${NC}"
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON ..
    cd ..
    echo -e "${GREEN}Project configured in Release mode.${NC}"
}

# Fonction pour configurer en mode Debug
configure_debug() {
    echo -e "${BLUE}Configuring project in Debug mode...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    cd build
    echo -e "${YELLOW}Running CMake in Debug mode...${NC}"
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON ..
    cd ..
    echo -e "${GREEN}Project configured in Debug mode.${NC}"
}

# Fonction pour builder le projet
build_project() {
    echo -e "${BLUE}Building project...${NC}"
    check_vcpkg_setup
    cd build
    echo -e "${YELLOW}Running CMake build...${NC}"
    cmake --build .
    cd ..
    echo -e "${GREEN}Project build completed.${NC}"
}

test_project() {
    echo -e "${BLUE}Testing project...${NC}"
    check_vcpkg_setup
    cd build || exit 1
    echo -e "${YELLOW}Running CMake build...${NC}"
    cmake --build .
    cd .. || exit 1
    echo -e "${YELLOW}Testing project...${NC}"
    cd build || exit 1
    ctest --rerun-failed --output-on-failure
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error with testing !${NC}"
        exit 1
    fi
    echo -e "${GREEN}Testing project completed.${NC}"
}

clean_project() {
    echo -e "${BLUE}Cleaning project...${NC}"

    # Supprimer le dossier testing à la racine
    echo -e "${YELLOW}Removing testing directory...${NC}"
    rm -rf Testing

    # Supprimer les dossiers Debug dans src
    echo -e "${YELLOW}Removing Debug folders in src...${NC}"
    find src -type d -name "Debug" -exec rm -rf {} +

    # Supprimer les binaires spécifiques
    echo -e "${YELLOW}Removing specific binaries...${NC}"
    rm -rf r-type_client
    rm -rf r-type_server
    rm -rf ./lib/*

    echo -e "${GREEN}Project cleaned successfully.${NC}"
}

# Vérification des arguments
if [ $# -eq 0 ]; then
    echo -e "${RED}Error: No rule specified.${NC}"
    show_help
    exit 1
fi

# Traitement de la règle spécifiée
case $1 in
    SETUP_VCPKG)
        setup_vcpkg
        ;;
    Init)
        init_project
        ;;
    Reset)
        reset_project
        ;;
    Release)
        configure_release
        ;;
    Debug)
        configure_debug
        ;;
    Build)
        build_project
        ;;
    Test)
        test_project
        ;;
    Clean)
        clean_project
        ;;
    Help)
        show_help
        ;;
    *)
        echo -e "${RED}Error: Unknown rule '$1'${NC}"
        show_help
        exit 1
        ;;
esac
