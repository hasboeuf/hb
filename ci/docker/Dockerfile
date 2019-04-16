FROM ubuntu:18.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libdbus-1-3 \
    xvfb \
    libfontconfig \
    python3 \
    python3-pip \
    cmake \
    libgl1-mesa-dev \
    libglib2.0-0 \
    git

ARG workspace=/root/workspace
ARG qtdestdir=/opt/Qt

RUN mkdir -p $workspace && cd $workspace

RUN pip3 install cuteci && \
    cuteci \
        --rm \
        --installer http://download.qt.io/official_releases/qt/5.12/5.12.2/qt-opensource-linux-x64-5.12.2.run \
        install \
        --destdir $qtdestdir \
        --packages qt.qt5.5122.qtnetworkauth,qt.qt5.5122.qtwebengine,qt.qt5.5122.gcc_64

WORKDIR $workspace

ENTRYPOINT ["/bin/bash"]
