FROM ubuntu:disco as build
RUN apt update

LABEL description="Build container - boost-python-test"

RUN apt install -y wget
RUN apt install -y cmake

# install g++
RUN apt install -y g++

# install python
RUN apt install -y python3-dev
RUN apt install -y python3

# install boost
WORKDIR /tmp
RUN wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.bz2

RUN tar --bzip2 -xf /tmp/boost_1_71_0.tar.bz2
WORKDIR /tmp/boost_1_71_0

RUN ./bootstrap.sh --with-libraries=python --with-python-version=3
# make python3 default
RUN ln -s /usr/bin/python3 /usr/bin/python 
RUN ./b2 install

# create build directory
RUN mkdir build

# copy source
WORKDIR /code
COPY ./code .

# build 
WORKDIR /code/build
RUN cmake ..
RUN make

FROM ubuntu:disco as runtime
RUN apt update
 
LABEL description="Run container - boost-python-test"
 
# install python
RUN apt install -y python3
RUN apt install -y python3-dev

RUN mkdir /boost-python-test
COPY --from=build /code/build/python_shared_mem.so /boost-python-test/
COPY --from=build /code/get_shared_mem_number.py /boost-python-test/

# Copy boost libraries to /usr/local/lib so we don't have to modify LD_LIBRARY_PATH
COPY --from=build /usr/local/lib/libboost_python37.so* /usr/local/lib/
 
WORKDIR /boost-python-test