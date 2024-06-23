#ifndef INPUT2_H
#define INPUT2_H
#include "Exports/Exports.h"
#include "Window/Window.h"
#include "Camera2/Camera2.h"
#include <list>
namespace MikkaiEngine
{
    class GraficosEngine_API Input2 {
    public:
        static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        Input2(Window* w, Camera2* c);
        static void Init(Window* w, Camera2* c);
        ~Input2() {};
        static void mouse_callback(double xposIn, double yposIn);
        #include "KeyState.h"
        #include "KeyCode.h"
        KeyCode _keyCode;
        KeyState _keyState;

        static bool IsKeyDown(KeyCode key);
        static bool IsKeyPressed(KeyCode keyCode);
        static bool IsKeyUp(KeyCode keyCode);

        static void lock_cursor(bool value);


    private:
        static Window*  _window;
        static Camera2* _mainCam;
        static std::list<int> _currentKeysDown;
        static int GetKey(int key);
       
    };
}
#endif