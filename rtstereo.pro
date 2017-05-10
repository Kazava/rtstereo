TEMPLATE = app
CONFIG += console c++11 warn_on
CONFIG -= app_bundle
CONFIG -= qt

TARGET = rtstereo

QMAKE_RESOURCE_FLAGS += -compress 9
#QMAKE_RESOURCE_FLAGS += -no-compress

DEFINES += USE_CAFFE USE_CUDNN

INCLUDEPATH += \
    /usr/include \
    /usr/local/include \
    /usr/local/cuda-8.0/include \
    $$PWD/include \
    $$PWD/3rdparty/caffe/include \
    $$PWD/3rdparty/openpose/include \
    $$PWD/3rdparty/spinnaker/include

DEPENDPATH += \
    $$PWD/include \
    $$PWD/3rdparty/caffe/include \
    $$PWD/3rdparty/openpose/include \
    $$PWD/3rdparty/spinnaker/include

#win32 {
#    message("Operating system is Windows")
#    LIBS += \
#    # OpenCV 2.4.10
#    #win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_core2410 -lopencv_imgproc2410 -lopencv_highgui2410 -lopencv_objdetect2410
#    #else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lopencv_core2410d -lopencv_imgproc2410d -lopencv_highgui2410d -lopencv_objdetect2410d
#    $$PWD/lib/opencv_core2410.lib \
#    $$PWD/lib/opencv_highgui2410.lib \
#    $$PWD/lib/opencv_imgproc2410.lib \
#    $$PWD/lib/opencv_objdetect2410.lib
#    # OpenCV 3.X
#    $$PWD/lib/opencv_world310.lib
#}
#macx{
#    message("Operating system is Mac")
#    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
#    LIBS += -L/usr/local/lib
#    LIBS += -lopencv_core
#    LIBS += -lopencv_highgui
#    LIBS += -lopencv_imgproc
#}
unix:!macx{
    message("Operating system is Linux")
    LIBS += -L/usr/lib/ -L/usr/local/lib/ -L/usr/lib/x86_64-linux-gnu
    # OpenPose
    LIBS += -Wl,-rpath=$$PWD/3rdparty/openpose/lib
    LIBS += -Wl,-Bdynamic -L$$PWD/3rdparty/openpose/lib/ -lopenpose
    # Caffe
    LIBS += -Wl,-rpath=$$PWD/3rdparty/caffe/lib
    LIBS += -Wl,-Bdynamic -L$$PWD/3rdparty/caffe/lib/ -lcaffe
    # Spinnaker
    LIBS += -Wl,-rpath=$$PWD/3rdparty/spinnaker/lib
    LIBS += -Wl,-Bdynamic -L$$PWD/3rdparty/spinnaker/lib/ -lSpinnaker
    # OpenCV
    LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_contrib -lopencv_calib3d
    # CUDA
    LIBS += -I/usr/local/cuda-8.0/include/
    LIBS += -L/usr/local/cuda-8.0/lib64 -lcudart -lcublas -lcurand
    # OpenGL
    LIBS += -lGLU -lGL -lglut
    # Other 3rdparty
    LIBS += -lcudnn -lglog -lgflags -lboost_system -lboost_filesystem -lm -lboost_thread
    LIBS += -pthread -fPIC -std=c++11 -fopenmp
    # Optimization flags
    LIBS += -DNDEBUG -O3 -march=native
    # Debug flags
    LIBS += -Wpedantic -Wall -Wextra -Wfatal-errors
}

message($$PWD)
SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/pointGrey.cpp \
    $$PWD/src/reconstruction3D.cpp \
    $$PWD/src/renderer.cpp

HEADERS  += \
    $$PWD/include/datum3D.hpp \
    $$PWD/include/pointGrey.hpp \
    $$PWD/include/reconstruction3D.hpp \
    $$PWD/include/renderer.hpp
