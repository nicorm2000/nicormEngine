#include "MyImGui.h"
#include <iostream>
MyImGui::MyImGui()
{
}

void MyImGui::Init()
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}

void MyImGui::InitAfterWindow(Window* win)
{
    glfwMakeContextCurrent(win->GetWindow());
    glfwSwapInterval(1); // Enable vsync
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win->GetWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    _window = win;
}

void MyImGui::Update()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    UpdateMainWindows();
    if (ShowEntity2List)
    {
        UpdateWindowsEntity2();
    }
    if (ShowModelList)
    {
        UpdateWindowsModel();
    }
    if (ShowLights)
    {
        UpdateWindowsLights();
    }
}

void MyImGui::Draw()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window->GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

MyImGui::~MyImGui()
{
}
ImVec4 clear_color;
void MyImGui::Begin(std::string a){ ImGui::Begin(a.c_str()); }
void MyImGui::End() { ImGui::End(); }
void MyImGui::Text(std::string a) { ImGui::Text(a.c_str()); }
void MyImGui::SliderFloat(std::string a, float * b, float min,float max) { ImGui::SliderFloat(a.c_str(), b, min, max); }
bool MyImGui::SliderFloat3(std::string a,vec3 * b, float min, float max) 
{
    return ImGui::SliderFloat3(a.c_str(), (float*)&b, min, max); 
}

void MyImGui::UpdateMainWindows()
{
    ImGui::Begin("Config");
    if (ImGui::Button("ENTITY2",ImVec2(ImGui::GetWindowWidth(),20)))
    {
        ShowEntity2List = !ShowEntity2List;
    }
    if (ImGui::Button("MODEL", ImVec2(ImGui::GetWindowWidth(), 20)))
    {
        ShowModelList = !ShowModelList;
    }
    if (ImGui::Button("LIGHTS", ImVec2(ImGui::GetWindowWidth(), 20)))
    {
        ShowLights = !ShowLights;
    }

    ImGui::Text("Inputs:");
    ImGui::Text("W: Forward, S: Back, A: Left, D: Right, Q: Up, E: Down");
    ImGui::Text("C: LockCursor, B: CameraMode, SPACE: CameraFollowCursor");

    ImGui::End();
}
using namespace MikkaiEngine;

