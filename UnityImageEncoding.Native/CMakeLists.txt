# CMakeList.txt : CMake project for UnityImageEncoding.Native, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.13)

project ("UnityImageEncoding.Native" CXX)
set (CMAKE_CXX_STANDARD 17)


include_directories("src/include/" "src/lib" "src/lib/etcpak")
add_library (UnityImageEncoding.Native SHARED "src/lib/etcpak/Dither.cpp"
"src/lib/etcpak/Tables.cpp"
"src/lib/etcpak/ProcessRGB.cpp"
"src/UnityImageEncoders.cpp"
)

if(MSVC)
    ADD_DEFINITIONS(/arch:AVX2)
endif()

#set(CMAKE_CXX_FLAGS_RELEASE "/MD /DNDEBUG /Zi /Od /Ob0")
# message(${CMAKE_CXX_FLAGS_RELEASE}) /MD /O2 /Ob2 /DNDEBUG /Zi /O1
# message(${CMAKE_CXX_FLAGS_DEBUG}) /MDd /Zi /Ob0 /Od /RTC1
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --save-temps -march=native")

# TODO: Add tests and install targets if needed.
