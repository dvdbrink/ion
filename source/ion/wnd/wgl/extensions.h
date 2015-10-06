#ifndef WINDOWSGL_NOLOAD_STYLE_H
#define WINDOWSGL_NOLOAD_STYLE_H

#ifdef __wglext_h_
#error Attempt to include auto-generated WGL header after wglext.h
#endif

#define __wglext_h_

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX
	#define NOMINMAX
#endif
#include <windows.h>

#ifdef CODEGEN_FUNCPTR
#undef CODEGEN_FUNCPTR
#endif /*CODEGEN_FUNCPTR*/
#define CODEGEN_FUNCPTR WINAPI

#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
#define GLvoid void

#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/


#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS


#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/

struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
};
DECLARE_HANDLE(HPBUFFERARB);
DECLARE_HANDLE(HPBUFFEREXT);
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
DECLARE_HANDLE(HPVIDEODEV);
DECLARE_HANDLE(HGPUNV);
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
typedef struct _GPU_DEVICE *PGPU_DEVICE;

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/////////////////////////
// Extension Variables

extern int wgl_ext_ARB_multisample;
extern int wgl_ext_ARB_extensions_string;
extern int wgl_ext_ARB_pixel_format;
extern int wgl_ext_ARB_pixel_format_float;
extern int wgl_ext_ARB_framebuffer_sRGB;
extern int wgl_ext_ARB_create_context;
extern int wgl_ext_ARB_create_context_profile;
extern int wgl_ext_ARB_create_context_robustness;
extern int wgl_ext_EXT_swap_control;
extern int wgl_ext_EXT_pixel_format_packed_float;
extern int wgl_ext_EXT_create_context_es2_profile;
extern int wgl_ext_EXT_swap_control_tear;
extern int wgl_ext_NV_swap_group;

// Extension: ARB_multisample
#define WGL_SAMPLES_ARB                  0x2042
#define WGL_SAMPLE_BUFFERS_ARB           0x2041

// Extension: ARB_pixel_format
#define WGL_ACCELERATION_ARB             0x2003
#define WGL_ACCUM_ALPHA_BITS_ARB         0x2021
#define WGL_ACCUM_BITS_ARB               0x201D
#define WGL_ACCUM_BLUE_BITS_ARB          0x2020
#define WGL_ACCUM_GREEN_BITS_ARB         0x201F
#define WGL_ACCUM_RED_BITS_ARB           0x201E
#define WGL_ALPHA_BITS_ARB               0x201B
#define WGL_ALPHA_SHIFT_ARB              0x201C
#define WGL_AUX_BUFFERS_ARB              0x2024
#define WGL_BLUE_BITS_ARB                0x2019
#define WGL_BLUE_SHIFT_ARB               0x201A
#define WGL_COLOR_BITS_ARB               0x2014
#define WGL_DEPTH_BITS_ARB               0x2022
#define WGL_DOUBLE_BUFFER_ARB            0x2011
#define WGL_DRAW_TO_BITMAP_ARB           0x2002
#define WGL_DRAW_TO_WINDOW_ARB           0x2001
#define WGL_FULL_ACCELERATION_ARB        0x2027
#define WGL_GENERIC_ACCELERATION_ARB     0x2026
#define WGL_GREEN_BITS_ARB               0x2017
#define WGL_GREEN_SHIFT_ARB              0x2018
#define WGL_NEED_PALETTE_ARB             0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB      0x2005
#define WGL_NO_ACCELERATION_ARB          0x2025
#define WGL_NUMBER_OVERLAYS_ARB          0x2008
#define WGL_NUMBER_PIXEL_FORMATS_ARB     0x2000
#define WGL_NUMBER_UNDERLAYS_ARB         0x2009
#define WGL_PIXEL_TYPE_ARB               0x2013
#define WGL_RED_BITS_ARB                 0x2015
#define WGL_RED_SHIFT_ARB                0x2016
#define WGL_SHARE_ACCUM_ARB              0x200E
#define WGL_SHARE_DEPTH_ARB              0x200C
#define WGL_SHARE_STENCIL_ARB            0x200D
#define WGL_STENCIL_BITS_ARB             0x2023
#define WGL_STEREO_ARB                   0x2012
#define WGL_SUPPORT_GDI_ARB              0x200F
#define WGL_SUPPORT_OPENGL_ARB           0x2010
#define WGL_SWAP_COPY_ARB                0x2029
#define WGL_SWAP_EXCHANGE_ARB            0x2028
#define WGL_SWAP_LAYER_BUFFERS_ARB       0x2006
#define WGL_SWAP_METHOD_ARB              0x2007
#define WGL_SWAP_UNDEFINED_ARB           0x202A
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB  0x203A
#define WGL_TRANSPARENT_ARB              0x200A
#define WGL_TRANSPARENT_BLUE_VALUE_ARB   0x2039
#define WGL_TRANSPARENT_GREEN_VALUE_ARB  0x2038
#define WGL_TRANSPARENT_INDEX_VALUE_ARB  0x203B
#define WGL_TRANSPARENT_RED_VALUE_ARB    0x2037
#define WGL_TYPE_COLORINDEX_ARB          0x202C
#define WGL_TYPE_RGBA_ARB                0x202B

