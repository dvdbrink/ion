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

int glx_ext_ARB_create_context = 0;
int glx_ext_ARB_create_context_profile = 0;
int glx_ext_ARB_create_context_robustness = 0;
int glx_ext_ARB_fbconfig_float = 0;
int glx_ext_ARB_framebuffer_sRGB = 0;
int glx_ext_ARB_multisample = 0;
int glx_ext_EXT_create_context_es2_profile = 0;
int glx_ext_EXT_fbconfig_packed_float = 0;
int glx_ext_EXT_framebuffer_sRGB = 0;
int glx_ext_EXT_import_context = 0;
int glx_ext_EXT_swap_control = 0;
int glx_ext_EXT_swap_control_tear = 0;

// Extension: ARB_create_context
typedef GLXContext (CODEGEN_FUNCPTR *PFN_PTRC_GLXCREATECONTEXTATTRIBSARBPROC)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
static GLXContext CODEGEN_FUNCPTR Switch_CreateContextAttribsARB(Display * dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int * attrib_list);

// Extension: EXT_import_context
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLXFREECONTEXTEXTPROC)(Display *, GLXContext);
static void CODEGEN_FUNCPTR Switch_FreeContextEXT(Display * dpy, GLXContext context);
typedef GLXContextID (CODEGEN_FUNCPTR *PFN_PTRC_GLXGETCONTEXTIDEXTPROC)(const GLXContext);
static GLXContextID CODEGEN_FUNCPTR Switch_GetContextIDEXT(const GLXContext context);
typedef Display * (CODEGEN_FUNCPTR *PFN_PTRC_GLXGETCURRENTDISPLAYEXTPROC)();
static Display * CODEGEN_FUNCPTR Switch_GetCurrentDisplayEXT();
typedef GLXContext (CODEGEN_FUNCPTR *PFN_PTRC_GLXIMPORTCONTEXTEXTPROC)(Display *, GLXContextID);
static GLXContext CODEGEN_FUNCPTR Switch_ImportContextEXT(Display * dpy, GLXContextID contextID);
typedef int (CODEGEN_FUNCPTR *PFN_PTRC_GLXQUERYCONTEXTINFOEXTPROC)(Display *, GLXContext, int, int *);
static int CODEGEN_FUNCPTR Switch_QueryContextInfoEXT(Display * dpy, GLXContext context, int attribute, int * value);

// Extension: EXT_swap_control
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLXSWAPINTERVALEXTPROC)(Display *, GLXDrawable, int);
static void CODEGEN_FUNCPTR Switch_SwapIntervalEXT(Display * dpy, GLXDrawable drawable, int interval);


// Extension: ARB_create_context
PFN_PTRC_GLXCREATECONTEXTATTRIBSARBPROC _ptrc_glXCreateContextAttribsARB = Switch_CreateContextAttribsARB;

// Extension: EXT_import_context
PFN_PTRC_GLXFREECONTEXTEXTPROC _ptrc_glXFreeContextEXT = Switch_FreeContextEXT;
PFN_PTRC_GLXGETCONTEXTIDEXTPROC _ptrc_glXGetContextIDEXT = Switch_GetContextIDEXT;
PFN_PTRC_GLXGETCURRENTDISPLAYEXTPROC _ptrc_glXGetCurrentDisplayEXT = Switch_GetCurrentDisplayEXT;
PFN_PTRC_GLXIMPORTCONTEXTEXTPROC _ptrc_glXImportContextEXT = Switch_ImportContextEXT;
PFN_PTRC_GLXQUERYCONTEXTINFOEXTPROC _ptrc_glXQueryContextInfoEXT = Switch_QueryContextInfoEXT;

// Extension: EXT_swap_control
PFN_PTRC_GLXSWAPINTERVALEXTPROC _ptrc_glXSwapIntervalEXT = Switch_SwapIntervalEXT;


// Extension: ARB_create_context
static GLXContext CODEGEN_FUNCPTR Switch_CreateContextAttribsARB(Display * dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int * attrib_list)
{
  _ptrc_glXCreateContextAttribsARB = (PFN_PTRC_GLXCREATECONTEXTATTRIBSARBPROC)IntGetProcAddress("glXCreateContextAttribsARB");
  return _ptrc_glXCreateContextAttribsARB(dpy, config, share_context, direct, attrib_list);
}


// Extension: EXT_import_context
static void CODEGEN_FUNCPTR Switch_FreeContextEXT(Display * dpy, GLXContext context)
{
  _ptrc_glXFreeContextEXT = (PFN_PTRC_GLXFREECONTEXTEXTPROC)IntGetProcAddress("glXFreeContextEXT");
  _ptrc_glXFreeContextEXT(dpy, context);
}

