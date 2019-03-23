FROM ubuntu:18.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libdbus-1-3 \
    xvfb \
    libfontconfig \
    python3 \
    ca-certificates \
    wget \
    cmake \
    libgl1-mesa-dev \
    libglib2.0-0 \
    git

ARG workspace=/root/workspace
ARG qtdestdir=/opt/Qt

RUN mkdir -p $workspace && cd $workspace

RUN wget https://github.com/hasboeuf/cuteci/raw/1.0.0/deploy_qt && \
    wget https://github.com/hasboeuf/cuteci/raw/1.0.0/install-qt.qs && \
    chmod +x deploy_qt && \
    ./deploy_qt \
        --rm \
        --installer http://download.qt.io/official_releases/qt/5.12/5.12.2/qt-opensource-linux-x64-5.12.2.run \
        install \
        --destdir $qtdestdir \
        --packages qt.qt5.5122.qtnetworkauth,qt.qt5.5122.qtwebengine,qt.qt5.5122.gcc_64 && \
    rm --force deploy_qt install-qt.qs

WORKDIR $workspace

ENTRYPOINT ["/bin/bash"]
