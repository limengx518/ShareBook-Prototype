cmake_minimum_required( VERSION 3.23 )

project( ShareBook 
         VERSION 0.1.0
         DESCRIPTION "Description of project"
         HOMEPAGE_URL "http://www.abc.com"
         LANGUAGES CXX )
         
#execute_process(COMMAND g++ -std=c++20 -xc++-system-header -fmodules-ts
#         iostream
#         string
#)
         
add_executable( ShareBook )

target_sources( ShareBook PRIVATE
        comment.cpp
        commentbroker.cpp
        commentinterface.cpp
        commentproxy.cpp
        jotting.cpp
        jottingbroker.cpp
        jottinginterface.cpp
        jottingnotification.cpp
        jottingproxy.cpp
        jottingsocialcontrol.cpp
        main.cpp
        material.cpp
        materialbroker.cpp
        materialinterface.cpp
        materialproxy.cpp
        messagesequence.cpp
        mytimer.cpp
        netizen.cpp
        netizenbroker.cpp
        netizeninterface.cpp
        netizenproxy.cpp
        relationalbroker.cpp
        snowflakeidworker.cpp
        )
                
target_compile_features( ShareBook PRIVATE cxx_std_20 )

add_subdirectory(json)
#链接库
target_link_libraries(ShareBook
    PRIVATE
    mariadbcpp
    pthread
    boost_system
    pthread
    boost_timer
    nlohmann_json
)
