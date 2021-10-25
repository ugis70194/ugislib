FROM quay.io/cybozu/ubuntu:18.04
WORKDIR /work/build
ARG UID=1000 
RUN useradd -m -u ${UID} docker && \
    apt-get update && \ 
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y wget unzip g++-9-multilib && \
    rm -rf /var/lib/apt-lists/* && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 30 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 30 && \
    wget https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.bz2 && \
    tar --bzip2 -xf ./boost_1_77_0.tar.bz2 && \
    cd ./boost_1_77_0 && \ 
    sh bootstrap.sh && \
    ./b2 install -j2 --prefix=/home/docker/local && \
    wget https://img.atcoder.jp/practice2/ac-library.zip && \
    unzip ac-library.zip && \
    mv ./atcoder /home/docker/local/include && \
    rm -rf  boost_1_77_0.tar.bz2 boost_1_77_0 \ 
            ac-library.zip document_en document_ja expander.py
USER docker
WORKDIR /home/docker/work
RUN echo "alias g++='g++ -std=gnu++17'" >> /home/docker/.bashrc
ENV CPLUS_INCLUDE_PATH="/home/docker/local/include:$CPLUS_INCLUDE_PATH" \
    LIBRARY_PATH="/home/docker/local/lib:$LIBRARY_PATH" \ 