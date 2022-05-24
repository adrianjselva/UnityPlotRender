cmake_minimum_required(VERSION 3.22)
project(UnityPlotRender)

set(CMAKE_CXX_STANDARD 17)

add_library(UnityPlotRender SHARED
        src/UnityPlotRenderPlugin.cpp
        include/PlatformBase.h
        include/Unity/IUnityGraphics.h
        include/Unity/IUnityInterface.h include/RenderAPI.h src/RenderAPI_OpenGLCoreES.cpp src/RenderAPI.cpp src/dataset/Dataset.cpp include/dataset/Dataset.h src/dataset/Summary.cpp include/dataset/Summary.h src/dataset/NormalizedDataset.cpp include/dataset/NormalizedDataset.h src/plot/PlotManager.cpp include/plot/PlotManager.h src/plot/Plot.cpp include/plot/Plot.h)
target_include_directories(UnityPlotRender PRIVATE include)
