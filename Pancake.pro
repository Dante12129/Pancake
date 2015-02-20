#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T10:14:57
#
#-------------------------------------------------

QT       -= core gui

CONFIG(release, debug|release): TARGET = pancake
CONFIG(debug, debug|release): TARGET = pancake-d
CONFIG(debug, debug|release): DEFINES += PCKE_DEBUG
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -pedantic -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-unused-variable

win32{
    DEFINES += PANCAKE_WINDOWS
    PLATFORM = Windows

    LIBS += -LC:/Users/Dan/Documents/Programs/Libraries/lib
    INCLUDEPATH += include C:/Users/Dan/Documents/Programs/Libraries/include
    DEPENDPATH += include C:/Users/Dan/Document/Programs/Libraries/include
}

unix:!macx{
    DEFINES += PANCAKE_UNIX
    PLATFORM = Unix

    LIBS += -Lusr/local/lib
    INCLUDEPATH += include usr/local/include
    DEPENDPATH += include usr/local/include
}

CONFIG(debug, debug|release): LIBS += -Wl,--whole-archive -lglutilD -lglloadD -Wl,--no-whole-archive
CONFIG(release, debug|release): LIBS += -Wl,--whole-archive -lglutil -lglload -Wl,--no-whole-archive


win32:LIBS += -lSDL2 -lSDL2_ttf -lopengl32
unix:!macx:LIBS += -lGL

SOURCES += \
    source/Graphics/Color.cpp \
    source/Graphics/Vertex.cpp \
    source/Window/Window.cpp \
    source/Pancake.cpp \
    source/OpenGL/Shader.cpp \
    source/OpenGL/ShaderProgram.cpp \
    source/Graphics/Image.cpp \
    source/OpenGL/Texture.cpp \
    source/OpenGL/GLCheck.cpp \
    source/OpenGL/BufferObject.cpp \
    source/Window/Context.cpp \
    source/Window/ContextSettings.cpp \
    source/System/Clipboard.cpp \
    source/System/Info.cpp \
    source/OpenGL/Extensions.cpp \
    source/Window/Display.cpp \
    source/System/Library.cpp

HEADERS += \
    include/Pancake/Graphics/Color.hpp \
    include/Pancake/Graphics/Vertex.hpp \
    include/Pancake/OpenGL/Shader.hpp \
    include/Pancake/OpenGL/ShaderProgram.hpp \
    include/Pancake/Window/Window.hpp \
    include/Pancake/Pancake.hpp \
    include/Pancake/Graphics/Image.hpp \
    include/Pancake/Graphics/stb/stb_image.h \
    include/Pancake/Graphics/stb/stb_image_write.h \
    include/Pancake/OpenGL/Texture.hpp \
    include/Pancake/Graphics.hpp \
    include/Pancake/OpenGL.hpp \
    include/Pancake/Window.hpp \
    source/OpenGL/GLCheck.hpp \
    include/Pancake/OpenGL/BufferObject.hpp \
    include/Pancake/Window/Context.hpp \
    include/Pancake/Window/ContextSettings.hpp \
    include/Pancake/System/Clipboard.hpp \
    include/Pancake/System.hpp \
    include/Pancake/System/Info.hpp \
    include/Pancake/OpenGL/Extensions.hpp \
    include/Pancake/Window/Display.hpp \
    include/Pancake/System/Library.hpp \
    include/Pancake/Config.hpp
