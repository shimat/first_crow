FROM ubuntu:22.04

ENV TZ=Asia/Tokyo
ENV DEBIAN_FRONTEND=noninteractive

# https://drogon.docsforge.com/master/installation/#library-dependencies
RUN apt-get update && apt install -y \
  git \
  build-essential \
  cmake \
  libasio-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# experimental
#RUN apt-get update && apt install -y \
#  libopencv-dev \
#  && apt-get clean \
#  && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/CrowCpp/Crow.git \
  && mkdir Crow/build \
  && cd Crow/build \
  && cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF \
  && make -j$(nproc) \
  && make install \
  && make clean \
  && cd && rm -rf Crow

RUN git clone https://github.com/opencv/opencv.git -b 4.6.0 --single-branch --depth 1 \
  && mkdir opencv/build \
  && cd opencv/build \
  && cmake .. \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_LIST=core,improc,imgcodecs,features2d,photo \
    -DBUILD_JAVA=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DWITH_ADE=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_GSTREAMER=OFF \
    -DWITH_OPENEXR=OFF \
    -DWITH_PROTOBUF=OFF \
    -DWITH_QUIRC=OFF \
    -DWITH_VTK=OFF \
  && make -j$(nproc) \
  && make install \
  && make clean \
  && ldconfig \
  && cd && rm -rf opencv
