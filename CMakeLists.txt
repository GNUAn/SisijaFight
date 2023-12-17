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

file(GLOB_RECURSE IRR_SRC "lib/Irrlicht/*.cpp" "lib/Irrlicht/*.c")
file(GLOB_RECURSE SOLOUD_SRC "lib/soloud/*.cpp" "lib/soloud/*.c")
file(GLOB_RECURSE PUGIXML_SRC "lib/pugixml/*.cpp")
file(GLOB_RECURSE OPENCL_SRC "lib/OpenCL/src/*.c" "lib/OpenCL/src/*.cpp")
file(GLOB_RECURSE IBULLET_SRC "lib/irrbullet/*.cpp" "lib/irrbullet/.c" "lib/Bullet/*.cpp" "lib/Bullet/*.c")
file(GLOB_RECURSE ENET_SRC "lib/enet/*.c")

# Pfad zur JPEG-Bibliothek innerhalb von Irrlicht
set(JPEG_LIB_PATH "lib/Irrlicht/jpeglib")

# Ausschlussregeln für Windows
if(WIN32)
    list(REMOVE_ITEM IRR_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemmac.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemname.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
    )
endif()

# Ausschlussregeln für Mac OS
if(APPLE)
    list(REMOVE_ITEM IRR_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
        # Füge weitere nicht benötigte Dateien für Mac hinzu
    )
endif()

# Ausschlussregeln für Unix/Linux
if(UNIX AND NOT APPLE)
    list(REMOVE_ITEM IRR_SRC
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
include_directories("lib/irrbullet/include")
include_directories("lib/Bullet/src")
include_directories("lib/pugixml")
include_directories("lib")
include_directories("lib/enet/include")
include_directories("lib/Bullet/Extras/BulletRoboticsGUI" "lib/Bullet/Extras/ConvexDecomposition" "lib/Bullet/Extras/GIMPACTUtils" "lib/Bullet/Extras/HACD" "lib/Bullet/Extras/InverseDynamics" "lib/Bullet/Extras/obj2sdf" "lib/Bullet/Extras/Serialize" "lib/Bullet/Extras/VHACD/inc" "lib/Bullet/Extras/BulletRobotics" "C:/Users/Lucas Gola/Desktop/Sisija/SisijaFight/SisijaFight/lib/Bullet/Extras/Serialize/BulletFileLoader"
 "lib/Bullet/Extras/Serialize/BulletWorldImporter"
 "lib/Bullet/Extras/Serialize/BulletXmlWorldImporter"
 "lib/Bullet/Extras/Serialize/HeaderGenerator"
 "lib/Bullet/Extras/Serialize/makesdna"
 "lib/Bullet/Extras/Serialize/ReadBulletSample"
 "lib/Bullet/Extras/Serialize/BlenderSerialize")


add_executable (SisijaFight "main.cpp" "Gamemodes/ClassicFight.cpp" "SGE/SisijaGraphicsUnitSubsystem.cpp" "SGE/SGU-S.h" "lib/json.hpp" ${IRR_SRC} ${SOLOUD_SRC} ${PUGIXML_SRC} ${IBULLET_SRC} ${ENET_SRC} "Game/Audio/Backend.h" "Game/Audio/Backend.cpp" "globals.h" "Game/Session.h" "Game/Session.cpp" "Game/EventReceivers/InGameEVR.h"  "Game/EventReceivers/LobbyEVR.h"  "Game/GUI/GUI.h" "Gamemodes/Gamemodes.h" "Network/NetworkHandler.h" "Network/NetworkHandler.cpp" "Game/Player/Player.h" "Game/Player/Player.cpp" "Game/World/World.h" "Game/World/World.cpp" "Game/EventReceivers/InGameEVR.cpp" "Game/EventReceivers/LobbyEVR.cpp"  "Game/GUI/Lobby.cpp" "Tools/GUITools.h" "Tools/GUITools.cpp" "Game/GUI/Elements/MeshViewer.h" "Game/GUI/Elements/MeshViewer.cpp" "Game/GUI/Elements/SuperTable.h" "Game/GUI/Elements/SuperTable.cpp" "Game/GUI/helpers/helpers.h" "Game/GUI/helpers/helpers.cpp"  "SGE/SCamera.cpp" "Game/World/SPHSplash/Splatter.hpp" "Game/World/SPHSplash/Splatter.cpp")

# Finde die notwendigen Bibliotheken je nach BetriebssystemPENCL_SRC}
if(WIN32)
    # Für Windows, verlinke gegen die Winsock-Bibliothek
    target_link_libraries(SisijaFight wsock32 ws2_32)
    include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
elseif(UNIX AND NOT APPLE)
    
elseif(APPLE)
    # Für macOS, finde und verlinke gegen erforderliche Frameworks
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(SisijaFight ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SisijaFight PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
