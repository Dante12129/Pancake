#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T10:14:57
#
#-------------------------------------------------

QT       -= core gui

CONFIG(release, debug|release): TARGET = pancake
CONFIG(debug, debug|release): TARGET = pancake-d
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-unused-variable

LIBS += -LC:/SDL/lib -LC:/GL/SDK/lib

CONFIG(debug, debug|release): LIBS += -Wl,--whole-archive -lglutilD -lglloadD -Wl,--no-whole-archive
CONFIG(release, debug|release): LIBS += -Wl,--whole-archive -lglutil -lglload -Wl,--no-whole-archive
LIBS += -lmingw32 -lSDL2main -lSDL2 -lopengl32

INCLUDEPATH += include C:/SDL/include C:/GL/glm C:/GL/SDK/include
DEPENDPATH += include C:/SDL/include C:/GL/glm C:/GL/SDK/include

SOURCES += \
    source/Graphics/Color.cpp \
    source/Graphics/Vertex.cpp \
    source/OpenGL/Vbo.cpp \
    source/Window/Window.cpp \
    source/Pancake.cpp \
    source/OpenGL/Shader.cpp \
    source/OpenGL/ShaderProgram.cpp \
    source/Graphics/Image.cpp \
    source/OpenGL/Texture.cpp

HEADERS += \
    include/Pancake/Graphics/Color.hpp \
    include/Pancake/Graphics/Vertex.hpp \
    include/Pancake/OpenGL/Shader.hpp \
    include/Pancake/OpenGL/ShaderProgram.hpp \
    include/Pancake/OpenGL/Vbo.hpp \
    include/Pancake/Window/Window.hpp \
    include/Pancake/Pancake.hpp \
    include/Pancake/Graphics/Image.hpp \
    include/Pancake/Graphics/stb/stb_image.h \
    include/Pancake/Graphics/stb/stb_image_write.h \
    include/Pancake/OpenGL/Texture.hpp
