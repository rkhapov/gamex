TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

equals(QMAKE_HOST.os, Windows): error("Add windows allegro library")

equals(QMAKE_HOST.os, Linux): LIBS += -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_primitives -lallegro_color

SOURCES += \
    src/main.cpp \
    src/color.cpp \
    src/cords.cpp \
    src/font.cpp \
    src/image.cpp \
    src/my_string.cpp \
    src/vector.cpp \
    src/window.cpp \
    src/sgl.cpp \
    src/menu.cpp \
    src/text_printer.cpp

HEADERS += \
    src/color.h \
    src/cords.h \
    src/event_manager.h \
    src/font.h \
    src/image.h \
    src/my_string.h \
    src/timer.h \
    src/vector.h \
    src/window.h \
    src/sgl.h \
    src/menu.h \
    src/text_printer.h
