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
    LIBS += -L$${LIBS_PATH}
    INCLUDEPATH += include $$INC_PATH
    DEPENDPATH += include $$INC_PATH
}

unix:!macx{
    LIBS += -L$${LIBS_PATH}
    INCLUDEPATH += include $$INC_PATH
    DEPENDPATH += include $$INC_PATH
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
    source/Graphics/Image.cpp \
    source/Window/Context.cpp \
    source/Window/ContextSettings.cpp \
    source/System/Clipboard.cpp \
    source/System/Info.cpp \
    source/Window/Display.cpp \
    source/System/Library.cpp \
    source/Graphics/BufferObject.cpp \
    source/Graphics/Extensions.cpp \
    source/Graphics/GLCheck.cpp \
    source/Graphics/Shader.cpp \
    source/Graphics/ShaderProgram.cpp \
    source/Graphics/Texture.cpp

HEADERS += \
    include/Pancake/Graphics/Color.hpp \
    include/Pancake/Graphics/Vertex.hpp \
    include/Pancake/Window/Window.hpp \
    include/Pancake/Pancake.hpp \
    include/Pancake/Graphics/Image.hpp \
    include/Pancake/Graphics/stb/stb_image.h \
    include/Pancake/Graphics/stb/stb_image_write.h \
    include/Pancake/Graphics.hpp \
    include/Pancake/Window.hpp \
    include/Pancake/Window/Context.hpp \
    include/Pancake/Window/ContextSettings.hpp \
    include/Pancake/System/Clipboard.hpp \
    include/Pancake/System.hpp \
    include/Pancake/System/Info.hpp \
    include/Pancake/Window/Display.hpp \
    include/Pancake/System/Library.hpp \
    include/Pancake/Config.hpp \
    include/Pancake/Graphics/BufferObject.hpp \
    include/Pancake/Graphics/Extensions.hpp \
    include/Pancake/Graphics/Shader.hpp \
    include/Pancake/Graphics/ShaderProgram.hpp \
    include/Pancake/Graphics/Texture.hpp \
    include/Pancake/DocMain.hpp \
    source/Graphics/stb/stb_image.h \
    source/Graphics/stb/stb_image_write.h \
    source/Graphics/GLCheck.hpp
