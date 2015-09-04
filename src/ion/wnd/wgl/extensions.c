#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "extensions.h"

#if defined(__APPLE__)
#include <mach-o/dyld.h>

static void* AppleGLGetProcAddress (const GLubyte *name)
{
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
	 symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#endif

static int TestPointer(const PROC pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

static PROC WinGetProcAddress(const char *name)
{
	HMODULE glMod = NULL;
	PROC pFunc = wglGetProcAddress((LPCSTR)name);
	if(TestPointer(pFunc))
	{
		return pFunc;
	}
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}
	
#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
	#if defined(__APPLE__)
		#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define IntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
		    #include <GL/glx.h>

			#define IntGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
		#endif
	#endif
#endif

int wgl_ext_ARB_multisample = 0;
int wgl_ext_ARB_extensions_string = 0;
int wgl_ext_ARB_pixel_format = 0;
int wgl_ext_ARB_pixel_format_float = 0;
int wgl_ext_ARB_framebuffer_sRGB = 0;
int wgl_ext_ARB_create_context = 0;
int wgl_ext_ARB_create_context_profile = 0;
int wgl_ext_ARB_create_context_robustness = 0;
int wgl_ext_EXT_swap_control = 0;
int wgl_ext_EXT_pixel_format_packed_float = 0;
int wgl_ext_EXT_create_context_es2_profile = 0;
int wgl_ext_EXT_swap_control_tear = 0;
int wgl_ext_NV_swap_group = 0;

// Extension: ARB_extensions_string
typedef const char * (CODEGEN_FUNCPTR *PFN_PTRC_WGLGETEXTENSIONSSTRINGARBPROC)(HDC);
static const char * CODEGEN_FUNCPTR Switch_GetExtensionsStringARB(HDC hdc);

// Extension: ARB_pixel_format
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLCHOOSEPIXELFORMATARBPROC)(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
static BOOL CODEGEN_FUNCPTR Switch_ChoosePixelFormatARB(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLGETPIXELFORMATATTRIBFVARBPROC)(HDC, int, int, UINT, const int *, FLOAT *);
static BOOL CODEGEN_FUNCPTR Switch_GetPixelFormatAttribfvARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLGETPIXELFORMATATTRIBIVARBPROC)(HDC, int, int, UINT, const int *, int *);
static BOOL CODEGEN_FUNCPTR Switch_GetPixelFormatAttribivARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues);

// Extension: ARB_create_context
typedef HGLRC (CODEGEN_FUNCPTR *PFN_PTRC_WGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
static HGLRC CODEGEN_FUNCPTR Switch_CreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int * attribList);

// Extension: EXT_swap_control
typedef int (CODEGEN_FUNCPTR *PFN_PTRC_WGLGETSWAPINTERVALEXTPROC)();
static int CODEGEN_FUNCPTR Switch_GetSwapIntervalEXT();
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLSWAPINTERVALEXTPROC)(int);
static BOOL CODEGEN_FUNCPTR Switch_SwapIntervalEXT(int interval);

// Extension: NV_swap_group
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLBINDSWAPBARRIERNVPROC)(GLuint, GLuint);
static BOOL CODEGEN_FUNCPTR Switch_BindSwapBarrierNV(GLuint group, GLuint barrier);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLJOINSWAPGROUPNVPROC)(HDC, GLuint);
static BOOL CODEGEN_FUNCPTR Switch_JoinSwapGroupNV(HDC hDC, GLuint group);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLQUERYFRAMECOUNTNVPROC)(HDC, GLuint *);
static BOOL CODEGEN_FUNCPTR Switch_QueryFrameCountNV(HDC hDC, GLuint * count);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLQUERYMAXSWAPGROUPSNVPROC)(HDC, GLuint *, GLuint *);
static BOOL CODEGEN_FUNCPTR Switch_QueryMaxSwapGroupsNV(HDC hDC, GLuint * maxGroups, GLuint * maxBarriers);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLQUERYSWAPGROUPNVPROC)(HDC, GLuint *, GLuint *);
static BOOL CODEGEN_FUNCPTR Switch_QuerySwapGroupNV(HDC hDC, GLuint * group, GLuint * barrier);
typedef BOOL (CODEGEN_FUNCPTR *PFN_PTRC_WGLRESETFRAMECOUNTNVPROC)(HDC);
static BOOL CODEGEN_FUNCPTR Switch_ResetFrameCountNV(HDC hDC);


