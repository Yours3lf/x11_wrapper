add_library(x11 SHARED atom display screen window pixmap cursor)

target_link_libraries(x11 X11)
