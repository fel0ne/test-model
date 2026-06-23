cmake_minimum_required(VERSION 3.10)
project(TEST_MODEL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory(third_party/glfw)


include_directories(third_party/imgui)
include_directories(third_party/imgui/backends)
include_directories(third_party/implot)
include_directories(third_party/glfw/include) 


add_executable(main 
    src/main.cpp
    

    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
    

    third_party/implot/implot.cpp
    third_party/implot/implot_items.cpp
    third_party/implot/implot_demo.cpp
)


find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE glfw OpenGL::GL ${CMAKE_DL_LIBS})