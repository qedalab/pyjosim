FROM centos:centos7

# Update and set repositories
RUN yum -y update; yum clean all
RUN yum -y install epel-release centos-release-scl; yum clean all

# Basic dev tools
RUN yum -y install devtoolset-8 git doxygen wget lcov python34 python34-pip sudo; yum clean all
RUN python3.4 -m pip install conan sphinx cpp-coveralls cmake

# Install newer cmake seperate from system
RUN mkdir /cmake/
RUN wget -q --no-check-certificate https://cmake.org/files/v3.16/cmake-3.16.1-Linux-x86_64.tar.gz \
    && tar -xzf cmake-3.16.1-Linux-x86_64.tar.gz \
       --exclude=bin/cmake-gui \
       --exclude=doc/cmake \
       --exclude=share/cmake-3.12/Help \
    && cp -fR cmake-3.16.1-Linux-x86_64/* /cmake/ \
    && rm -rf cmake-3.16.1-Linux-x86_64 \
    && rm cmake-3.16.1-Linux-x86_64.tar.gz

# Install newer python version
RUN yum -y install rh-python36; yum clean all

# Use newer cmake
ENV PATH="/cmake/bin:${PATH}"

COPY . /josim-tools-source/

RUN scl enable devtoolset-8 rh-python36 "cd josim-tools-source &&  python3.6 setup.py install"
