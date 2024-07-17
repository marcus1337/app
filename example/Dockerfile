FROM debian:latest

WORKDIR /usr/src/app
COPY . .
RUN rm -rf /usr/src/app/build
RUN mkdir -p /usr/src/app/build
WORKDIR /usr/src/app/build

RUN apt-get update && \
    apt-get install -y \
        cmake \
        g++ \
        git \
        libsdl2-dev \
        libsdl2-image-dev \
        libsdl2-ttf-dev \
        libsdl2-mixer-dev \
        xz-utils \
        python3

RUN git clone https://github.com/emscripten-core/emsdk.git && \
    cd emsdk && \
    ./emsdk install latest && \
    ./emsdk activate latest
    ENV EMSDK="/usr/src/app/build/emsdk"
    ENV EM_CONFIG="/usr/src/app/build/emsdk/.emscripten"
    ENV PATH="/usr/src/app/build/emsdk:/usr/src/app/build/emsdk/upstream/emscripten:${PATH}"

RUN emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
RUN emmake make

RUN mv ./* /usr/src/app/html
WORKDIR /usr/src/app/html

EXPOSE 8000
CMD ["python3", "-m", "http.server", "8000"]

