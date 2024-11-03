FROM ubuntu:latest

COPY . /app

WORKDIR /app

EXPOSE 4242/udp

RUN apt-get update

ENV VCPKG_FORCE_SYSTEM_BINARIES=1

RUN apt-get update && apt-get install -y \
    cmake \
    git \
    build-essential \
    libxinerama-dev \
    libxcursor-dev \
    xorg-dev \
    libglu1-mesa-dev \
    pkg-config \
    make \
    gcc \
    g++ \
    curl \
    zip \
    unzip\
    tar\
    ninja-build

RUN ./build.sh full_build

CMD ./r-type_server 4242