void baseEntity2Edit(Entity2* it)
{
    ImGui::Text("-------------");
    bool enabled = (it)->getactive();
    if (ImGui::Checkbox(((it)->getName() + "enabled").c_str(), &enabled))
        (it)->setActive(enabled);
    if ((it)->getactive())
    {
        vec3 pos = (it)->getPos();
        vec3 rot = (it)->getRot();
        vec3 scale = (it)->getScale();
        vec3 color = (it)->getColor();
        //if ((it)->canDrawThisFrame())
        //    ImGui::Text("Se dibuja");
        //else
        //    ImGui::Text("No Se dibuja");
        if (ImGui::SliderFloat3(("pos "+(it)->getName()).c_str(), (float*)&pos, -15.0f, 15.0f))
            (it)->SetPos(pos);
        if (ImGui::SliderFloat3(("rot "+(it)->getName()).c_str(), (float*)&rot, -180.0f, 180.0f))
            (it)->SetRotations(rot);
        if (ImGui::SliderFloat3(("scl "+(it)->getName()).c_str(), (float*)&scale, -0.0f, 3.0f))
            (it)->SetScale(scale);
        if (ImGui::ColorEdit3(("clo " + (it)->getName()).c_str(), (float*)&color))
            (it)->SetColor(color);
    }
    if ((it)->getChildren().size() > 0)
    {
        ImGui::Text("HIJOS: ");
        for (int i = 0; i < (it)->getChildren().size(); i++)
            ImGui::Text((it)->getChildren()[i]->getName().c_str());
    }
    else
    {
        ImGui::Text("HIJOS: NULL");
    }
    if ((it)->getChildren().size()>0)
        for (int i = 0; i < (it)->getChildren().size(); i++)
            baseEntity2Edit((it)->getChildren()[i]);
    if ((it)->getParent()!=nullptr)
    {
        ImGui::Text(("PADRE: "+ (it)->getParent()->getName()).c_str());
    }
    else
    {
        ImGui::Text("PADRE: NULL");
    }
    if ((it)->getMeshes().size()>0)
    {
        int a = (it)->getMeshes().size();
        
        std::string val("MESHES:" + std::to_string(a));
        ImGui::Text(val.c_str());
    }
    ImGui::Text("-------------");
}
void baseLight2Edit(Light* it)
{
    bool enabled = (it)->getactive();
    if (ImGui::Checkbox(((it)->getName() + "enabled").c_str(), &enabled))
        (it)->setActive(enabled);
    if ((it)->getactive())
    {
        vec3 amb = (it)->GetAmbient();
        vec3 dif = (it)->GetDiffuse();
        vec3 spe = (it)->GetSpecular();
        vec3 col = (it)->getColor();
        if (ImGui::SliderFloat3(((it)->getName() + " amb").c_str(), (float*)&amb, 0.0f, 1.0f))
            (it)->SetAmbient(amb);
        if (ImGui::SliderFloat3(((it)->getName() + " dif").c_str(), (float*)&dif, 0.0f, 1.0f))
            (it)->SetDiffuse(dif);
        if (ImGui::SliderFloat3(((it)->getName() + " spe").c_str(), (float*)&spe, 0.0f, 1.0f))
            (it)->SetSpecular(spe);
        if (ImGui::ColorEdit3(((it)->getName() + " spe").c_str(), (float*)&col))
            (it)->SetColor(col);
    }
}
void DirLightEdit(DirectionLight* it)
{
    bool enabled = (it)->getactive();
    if (ImGui::Checkbox(((it)->getName() + "enabled").c_str(), &enabled))
        (it)->setActive(enabled);
    if ((it)->getactive())
    {
        vec3 dir = (it)->GetDirection();
        if (ImGui::SliderFloat3(((it)->getName() + " dir").c_str(), (float*)&dir, 0.0f, 1.0f))
            (it)->SetAmbient(dir);
        baseLight2Edit(it);
    }

}

void MyImGui::UpdateWindowsEntity2()
{
    ImGui::Begin("Entity2");
    if (Entity2::EntitysLists.size()>0)
    {
        for (std::list<Entity2*>::iterator it = Entity2::EntitysLists.begin(); it != Entity2::EntitysLists.end(); it++)
        {
            baseEntity2Edit(*it);
        }
    }
    ImGui::End();
}
void MyImGui::UpdateWindowsLights()
{
    ImGui::Begin("Lights");
    if (Light::LightsLists.size() > 0)
    {
        for (std::list<Light*>::iterator it = Light::LightsLists.begin(); it != Light::LightsLists.end(); it++)
        {
            baseLight2Edit(*it);
        }
    }
    ImGui::End();
}

void MyImGui::UpdateWindowsDirectionLights()
{
    ImGui::Begin("DirectionLights");
    if (DirectionLight::DirectionLightLists.size() > 0)
    {
        for (std::list<DirectionLight*>::iterator it = DirectionLight::DirectionLightLists.begin(); it != DirectionLight::DirectionLightLists.end(); it++)
        {
            DirLightEdit(*it);
        }
    }
    ImGui::End();
}

void MyImGui::UpdateWindowsModel()
{
    ImGui::Begin("MODEL");
    if (Entity3D::entitys3dList.size()>0)
    {
        for (std::list<Entity3D*>::iterator it = Entity3D::entitys3dList.begin(); it != Entity3D::entitys3dList.end(); it++)
        {
            baseEntity2Edit((*it)->model->GetBaseNode());
        }
    }
    ImGui::End();
}

