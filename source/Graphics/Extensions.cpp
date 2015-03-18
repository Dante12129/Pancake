#include "include/Pancake/Graphics/Extensions.hpp"

#include <glload/gl_load.h>
#include <glload/gl_3_3.h>

namespace pcke
{
    namespace ext
    {
        //Shader extensions
        bool programBinary()
        {
            return ogl_IsVersionGEQ(4, 1) || glext_ARB_get_program_binary;
        }
        bool programInterfaceQuery()
        {
            return ogl_IsVersionGEQ(4, 3) || glext_ARB_program_interface_query;
        }
        bool separateShaderObjects()
        {
            return ogl_IsVersionGEQ(4, 1) || glext_ARB_separate_shader_objects;
        }
        bool glsl420Pack()
        {
            return ogl_IsVersionGEQ(4, 2) || glext_ARB_shading_language_420pack;
        }
        bool shaderSubroutine()
        {
            return ogl_IsVersionGEQ(4, 0) || glext_ARB_shader_subroutine;
        }
        bool computeShader()
        {
            return ogl_IsVersionGEQ(4, 3) || glext_ARB_compute_shader;
        }

        //Texture extensions
        bool textureCompressionS3TC()
        {
            return glext_EXT_texture_compression_s3tc;
        }
        bool textureStorage()
        {
            return ogl_IsVersionGEQ(4, 2) || glext_ARB_texture_storage;
        }
        bool clearTexture()
        {
            return ogl_IsVersionGEQ(4, 4) || glext_ARB_clear_texture;
        }

        //Ungrouped extensions
        bool directStateAccess()
        {
            return ogl_IsVersionGEQ(4, 5) || glext_EXT_direct_state_access;
        }
        bool clearBufferObject()
        {
            return ogl_IsVersionGEQ(4, 3) || glext_ARB_clear_buffer_object;
        }
        bool viewportArray()
        {
            return ogl_IsVersionGEQ(4, 1) || glext_ARB_viewport_array;
        }
        bool drawIndirect()
        {
            return ogl_IsVersionGEQ(4, 0) || glext_ARB_draw_indirect;
        }
    }
}