// Extension: ARB_extensions_string
PFN_PTRC_WGLGETEXTENSIONSSTRINGARBPROC _ptrc_wglGetExtensionsStringARB = Switch_GetExtensionsStringARB;

// Extension: ARB_pixel_format
PFN_PTRC_WGLCHOOSEPIXELFORMATARBPROC _ptrc_wglChoosePixelFormatARB = Switch_ChoosePixelFormatARB;
PFN_PTRC_WGLGETPIXELFORMATATTRIBFVARBPROC _ptrc_wglGetPixelFormatAttribfvARB = Switch_GetPixelFormatAttribfvARB;
PFN_PTRC_WGLGETPIXELFORMATATTRIBIVARBPROC _ptrc_wglGetPixelFormatAttribivARB = Switch_GetPixelFormatAttribivARB;

// Extension: ARB_create_context
PFN_PTRC_WGLCREATECONTEXTATTRIBSARBPROC _ptrc_wglCreateContextAttribsARB = Switch_CreateContextAttribsARB;

// Extension: EXT_swap_control
PFN_PTRC_WGLGETSWAPINTERVALEXTPROC _ptrc_wglGetSwapIntervalEXT = Switch_GetSwapIntervalEXT;
PFN_PTRC_WGLSWAPINTERVALEXTPROC _ptrc_wglSwapIntervalEXT = Switch_SwapIntervalEXT;

// Extension: NV_swap_group
PFN_PTRC_WGLBINDSWAPBARRIERNVPROC _ptrc_wglBindSwapBarrierNV = Switch_BindSwapBarrierNV;
PFN_PTRC_WGLJOINSWAPGROUPNVPROC _ptrc_wglJoinSwapGroupNV = Switch_JoinSwapGroupNV;
PFN_PTRC_WGLQUERYFRAMECOUNTNVPROC _ptrc_wglQueryFrameCountNV = Switch_QueryFrameCountNV;
PFN_PTRC_WGLQUERYMAXSWAPGROUPSNVPROC _ptrc_wglQueryMaxSwapGroupsNV = Switch_QueryMaxSwapGroupsNV;
PFN_PTRC_WGLQUERYSWAPGROUPNVPROC _ptrc_wglQuerySwapGroupNV = Switch_QuerySwapGroupNV;
PFN_PTRC_WGLRESETFRAMECOUNTNVPROC _ptrc_wglResetFrameCountNV = Switch_ResetFrameCountNV;


// Extension: ARB_extensions_string
static const char * CODEGEN_FUNCPTR Switch_GetExtensionsStringARB(HDC hdc)
{
  _ptrc_wglGetExtensionsStringARB = (PFN_PTRC_WGLGETEXTENSIONSSTRINGARBPROC)IntGetProcAddress("wglGetExtensionsStringARB");
  return _ptrc_wglGetExtensionsStringARB(hdc);
}


// Extension: ARB_pixel_format
static BOOL CODEGEN_FUNCPTR Switch_ChoosePixelFormatARB(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats)
{
  _ptrc_wglChoosePixelFormatARB = (PFN_PTRC_WGLCHOOSEPIXELFORMATARBPROC)IntGetProcAddress("wglChoosePixelFormatARB");
  return _ptrc_wglChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
}

static BOOL CODEGEN_FUNCPTR Switch_GetPixelFormatAttribfvARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues)
{
  _ptrc_wglGetPixelFormatAttribfvARB = (PFN_PTRC_WGLGETPIXELFORMATATTRIBFVARBPROC)IntGetProcAddress("wglGetPixelFormatAttribfvARB");
  return _ptrc_wglGetPixelFormatAttribfvARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues);
}