static GLXContextID CODEGEN_FUNCPTR Switch_GetContextIDEXT(const GLXContext context)
{
  _ptrc_glXGetContextIDEXT = (PFN_PTRC_GLXGETCONTEXTIDEXTPROC)IntGetProcAddress("glXGetContextIDEXT");
  return _ptrc_glXGetContextIDEXT(context);
}

static Display * CODEGEN_FUNCPTR Switch_GetCurrentDisplayEXT()
{
  _ptrc_glXGetCurrentDisplayEXT = (PFN_PTRC_GLXGETCURRENTDISPLAYEXTPROC)IntGetProcAddress("glXGetCurrentDisplayEXT");
  return _ptrc_glXGetCurrentDisplayEXT();
}

static GLXContext CODEGEN_FUNCPTR Switch_ImportContextEXT(Display * dpy, GLXContextID contextID)
{
  _ptrc_glXImportContextEXT = (PFN_PTRC_GLXIMPORTCONTEXTEXTPROC)IntGetProcAddress("glXImportContextEXT");
  return _ptrc_glXImportContextEXT(dpy, contextID);
}

static int CODEGEN_FUNCPTR Switch_QueryContextInfoEXT(Display * dpy, GLXContext context, int attribute, int * value)
{
  _ptrc_glXQueryContextInfoEXT = (PFN_PTRC_GLXQUERYCONTEXTINFOEXTPROC)IntGetProcAddress("glXQueryContextInfoEXT");
  return _ptrc_glXQueryContextInfoEXT(dpy, context, attribute, value);
}


// Extension: EXT_swap_control
static void CODEGEN_FUNCPTR Switch_SwapIntervalEXT(Display * dpy, GLXDrawable drawable, int interval)
{
  _ptrc_glXSwapIntervalEXT = (PFN_PTRC_GLXSWAPINTERVALEXTPROC)IntGetProcAddress("glXSwapIntervalEXT");
  _ptrc_glXSwapIntervalEXT(dpy, drawable, interval);
}



static void ClearExtensionVariables()
{
  glx_ext_ARB_create_context = 0;
  glx_ext_ARB_create_context_profile = 0;
  glx_ext_ARB_create_context_robustness = 0;
  glx_ext_ARB_fbconfig_float = 0;
  glx_ext_ARB_framebuffer_sRGB = 0;
  glx_ext_ARB_multisample = 0;
  glx_ext_EXT_create_context_es2_profile = 0;
  glx_ext_EXT_fbconfig_packed_float = 0;
  glx_ext_EXT_framebuffer_sRGB = 0;
  glx_ext_EXT_import_context = 0;
  glx_ext_EXT_swap_control = 0;
  glx_ext_EXT_swap_control_tear = 0;
}

typedef struct glx_MapTable_s
{
	char *extName;
	int *extVariable;
}glx_MapTable;

static glx_MapTable g_mappingTable[12] = 
{
  {"GLX_ARB_create_context", &glx_ext_ARB_create_context},
  {"GLX_ARB_create_context_profile", &glx_ext_ARB_create_context_profile},
  {"GLX_ARB_create_context_robustness", &glx_ext_ARB_create_context_robustness},
  {"GLX_ARB_fbconfig_float", &glx_ext_ARB_fbconfig_float},
  {"GLX_ARB_framebuffer_sRGB", &glx_ext_ARB_framebuffer_sRGB},
  {"GLX_ARB_multisample", &glx_ext_ARB_multisample},
  {"GLX_EXT_create_context_es2_profile", &glx_ext_EXT_create_context_es2_profile},
  {"GLX_EXT_fbconfig_packed_float", &glx_ext_EXT_fbconfig_packed_float},
  {"GLX_EXT_framebuffer_sRGB", &glx_ext_EXT_framebuffer_sRGB},
  {"GLX_EXT_import_context", &glx_ext_EXT_import_context},
  {"GLX_EXT_swap_control", &glx_ext_EXT_swap_control},
  {"GLX_EXT_swap_control_tear", &glx_ext_EXT_swap_control_tear},
};

static void LoadExtByName(const char *extensionName)
{
	glx_MapTable *tableEnd = &g_mappingTable[12];
	glx_MapTable *entry = &g_mappingTable[0];
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

void glx_CheckExtensions(Display *display, int screen)
{
  ClearExtensionVariables();
  
  {
    ProcExtsFromExtString((const char *)glXQueryExtensionsString(display, screen));
  }
}
