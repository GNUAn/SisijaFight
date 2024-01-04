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
file(GLOB_RECURSE AS_SRC "lib/angelscript/*.cpp" "lib/angelscript/*.c")

set(DIRR_STATIC_LIB_)

set(JPEG_LIB_PATH "lib/Irrlicht/jpeglib")

if(WIN32)
    list(REMOVE_ITEM IRR_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemmac.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemname.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
    )
endif()

if(APPLE)
    list(REMOVE_ITEM IRR_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemdos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
        file(GLOB_RECURSE ISRCMM "lib/Irrlicht/*.mm")
        set(IRR_SRC IRR_SRC ISRCMM)
    )
endif()

if(UNIX AND NOT APPLE)
    list(REMOVE_ITEM IRR_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemmac.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${JPEG_LIB_PATH}/jmemnobs.c"
        # Füge weitere nicht benötigte Dateien für Unix/Linux hinzu
    )
endif()

include_directories("lib/Irrlicht/include")
include_directories("lib/angelscript/include")
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

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_IRR_STATIC_LIB_")

# for angelscript
set(ARCHFLAGS "${CMAKE_SYSTEM_PROCESSOR}")
if (APPLE AND NOT IOS)
  if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set(ARCHFLAGS "aarch64")
  endif ()
endif ()

if(MSVC AND CMAKE_CL_64)
    enable_language(ASM_MASM)
    if(CMAKE_ASM_MASM_COMPILER_WORKS)
        set(AS_SRC ${AS_SRC} "lib/angelscript/src/as_callfunc_x64_msvc_asm.asm")
    else()
        message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
    endif()
endif()

if(${ARCHFLAGS} MATCHES "^arm")
    enable_language(ASM)
    if(CMAKE_ASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} "lib/angelscript/src/as_callfunc_arm.cpp" "lib/angelscript/src/as_callfunc_arm_gcc.S")
        set_property(SOURCE "lib/angelscript/src/as_callfunc_arm_gcc.S" APPEND PROPERTY COMPILE_FLAGS " -Wa,-mimplicit-it=always")
    else()
        message(FATAL ERROR "ARM target requires a working assembler")
    endif()
endif()

if(${ARCHFLAGS} MATCHES "^aarch64")
    enable_language(ASM)
    if(CMAKE_ASM_COMPILER_WORKS)
        if(NOT APPLE)
            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} "lib/angelscript/src/as_callfunc_arm64.cpp" "lib/angelscript/src/as_callfunc_arm64_gcc.S")
        else()
            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} "lib/angelscript/src/as_callfunc_arm64.cpp" "lib/angelscript/src/as_callfunc_arm64_xcode.S")
        endif()
    else()
        message(FATAL ERROR "ARM target requires a working assembler")
    endif()
endif()

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")  
endif()

add_executable (SisijaFight "src/main.cpp" "src/Gamemodes/ClassicFight.cpp" "src/SGE/SisijaGraphicsUnitSubsystem.cpp" "src/SGE/SGU-S.hpp" "lib/json.hpp" ${IRR_SRC} ${SOLOUD_SRC} ${PUGIXML_SRC} ${IBULLET_SRC} ${ENET_SRC} ${AS_SRC} "src/Game/Audio/Backend.hpp" "src/Game/Audio/Backend.cpp" "src/globals.hpp" "src/Game/Session.hpp" "src/Game/Session.cpp" "src/Game/EventReceivers/InGameEVR.hpp"  "src/Game/EventReceivers/LobbyEVR.hpp"  "src/Game/GUI/GUI.hpp" "src/Gamemodes/Gamemodes.hpp" "src/Network/NetworkHandler.hpp" "src/Network/NetworkHandler.cpp" "src/Game/Player/Player.hpp" "src/Game/Player/Player.cpp" "src/Game/World/World.hpp" "src/Game/World/World.cpp" "src/Game/EventReceivers/InGameEVR.cpp" "src/Game/EventReceivers/LobbyEVR.cpp"  "src/Game/GUI/Lobby.cpp" "src/Tools/GUITools.hpp" "src/Tools/GUITools.cpp" "src/Game/GUI/Elements/SuperTable.hpp" "src/Game/GUI/Elements/SuperTable.cpp" "src/Game/GUI/helpers/helpers.hpp" "src/Game/GUI/helpers/helpers.cpp"  "src/SGE/SCamera.cpp" "src/Game/World/SPHSplash/Splatter.hpp" "src/Game/World/SPHSplash/Splatter.cpp"  "src/Tools/Translation/Translator.cpp" "src/Configurator.cpp" "src/compileConfig.h" "src/Game/Network/NetworkTools.cpp" "src/Game/GUI/Widgets.cpp")

if(WIN32)
    target_link_libraries(SisijaFight wsock32 ws2_32)
    include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
elseif(UNIX AND NOT APPLE)

elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(SisijaFight ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
endif()