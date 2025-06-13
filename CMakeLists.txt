# Minimum CMake version and project
cmake_minimum_required(VERSION 3.10)
project(rogue C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Source files
set(SOURCES
    vers.c extern.c armor.c chase.c command.c daemon.c
    daemons.c fight.c init.c io.c list.c mach_dep.c
    main.c mdport.c misc.c monsters.c move.c new_level.c
    options.c pack.c passages.c potions.c rings.c rip.c
    rooms.c save.c scrolls.c state.c sticks.c things.c
    weapons.c wizard.c xcrypt.c
)

# Header files (for IDEs, not strictly needed)
set(HEADERS
    rogue.h extern.h score.h
)

# Find ncurses and tinfo
find_package(Curses REQUIRED)
find_library(TINFO_LIBRARY tinfo)
include_directories(${CURSES_INCLUDE_DIR})

# Add executable
add_executable(rogue ${SOURCES} ${HEADERS})

# Link with ncurses and tinfo if found
if(TINFO_LIBRARY)
    target_link_libraries(rogue ${CURSES_LIBRARIES} ${TINFO_LIBRARY})
else()
    target_link_libraries(rogue ${CURSES_LIBRARIES})
endif()

# Install rules
install(TARGETS rogue RUNTIME DESTINATION bin)
install(FILES LICENSE.TXT DESTINATION share/doc/rogue)

# Optionally install docs and manpage if generated
install(FILES rogue.6 DESTINATION share/man/man6 OPTIONAL)
install(FILES rogue.doc rogue.html rogue.cat rogue.me DESTINATION share/doc/rogue OPTIONAL)
