FROM ubuntu:18.04

RUN apt update && apt install -y gcc g++ cmake

WORKDIR /print

COPY . .

RUN mkdir build && \
    cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON && \
    cmake --build .

ENV LOG_PATH=/home/logs/log.txt

VOLUME /home/logs

WORKDIR /print/build

ENTRYPOINT ["./check"]

