## Installation Steps
1. `sudo apt-get install freeglut3-dev`.
2. Compile OpenPose by your own [from https://github.com/CMU-Perceptual-Computing-Lab/openpose](from https://github.com/CMU-Perceptual-Computing-Lab/openpose).
3. Perform `make distribute` on OpenPose, and copy the `include` and `lib` files in [3rdparty/openpose/](3rdparty/openpose/).
4. Copy the `include` and `lib` folders from {OpenPose path}/3rdparty/caffe/distribute/ to [3rdparty/caffe/](3rdparty/caffe/).
5. Copy your Spinnaker desired version `include` and `lib` folders on [3rdparty/spinnaker/](3rdparty/spinnaker/). Note: I already placed the newest version available on May 10th (Ubuntu 16, 64 bits), so you might skip this step.
6. Open the [rtstereo.pro](rtstereo.pro) file with Qt to have the project ready-to-compile-and-go. If you prefer using your own Makefile file, you can take a look to this Qt file to know which files (basically [src](src) and [include](include)) and compiler flags I used.
	1. If using Qt, you will have to manually copy the {OpenPose path}/models folder inside the generated build folder.
7. You must copy the contents of [add_to_bin_file/](add_to_bin_file/) where the final binary file is generated.
