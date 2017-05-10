################################################################################
# rtstereo Makefile
################################################################################

################################################################################
# Key paths and settings
################################################################################
CC = g++
OUTPUTNAME = rtstereo.bin${D}
OUTDIR = ./bin

################################################################################
# Master inc/lib/obj/dep settings
################################################################################
OBJ = rtstereo.o

################################################################################
# Dependencies
################################################################################

# OpenPose
OPENPOSE_LIB = -L./3rdparty/openpose/lib -lopenpose${D}
INC = -I./3rdparty/openpose/include
LIB = -Wl,-Bdynamic ${OPENPOSE_LIB}
LIB += -Wl,-rpath=./3rdparty/openpose/lib
LIBRARIES += openpose

# Caffe
-Wl,-rpath=$(CAFFE_DIR)/lib
CAFFE_LIB = -L./3rdparty/caffe/lib -lcaffe${D}
INC += -I./3rdparty/caffe/include
LIB += -Wl,-Bdynamic ${CAFFE_LIB}
LIB += -Wl,-rpath=./3rdparty/caffe/lib
LIBRARIES += caffe

# OpenCV
LIB += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_contrib -lopencv_calib3d
# CVFLAGS = `pkg-config --cflags opencv`
# CC += g++ ${CFLAGS}

# Spinnaker
SPINNAKER_LIB = -L./3rdparty/spinnaker/lib -lSpinnaker${D}
INC += -I./3rdparty/spinnaker/include
LIB += -Wl,-Bdynamic ${SPINNAKER_LIB}
LIB += -Wl,-rpath=./3rdparty/spinnaker/lib
LIBRARIES += Spinnaker
# LIB += -Wl,-rpath-link=./3rdparty/spinnaker/lib

# OpenGL Rendering
LIBRARIES += GLU GL glut

# Other 3rdparty libraries
INC += -I/usr/local/cuda-8.0/include
# LIB += cudart cublas curand
# LIB += -Wl,-rpath=/usr/local/cuda-8.0/lib
# LIB += cblas atlas
# LIBRARIES = glog gflags boost_system boost_filesystem m hdf5_hl hdf5 caffe
LIBRARIES += glog gflags boost_system boost_filesystem m caffe

# Add all libraries
LIB += $(foreach library,$(LIBRARIES),-l$(library)) -L/usr/lib/ -L/usr/local/lib/ -L/usr/lib/x86_64-linux-gnu

# Disable warnings
CC += -w

# Flags
CFLAGS += -DUSE_CAFFE -pthread -fPIC -std=c++11
CFLAGS += -fopenmp -Wpedantic -Wall -Wextra
CFLAGS += -Wfatal-errors
CFLAGS += -DNDEBUG -O3


# Others
LIBRARIES += cudnn boost_thread
CFLAGS += -DUSE_CUDNN -march=native

################################################################################
# Rules/recipes
################################################################################
# Final binary
${OUTPUTNAME}: ${OBJ}
	${CC} -o ${OUTPUTNAME} ${OBJ} ${LIB} ${CFLAGS}
	mv ${OUTPUTNAME} ${OUTDIR}

# Intermediate objects
%.o: %.cpp
	${CC} ${CFLAGS} ${INC} -Wall -c -D LINUX $*.cpp

# Clean up intermediate objects
clean_obj:
	rm -f ${OBJ}	@echo "all cleaned up!"

# Clean up everything.
clean:
	rm -f ${OUTDIR}/${OUTPUTNAME} ${OBJ}	@echo "all cleaned up!"
