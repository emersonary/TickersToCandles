cmake_minimum_required(VERSION 3.27)

project(TickersToCandles)

set(CMAKE_CXX_STANDARD 17)

add_executable( TickersToCandles
               main.cpp
        ucCtrlTickersToCandles.h
        ucCtrlTickersToCandles.cpp
        ucModelAsset.h
        ucModelAsset.cpp
        ucModelCandles.h
        ucModelCandles.cpp
        ucModelTicker.h
        ucModelTicker.cpp
        Generic/uAux.h
        Generic/uAux.cpp
        Base/ucModelBase.h
        Base/ucModelBase.cpp
        Base/ucModelCad.h
        Base/ucModelCad.cpp)

#[[
add_subdirectory(
        Base
        Generic
)

include_directories( TickersToCandles
        Base
        Generic
)

target_link_libraries(TickersToCandles
        Base
        Generic )
]]

