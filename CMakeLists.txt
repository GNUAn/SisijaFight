
cmake_minimum_required (VERSION 3.8)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SisijaFight")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_VERSION 18)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

file(GLOB_RECURSE IRR_SRC "lib/Irrlicht/*.cpp" "lib/Irrlicht/*.c")
file(GLOB_RECURSE SOLOUD_SRC "lib/soloud/*.cpp" "lib/soloud/*.c")
file(GLOB_RECURSE PUGIXML_SRC "lib/pugixml/*.cpp")
file(GLOB_RECURSE ASW_SRC "lib/sAS/*.cpp")
file(GLOB_RECURSE IBULLET_SRC "lib/irrbullet/*.cpp" "lib/irrbullet/.c" "lib/Bullet/*.cpp" "lib/Bullet/*.c")
file(GLOB_RECURSE ENET_SRC "lib/enet/*.c")
file(GLOB_RECURSE GUI_SRC "lib/gui/*.cpp" "lib/gui/*.c")
file(GLOB_RECURSE OPENAI "lib/openai/*.cpp")

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
include_directories("lib/angelscript/include" "lib/angelscript/addons")
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
include_directories("lib/gui/imgui"
    "lib/gui/imgui/IMGUI"
    "lib/gui/ImGuizmo"
    "lib/gui/Irrlicht-ImGui/includes"
    "lib/gui/imgui-node-editor")
include_directories("lib/enet/include")
include_directories("lib/Bullet/Extras/BulletRoboticsGUI" "lib/Bullet/Extras/ConvexDecomposition" "lib/Bullet/Extras/GIMPACTUtils" "lib/Bullet/Extras/HACD" "lib/Bullet/Extras/InverseDynamics" "lib/Bullet/Extras/obj2sdf" "lib/Bullet/Extras/Serialize" "lib/Bullet/Extras/VHACD/inc" "lib/Bullet/Extras/BulletRobotics" "C:/Users/Lucas Gola/Desktop/Sisija/SisijaFight/SisijaFight/lib/Bullet/Extras/Serialize/BulletFileLoader"
 "lib/Bullet/Extras/Serialize/BulletWorldImporter"
 "lib/Bullet/Extras/Serialize/BulletXmlWorldImporter"
 "lib/Bullet/Extras/Serialize/HeaderGenerator"
 "lib/Bullet/Extras/Serialize/makesdna"
 "lib/Bullet/Extras/Serialize/ReadBulletSample"
 "lib/Bullet/Extras/Serialize/BlenderSerialize")
 include_directories("lib/openai/include")
 include_directories("src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" " -D_IRR_STATIC_LIB_ -D_CURL_STATICLIB")

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")  
endif()

add_subdirectory("lib/whispercpp")
include_directories("lib/whispercpp")
add_subdirectory("lib/portaudio")
include_directories("lib/portaudio/include")
add_subdirectory("lib/curl")
include_directories("lib/curl/include")

add_subdirectory("lib/angelscript/angelscript/projects/cmake")
include_directories("lib/angelscript/angelscript/include" "lib/sAS")
include_directories("lib/angelscript/add_on")
file(GLOB_RECURSE ASAddon_src "lib/angelscript/add_on/*.cpp" "lib/angelscript/add_on/*.c")
add_executable (SisijaFight "src/main.cpp" "src/Gamemodes/ClassicFight.cpp" "src/SGE/SisijaGraphicsUnitSubsystem.cpp" "src/SGE/SGU-S.hpp" "lib/json.hpp" ${IRR_SRC} ${ASAddon_src} ${SOLOUD_SRC} ${PUGIXML_SRC} ${IBULLET_SRC} ${ENET_SRC} ${GUI_SRC} ${OPENAI} "src/Game/Audio/Backend.hpp" "src/Game/Audio/Backend.cpp" "src/globals.hpp" "src/Game/Session.hpp" "src/Game/Session.cpp" "src/Game/EventReceivers/InGameEVR.hpp"  "src/Game/EventReceivers/LobbyEVR.hpp"  "src/Game/GUI/GUI.hpp" "src/Gamemodes/Gamemodes.hpp" "src/Network/NetworkHandler.hpp" "src/Network/NetworkHandler.cpp" "src/Game/Player/Player.hpp" "src/Game/Player/Player.cpp" "src/Game/World/World.hpp" "src/Game/World/World.cpp" "src/Game/EventReceivers/InGameEVR.cpp" "src/Game/EventReceivers/LobbyEVR.cpp"  "src/Game/GUI/Pages/Lobby/Lobby.cpp" "src/Tools/GUITools.hpp" "src/Tools/GUITools.cpp" "src/Game/GUI/Elements/factory.cpp" "src/Game/GUI/helpers/helpers.hpp" "src/Game/GUI/helpers/helpers.cpp"  "src/SGE/SCamera.cpp" "src/Game/World/SPHSplash/Splatter.hpp" "src/Game/World/SPHSplash/Splatter.cpp"  "src/Tools/Translation/Translator.cpp" "src/Configurator.cpp" "src/compileConfig.h" "src/Game/Network/NetworkTools.cpp" "src/Game/GUI/Widgets.cpp" "src/SGE/Scripting.cpp" "src/SGE/GUIEnvironment.cpp" "src/AI/Transcriber.cpp" "src/AI/GPT.cpp" "src/Game/GUI/Pages/Lobby/GameModeSelection.cpp" "src/Game/GUI/Pages/Lobby/ServerSelection.cpp" "src/Game/GUI/Pages/Lobby/WorldSelection.cpp" "src/Game/GUI/Pages/Chat/Chat.cpp"  "src/Gamemodes/Gamemodes.cpp" "src/Game/GUI/Pages/Settings/SettingsWidget.cpp" "src/SGE/Animators.cpp" "src/Game/Managers/FileManager.cpp" "src/Game/Managers/MusicManager.cpp")


if(WIN32)
    target_link_libraries(SisijaFight wsock32 ws2_32)
    include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
elseif(UNIX AND NOT APPLE)

elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(SisijaFight ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(SisijaFight ${ZLIB_LIBRARIES})
endif()

find_package(PNG REQUIRED)
if(PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(SisijaFight ${PNG_LIBRARIES})
    add_definitions(${PNG_DEFINITIONS})
endif()

find_package(JPEG REQUIRED)
if(JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries(SisijaFight ${JPEG_LIBRARIES})
endif()

target_link_libraries(SisijaFight whisper)
target_link_libraries(SisijaFight portaudio)
target_link_libraries(SisijaFight angelscript)
target_link_libraries(SisijaFight CURL::libcurl)

install(TARGETS SisijaFight DESTINATION bin)
install(DIRECTORY "../SisijaFight-Data/" DESTINATION bin/data)