static BOOL CODEGEN_FUNCPTR Switch_GetPixelFormatAttribivARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues)
{
  _ptrc_wglGetPixelFormatAttribivARB = (PFN_PTRC_WGLGETPIXELFORMATATTRIBIVARBPROC)IntGetProcAddress("wglGetPixelFormatAttribivARB");
  return _ptrc_wglGetPixelFormatAttribivARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues);
}


// Extension: ARB_create_context
static HGLRC CODEGEN_FUNCPTR Switch_CreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int * attribList)
{
  _ptrc_wglCreateContextAttribsARB = (PFN_PTRC_WGLCREATECONTEXTATTRIBSARBPROC)IntGetProcAddress("wglCreateContextAttribsARB");
  return _ptrc_wglCreateContextAttribsARB(hDC, hShareContext, attribList);
}


// Extension: EXT_swap_control
static int CODEGEN_FUNCPTR Switch_GetSwapIntervalEXT()
{
  _ptrc_wglGetSwapIntervalEXT = (PFN_PTRC_WGLGETSWAPINTERVALEXTPROC)IntGetProcAddress("wglGetSwapIntervalEXT");
  return _ptrc_wglGetSwapIntervalEXT();
}

static BOOL CODEGEN_FUNCPTR Switch_SwapIntervalEXT(int interval)
{
  _ptrc_wglSwapIntervalEXT = (PFN_PTRC_WGLSWAPINTERVALEXTPROC)IntGetProcAddress("wglSwapIntervalEXT");
  return _ptrc_wglSwapIntervalEXT(interval);
}


// Extension: NV_swap_group
static BOOL CODEGEN_FUNCPTR Switch_BindSwapBarrierNV(GLuint group, GLuint barrier)
{
  _ptrc_wglBindSwapBarrierNV = (PFN_PTRC_WGLBINDSWAPBARRIERNVPROC)IntGetProcAddress("wglBindSwapBarrierNV");
  return _ptrc_wglBindSwapBarrierNV(group, barrier);
}

static BOOL CODEGEN_FUNCPTR Switch_JoinSwapGroupNV(HDC hDC, GLuint group)
{
  _ptrc_wglJoinSwapGroupNV = (PFN_PTRC_WGLJOINSWAPGROUPNVPROC)IntGetProcAddress("wglJoinSwapGroupNV");
  return _ptrc_wglJoinSwapGroupNV(hDC, group);
}

static BOOL CODEGEN_FUNCPTR Switch_QueryFrameCountNV(HDC hDC, GLuint * count)
{
  _ptrc_wglQueryFrameCountNV = (PFN_PTRC_WGLQUERYFRAMECOUNTNVPROC)IntGetProcAddress("wglQueryFrameCountNV");
  return _ptrc_wglQueryFrameCountNV(hDC, count);
}

static BOOL CODEGEN_FUNCPTR Switch_QueryMaxSwapGroupsNV(HDC hDC, GLuint * maxGroups, GLuint * maxBarriers)
{
  _ptrc_wglQueryMaxSwapGroupsNV = (PFN_PTRC_WGLQUERYMAXSWAPGROUPSNVPROC)IntGetProcAddress("wglQueryMaxSwapGroupsNV");
  return _ptrc_wglQueryMaxSwapGroupsNV(hDC, maxGroups, maxBarriers);
}

static BOOL CODEGEN_FUNCPTR Switch_QuerySwapGroupNV(HDC hDC, GLuint * group, GLuint * barrier)
{
  _ptrc_wglQuerySwapGroupNV = (PFN_PTRC_WGLQUERYSWAPGROUPNVPROC)IntGetProcAddress("wglQuerySwapGroupNV");
  return _ptrc_wglQuerySwapGroupNV(hDC, group, barrier);
}

static BOOL CODEGEN_FUNCPTR Switch_ResetFrameCountNV(HDC hDC)
{
  _ptrc_wglResetFrameCountNV = (PFN_PTRC_WGLRESETFRAMECOUNTNVPROC)IntGetProcAddress("wglResetFrameCountNV");
  return _ptrc_wglResetFrameCountNV(hDC);
}



