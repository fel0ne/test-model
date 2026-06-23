#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



#include "implot.h"
#include "implot_internal.h"



#include <GLFW/glfw3.h>

int main(){
    if (!glfwInit()){ 
        return -1;
    }


    GLFWwindow* window = glfwCreateWindow(1000,500,"test_model", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    ImGui::CreateContext();

    
    
//========== begin font =======    
    ImGuiIO io =ImGui::GetIO(); 

    const ImWchar* cyrillic_ranges = io.Fonts->GetGlyphRangesCyrillic();

    ImFont* font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16.0f, nullptr, cyrillic_ranges);

    if (font == nullptr) {
        io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 16.0f, nullptr, cyrillic_ranges);
    }
//=========== end font  =======



    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 130");




    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int x; 
        int y;

        glfwGetWindowSize(window,&x,&y);

        ImVec2 size(x/2,y);
        ImVec2 pos(0,0);
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin("Меню теста", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
        ImGui::Text("тут будет меню");
        ImGui::End();


        ImGui::Render();
        

        

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}