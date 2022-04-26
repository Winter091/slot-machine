target_sources(
    slot-machine PRIVATE
    Application.cpp
    main.cpp
)

add_subdirectory(Slots)
add_subdirectory(States)
add_subdirectory(Window)
