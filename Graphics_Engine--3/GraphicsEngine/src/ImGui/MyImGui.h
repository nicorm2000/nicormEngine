#ifndef MYIMGUI_H
#define MYIMGUI_H
#include "ImGuiMaster/Imgui/imgui.h"
#include "ImGuiMaster/Source/imgui_impl_glfw.h"
#include "ImGuiMaster/Source/imgui_impl_opengl3.h"
#include "../Entity/Entity.h"
#include "Entity2/Entity2.h"
#include "Camera2/Camera2.h"
#include "Entity/Entity3D.h"
#include "Light/DirectionalLight.h"
#include <stdio.h>
#include "../Window/Window.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "GLFW/glfw3.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

class GraficosEngine_API MyImGui
{
public:
	MyImGui();
	void Init();
	void InitAfterWindow(Window* win);
	void Update();
	void Draw();
	~MyImGui();

	void Begin(std::string);

	void End();

	void Text(std::string a);

	void SliderFloat(std::string a, float* b, float min, float max);

	bool SliderFloat3(std::string a, vec3* b, float min, float max);

	void UpdateMainWindows();

	void UpdateWindowsEntity2();
	void UpdateWindowsLights();
	void UpdateWindowsDirectionLights();
	void UpdateWindowsModel();
	void UpdateWindowsCamera();
private:
	const char* glsl_version;
	Window* _window;
	bool ShowEntity2List;
	bool ShowModelList;
	bool ShowCamera2;
	bool ShowLights;
};

#endif