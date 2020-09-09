hunter_config(
    Lua
    VERSION 5.1.5-p3
)

hunter_config(
    SDL_mixer
    VERSION 2.0.4-p0
    CMAKE_ARGS "MUSIC_CMD=OFF" "MUSIC_FLAC=OFF" "MUSIC_OPUS=OFF"
)
