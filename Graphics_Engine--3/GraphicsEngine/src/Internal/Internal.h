//#include "glfw3.h"
//
//
//
//
//
//typedef int GLFWbool;
//typedef struct _GLFWmonitor     _GLFWmonitor;
//typedef struct _GLFWcontext     _GLFWcontext;
//
////typedef void (*_GLFWmakecontextcurrentfun)(_GLFWwindow*);
////typedef void (*_GLFWswapbuffersfun)(_GLFWwindow*);
////typedef void (*_GLFWswapintervalfun)(int);
////typedef int (*_GLFWextensionsupportedfun)(const char*);
////typedef GLFWglproc(*_GLFWgetprocaddressfun)(const char*);
////typedef void (*_GLFWdestroycontextfun)(_GLFWwindow*);
//
//
//typedef void (APIENTRY* PFNGLCLEARPROC)(GLbitfield);
//typedef const GLubyte* (APIENTRY* PFNGLGETSTRINGPROC)(GLenum);
//typedef void (APIENTRY* PFNGLGETINTEGERVPROC)(GLenum, GLint*);
//typedef const GLubyte* (APIENTRY* PFNGLGETSTRINGIPROC)(GLenum, GLuint);
//
//struct _GLFWcontext
//{
//    int                 client;
//    int                 source;
//    int                 major, minor, revision;
//    GLFWbool            forward, debug, noerror;
//    int                 profile;
//    int                 robustness;
//    int                 release;
//
//    PFNGLGETSTRINGIPROC  GetStringi;
//    PFNGLGETINTEGERVPROC GetIntegerv;
//    PFNGLGETSTRINGPROC   GetString;
//
//    //_GLFWmakecontextcurrentfun  makeCurrent;
//    //_GLFWswapbuffersfun         swapBuffers;
//    //_GLFWswapintervalfun        swapInterval;
//    //_GLFWextensionsupportedfun  extensionSupported;
//    //_GLFWgetprocaddressfun      getProcAddress;
//    //_GLFWdestroycontextfun      destroy;
//
//#define _GLFW_STICK 3
//
//};
//
//struct _GLFWwindow
//{
//    struct _GLFWwindow* next;
//
//    // Window settings and state
//    GLFWbool            resizable;
//    GLFWbool            decorated;
//    GLFWbool            autoIconify;
//    GLFWbool            floating;
//    GLFWbool            focusOnShow;
//    GLFWbool            mousePassthrough;
//    GLFWbool            shouldClose;
//    void* userPointer;
//    GLFWbool            doublebuffer;
//    GLFWvidmode         videoMode;
//    _GLFWmonitor* monitor;
//    _GLFWcursor* cursor;
//
//    int                 minwidth, minheight;
//    int                 maxwidth, maxheight;
//    int                 numer, denom;
//
//    GLFWbool            stickyKeys;
//    GLFWbool            stickyMouseButtons;
//    GLFWbool            lockKeyMods;
//    int                 cursorMode;
//    char                mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
//    char                keys[GLFW_KEY_LAST + 1];
//    // Virtual cursor position when cursor is disabled
//    double              virtualCursorPosX, virtualCursorPosY;
//    GLFWbool            rawMouseMotion;
//
//    _GLFWcontext        context;
//
//    struct {
//        GLFWwindowposfun          pos;
//        GLFWwindowsizefun         size;
//        GLFWwindowclosefun        close;
//        GLFWwindowrefreshfun      refresh;
//        GLFWwindowfocusfun        focus;
//        GLFWwindowiconifyfun      iconify;
//        GLFWwindowmaximizefun     maximize;
//        GLFWframebuffersizefun    fbsize;
//        GLFWwindowcontentscalefun scale;
//        GLFWmousebuttonfun        mouseButton;
//        GLFWcursorposfun          cursorPos;
//        GLFWcursorenterfun        cursorEnter;
//        GLFWscrollfun             scroll;
//        GLFWkeyfun                key;
//        GLFWcharfun               character;
//        GLFWcharmodsfun           charmods;
//        GLFWdropfun               drop;
//    } callbacks;
//
//};
//
//struct _GLFWcursor
//{
//    _GLFWcursor* next;
//
//};
//struct _GLFWmonitor
//{
//    char            name[128];
//    void* userPointer;
//
//    // Physical dimensions in millimeters.
//    int             widthMM, heightMM;
//
//    // The window whose video mode is current on this monitor
//    _GLFWwindow* window;
//
//    GLFWvidmode* modes;
//    int             modeCount;
//    GLFWvidmode     currentMode;
//
//    GLFWgammaramp   originalRamp;
//    GLFWgammaramp   currentRamp;
//
//
//};

#define _GLFW_REQUIRE_INIT_OR_RETURN(x)              \
    if (!_glfw.initialized)                          \
    {                                                \
        _glfwInputError(GLFW_NOT_INITIALIZED, NULL); \
        return x;                                    \
    }

#if defined(__GNUC__)
void _glfwInputError(int code, const char* format, ...)
__attribute__((format(printf, 2, 3)));
#else
void _glfwInputError(int code, const char* format, ...);
#endif