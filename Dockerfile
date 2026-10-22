FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake g++ make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY CMakeLists.txt README.md ./
COPY include include
COPY src src

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMATRIX_BUILD_TESTS=OFF && \
    cmake --build build --parallel 2

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends libstdc++6 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/matrix_calculator .

CMD ["./matrix_calculator"]