// Extension: ARB_pixel_format_float
#define WGL_TYPE_RGBA_FLOAT_ARB          0x21A0

// Extension: ARB_framebuffer_sRGB
#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9

// Extension: ARB_create_context
#define WGL_CONTEXT_DEBUG_BIT_ARB        0x00000001
#define WGL_CONTEXT_FLAGS_ARB            0x2094
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_LAYER_PLANE_ARB      0x2093
#define WGL_CONTEXT_MAJOR_VERSION_ARB    0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB    0x2092
#define WGL_ERROR_INVALID_VERSION_ARB    0x2095

// Extension: ARB_create_context_profile
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB     0x9126
#define WGL_ERROR_INVALID_PROFILE_ARB    0x2096

// Extension: ARB_create_context_robustness
#define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#define WGL_LOSE_CONTEXT_ON_RESET_ARB    0x8252
#define WGL_NO_RESET_NOTIFICATION_ARB    0x8261

// Extension: EXT_pixel_format_packed_float
#define WGL_TYPE_RGBA_UNSIGNED_FLOAT_EXT 0x20A8

// Extension: EXT_create_context_es2_profile
#define WGL_CONTEXT_ES2_PROFILE_BIT_EXT  0x00000004


// Extension: ARB_extensions_string
extern const char * (CODEGEN_FUNCPTR *_ptrc_wglGetExtensionsStringARB)(HDC hdc);
#define wglGetExtensionsStringARB _ptrc_wglGetExtensionsStringARB

// Extension: ARB_pixel_format
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglChoosePixelFormatARB)(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
#define wglChoosePixelFormatARB _ptrc_wglChoosePixelFormatARB
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglGetPixelFormatAttribfvARB)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues);
#define wglGetPixelFormatAttribfvARB _ptrc_wglGetPixelFormatAttribfvARB
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglGetPixelFormatAttribivARB)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues);
#define wglGetPixelFormatAttribivARB _ptrc_wglGetPixelFormatAttribivARB

// Extension: ARB_create_context
extern HGLRC (CODEGEN_FUNCPTR *_ptrc_wglCreateContextAttribsARB)(HDC hDC, HGLRC hShareContext, const int * attribList);
#define wglCreateContextAttribsARB _ptrc_wglCreateContextAttribsARB

// Extension: EXT_swap_control
extern int (CODEGEN_FUNCPTR *_ptrc_wglGetSwapIntervalEXT)();
#define wglGetSwapIntervalEXT _ptrc_wglGetSwapIntervalEXT
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglSwapIntervalEXT)(int interval);
#define wglSwapIntervalEXT _ptrc_wglSwapIntervalEXT

// Extension: NV_swap_group
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglBindSwapBarrierNV)(GLuint group, GLuint barrier);
#define wglBindSwapBarrierNV _ptrc_wglBindSwapBarrierNV
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglJoinSwapGroupNV)(HDC hDC, GLuint group);
#define wglJoinSwapGroupNV _ptrc_wglJoinSwapGroupNV
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglQueryFrameCountNV)(HDC hDC, GLuint * count);
#define wglQueryFrameCountNV _ptrc_wglQueryFrameCountNV
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglQueryMaxSwapGroupsNV)(HDC hDC, GLuint * maxGroups, GLuint * maxBarriers);
#define wglQueryMaxSwapGroupsNV _ptrc_wglQueryMaxSwapGroupsNV
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglQuerySwapGroupNV)(HDC hDC, GLuint * group, GLuint * barrier);
#define wglQuerySwapGroupNV _ptrc_wglQuerySwapGroupNV
extern BOOL (CODEGEN_FUNCPTR *_ptrc_wglResetFrameCountNV)(HDC hDC);
#define wglResetFrameCountNV _ptrc_wglResetFrameCountNV

void wgl_CheckExtensions(HDC hdc);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //WINDOWSGL_NOLOAD_STYLE_H
