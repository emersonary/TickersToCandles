cmake_minimum_required(VERSION 3.27)

project(TickersToCandles)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory( Generic )
add_subdirectory( Base )

include_directories( TickersToCandles
                     Generic
                     Base )

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
)

target_link_libraries( TickersToCandles
                       Generic
                       Base  )

