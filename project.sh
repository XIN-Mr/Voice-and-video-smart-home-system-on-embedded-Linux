#!/bin/bash
#arm-linux-gcc  编译器
#./src/*.c      当前src文件夹里的所有.c的源文件
#-o             输出
#./bin/project  生成的可执行文件
#-I ./inc/      指定头文件的路径
arm-linux-gcc ./src/*.c -o ./bin/project  -I  ./inc/  -I ./inc/camera_h/ -L  ./lib/camera_lib/  -ljpeg  -lapi_v4l2_arm1
