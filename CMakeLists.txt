# CMakeList.txt: CMake-Projekt für "SisijaFight". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SisijaFight")

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

file(GLOB_RECURSE IRR_SRC "lib/Irrlicht/*.cpp")
file(GLOB_RECURSE IRR_SRC_C "lib/Irrlicht/*.c")
file(GLOB_RECURSE SOLOUD_SRC "lib/soloud/*.cpp")
file(GLOB_RECURSE SOLOUD_SRC_C "lib/soloud/*.c")

# Pfad zur JPEG-Bibliothek innerhalb von Irrlicht
set(JPEG_LIB_PATH "lib/Irrlicht/jpeglib")

# Ausschlussregeln für Windows
if(WIN32)
    list(REMOVE_ITEM IRR_SRC_C
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemmac.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemname.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
    )
endif()

# Ausschlussregeln für Mac OS
if(APPLE)
    list(REMOVE_ITEM IRR_SRC_C
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
        # Füge weitere nicht benötigte Dateien für Mac hinzu
    )
endif()

# Ausschlussregeln für Unix/Linux
if(UNIX AND NOT APPLE)
    list(REMOVE_ITEM IRR_SRC_C
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemmac.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
        # Füge weitere nicht benötigte Dateien für Unix/Linux hinzu
    )
endif()

include_directories("lib/Irrlicht/include")
include_directories("lib/Irrlicht/aesGladman")
include_directories("lib/Irrlicht/bzip2")
include_directories("lib/Irrlicht/jpeglib")
include_directories("lib/Irrlicht/libpng")
include_directories("lib/Irrlicht/lzma")
include_directories("lib/Irrlicht/zlib")
include_directories("lib/soloud/include")
include_directories("lib/enet")
include_directories("lib")

add_executable (SisijaFight    "main.cpp" "Gamemodes/ClassicFight.cpp" "SGE/SisijaGraphicsUnitSubsystem.cpp" "SGE/SGU-S.h" "lib/json.hpp" ${IRR_SRC} ${IRR_SRC_C} ${SOLOUD_SRC} ${SOLOUD_SRC_C} ${ENET_SRC_C} "Game/Audio/Backend.h" "Game/Audio/Backend.cpp" "globals.h" "Game/Session.h" "Game/Session.cpp" "Game/EventReceivers/InGameEVR.h"  "Game/EventReceivers/LobbyEVR.h"  "Game/GUI/GUI.h" "Gamemodes/Gamemodes.h" "Network/NetworkHandler.h" "Game/Player/Player.h" "Game/Player/Player.cpp" "Game/World/World.h" "Game/World/World.cpp" "Game/EventReceivers/InGameEVR.cpp" "Game/EventReceivers/LobbyEVR.cpp")

link_directories("Irrlicht/libdirectX")

add_definitions(-DIRRLICHT_STATIC)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SisijaFight PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
