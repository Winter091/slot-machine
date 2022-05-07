target_sources(
    slot-machine PRIVATE
    Application.cpp
    Config.cpp
    main.cpp
)

add_subdirectory(Events)
add_subdirectory(Slots)
add_subdirectory(States)
add_subdirectory(Window)
