#include <vector>
#include <math.h>
#include <iostream>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"
#include "implot_internal.h"

#include <GLFW/glfw3.h>

#include "model.cpp"

//======== polar graph settings =======
#define N_CIRCLES 7
#define RESOLUTION_CIRCLE 1000
#define RESOLUTION_MODEL 1000
#define STEP_CIRCLES 1
#define CUR_STP 1
double current_step;
double x_for_circle[RESOLUTION_CIRCLE];
double y_for_circle[RESOLUTION_CIRCLE]; 
double x_for_model[RESOLUTION_MODEL];
double y_for_model[RESOLUTION_MODEL];
//=====================================




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
    ImPlot::CreateContext();
    
    
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


    int x; 
    int y;
    ImVec2 size;
    ImVec2 pos;

    float L = 1;
    float m = 1;
    float n = 1;
    Model model = Model(RESOLUTION_MODEL);


    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
        glfwGetWindowSize(window,&x,&y);

        


        //================  menu ==========================


        pos = ImVec2(0,0);
        size = ImVec2(x/4,y/2);
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin("Меню теста", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
        ImGui::SliderFloat("L", &L, 1.0f, 10.0f, "%.3f");
        ImGui::SliderFloat("m", &m, 1.0f, 10.0f, "%.3f");
        ImGui::SliderFloat("n", &n, 1.0f, 10.0f, "%.3f");
        ImGui::End();
        //=================================================



        //================= visual #1 ========================        
        pos = ImVec2(0,y/2);
        size = ImVec2(x/4,y/2);
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin("##first", nullptr,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
        if(ImPlot::BeginPlot("##firstp", size, ImPlotFlags_NoFrame | ImPlotFlags_Equal)){
            
            float max_radius = N_CIRCLES * STEP_CIRCLES;
            float margin = max_radius * 0.1f;
            ImPlot::SetupAxisLimits(ImAxis_X1, -max_radius - margin, max_radius + margin);
            ImPlot::SetupAxisLimits(ImAxis_Y1, -max_radius - margin, max_radius + margin);
            
            
            
            current_step = CUR_STP;
            for(int i = 0; i < N_CIRCLES; i++){
                for(int j = 0; j < RESOLUTION_CIRCLE; j++){
                        x_for_circle[j] = current_step * cosf((j / (float)(RESOLUTION_CIRCLE - 1)) * (2.0f * M_PI));
                        y_for_circle[j] = current_step * sinf((j / (float)(RESOLUTION_CIRCLE - 1)) * (2.0f * M_PI));
                }
                ImPlot::PlotLine("##", x_for_circle, y_for_circle, RESOLUTION_CIRCLE);
                current_step += STEP_CIRCLES;
            }

            model.start_math(L,m,n);

            for(int i = 0; i < RESOLUTION_MODEL; i ++){
                
                x_for_model[i] = model.r[i] * cosf(model.f[i]);
                y_for_model[i] = model.r[i] * sinf(model.f[i]);
                if(i < 6){
                    std::cout<<"i = "<< i << "   r = " <<  model.r[i] << "   f = " << model.f[i] << std::endl;
                    std::cout<<"i = "<< i << "   x = " <<  x_for_model[i] << "   y = " << y_for_model[i] << std::endl;
                }

                
            }
            ImPlot::PlotLine("graph", x_for_model, y_for_model, RESOLUTION_MODEL );
            ImPlot::EndPlot();            
        }
        ImGui::End();
        //=================================================



        //================= visual #2 ========================
        pos = ImVec2(x/4,0);
        size = ImVec2(x*3/4,y);
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin("##second", nullptr,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
        ImPlot::BeginPlot("##secondp", size, ImPlotFlags_NoFrame );





        ImPlot::PlotLine("graph", x_for_model, y_for_model, RESOLUTION_MODEL );
        
        
        
        ImPlot::EndPlot();
        ImGui::End();
        //=================================================

        ImGui::Render();
        

        

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    
    
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    

    glfwDestroyWindow(window);
    glfwTerminate();
}