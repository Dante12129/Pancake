#include "include/Pancake/Graphics/Extensions.hpp"

#include <Pancake/Graphics/OpenGL.hpp>

namespace pcke
{
    namespace ext
    {
        //Shader extensions
        bool programBinary()
        {
            return ogl_IsVersionGEQ(4, 1) || ogl_ext_ARB_get_program_binary;
        }
        bool programInterfaceQuery()
        {
            return ogl_IsVersionGEQ(4, 3) || ogl_ext_ARB_program_interface_query;
        }
        bool separateShaderObjects()
        {
            return ogl_IsVersionGEQ(4, 1) || ogl_ext_ARB_separate_shader_objects;
        }
        bool glsl420Pack()
        {
            return ogl_IsVersionGEQ(4, 2) || ogl_ext_ARB_shading_language_420pack;
        }
        bool shaderSubroutine()
        {
            return ogl_IsVersionGEQ(4, 0) || ogl_ext_ARB_shader_subroutine;
        }
        bool computeShader()
        {
            return ogl_IsVersionGEQ(4, 3) || ogl_ext_ARB_compute_shader;
        }

        //Texture extensions
        bool textureCompressionS3TC()
        {
            return ogl_ext_EXT_texture_compression_s3tc;
        }
        bool textureStorage()
        {
            return ogl_IsVersionGEQ(4, 2) || ogl_ext_ARB_texture_storage;
        }
        bool clearTexture()
        {
            return ogl_IsVersionGEQ(4, 4) || ogl_ext_ARB_clear_texture;
        }

        //Ungrouped extensions
        bool directStateAccess()
        {
            return ogl_IsVersionGEQ(4, 5) || ogl_ext_EXT_direct_state_access;
        }
        bool clearBufferObject()
        {
            return ogl_IsVersionGEQ(4, 3) || ogl_ext_ARB_clear_buffer_object;
        }
        bool viewportArray()
        {
            return ogl_IsVersionGEQ(4, 1) || ogl_ext_ARB_viewport_array;
        }
        bool drawIndirect()
        {
            return ogl_IsVersionGEQ(4, 0) || ogl_ext_ARB_draw_indirect;
        }
    }
}
