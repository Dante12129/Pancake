#ifndef EXTENSIONS_HPP
#define EXTENSIONS_HPP

namespace pcke
{
    namespace ext
    {
        //Shader extensions
        bool programBinary();
        bool programInterfaceQuery();
        bool separateShaderObjects();
        bool glsl420Pack();
        bool shaderSubroutine();
        bool computeShader();

        //Texture extensions
        bool textureCompressionS3TC();
        bool textureStorage();
        bool clearTexture();

        //Ungrouped extensions
        bool directStateAccess();
        bool clearBufferObject();
        bool viewportArray();
        bool drawIndirect();

    }
}

#endif // EXTENSIONS_HPP