static void ClearExtensionVariables()
{
  wgl_ext_ARB_multisample = 0;
  wgl_ext_ARB_extensions_string = 0;
  wgl_ext_ARB_pixel_format = 0;
  wgl_ext_ARB_pixel_format_float = 0;
  wgl_ext_ARB_framebuffer_sRGB = 0;
  wgl_ext_ARB_create_context = 0;
  wgl_ext_ARB_create_context_profile = 0;
  wgl_ext_ARB_create_context_robustness = 0;
  wgl_ext_EXT_swap_control = 0;
  wgl_ext_EXT_pixel_format_packed_float = 0;
  wgl_ext_EXT_create_context_es2_profile = 0;
  wgl_ext_EXT_swap_control_tear = 0;
  wgl_ext_NV_swap_group = 0;
}

typedef struct wgl_MapTable_s
{
	char *extName;
	int *extVariable;
}wgl_MapTable;

static wgl_MapTable g_mappingTable[13] = 
{
  {"WGL_ARB_multisample", &wgl_ext_ARB_multisample},
  {"WGL_ARB_extensions_string", &wgl_ext_ARB_extensions_string},
  {"WGL_ARB_pixel_format", &wgl_ext_ARB_pixel_format},
  {"WGL_ARB_pixel_format_float", &wgl_ext_ARB_pixel_format_float},
  {"WGL_ARB_framebuffer_sRGB", &wgl_ext_ARB_framebuffer_sRGB},
  {"WGL_ARB_create_context", &wgl_ext_ARB_create_context},
  {"WGL_ARB_create_context_profile", &wgl_ext_ARB_create_context_profile},
  {"WGL_ARB_create_context_robustness", &wgl_ext_ARB_create_context_robustness},
  {"WGL_EXT_swap_control", &wgl_ext_EXT_swap_control},
  {"WGL_EXT_pixel_format_packed_float", &wgl_ext_EXT_pixel_format_packed_float},
  {"WGL_EXT_create_context_es2_profile", &wgl_ext_EXT_create_context_es2_profile},
  {"WGL_EXT_swap_control_tear", &wgl_ext_EXT_swap_control_tear},
  {"WGL_NV_swap_group", &wgl_ext_NV_swap_group},
};

static void LoadExtByName(const char *extensionName)
{
	wgl_MapTable *tableEnd = &g_mappingTable[13];
	wgl_MapTable *entry = &g_mappingTable[0];
	for(; entry != tableEnd; ++entry)
	{
		if(strcmp(entry->extName, extensionName) == 0)
			break;
	}
	
	if(entry != tableEnd)
		*(entry->extVariable) = 1;
}

static void ProcExtsFromExtString(const char *strExtList)
{
	size_t iExtListLen = strlen(strExtList);
	const char *strExtListEnd = strExtList + iExtListLen;
	const char *strCurrPos = strExtList;
	char strWorkBuff[256];

	while(*strCurrPos)
	{
		/*Get the extension at our position.*/
		int iStrLen = 0;
		const char *strEndStr = strchr(strCurrPos, ' ');
		int iStop = 0;
		if(strEndStr == NULL)
		{
			strEndStr = strExtListEnd;
			iStop = 1;
		}

		iStrLen = (int)((ptrdiff_t)strEndStr - (ptrdiff_t)strCurrPos);

		if(iStrLen > 255)
			return;

		strncpy(strWorkBuff, strCurrPos, iStrLen);
		strWorkBuff[iStrLen] = '\0';

		LoadExtByName(strWorkBuff);

		strCurrPos = strEndStr + 1;
		if(iStop) break;
	}
}

void wgl_CheckExtensions(HDC hdc)
{
  ClearExtensionVariables();
  
  {
    typedef const char * (CODEGEN_FUNCPTR *MYGETEXTSTRINGPROC)(HDC);
    MYGETEXTSTRINGPROC InternalGetExtensionString = (MYGETEXTSTRINGPROC)IntGetProcAddress("wglGetExtensionsStringARB");
    if(!InternalGetExtensionString) return;
    ProcExtsFromExtString((const char *)InternalGetExtensionString(hdc));
  }
}
