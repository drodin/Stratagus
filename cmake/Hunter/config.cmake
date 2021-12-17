hunter_config(
    Lua
    VERSION 5.1.5-p3
)

#fix SDL2 hidapi/android/hid.cpp linking error
if(ANDROID AND NOT ${CMAKE_ANDROID_ARCH_ABI} STREQUAL "arm64-v8a")
hunter_config(
    SDL2
    VERSION 2.0.18
    CMAKE_ARGS
        CMAKE_CXX_FLAGS=-fPIC
)
endif()
