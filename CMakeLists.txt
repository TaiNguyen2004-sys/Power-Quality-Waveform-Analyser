cmake_minimum_required(VERSION 4.2)
project(Power_Quality_waveform_analyser C)

set(CMAKE_C_STANDARD 99)

add_executable(Power_Quality_waveform_analyser
        main.c
        waveform.c
        waveform.h
        io.c
        io.h

)
add_executable(RunUnitTests
        testmain.c
        waveform.c
        io.c
        io.h
        waveform.h
)