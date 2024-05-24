FROM alpine:latest AS build

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake \
    git

WORKDIR /solar-system-stimulation

COPY data/ ./data/
COPY src/ ./src/
COPY test/ ./test/
COPY CMakeLists.txt .

WORKDIR /solar-system-stimulation/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

RUN ./solar_system_stimulation_test

FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S sim && adduser -S sim -G sim
USER sim


COPY --chown=sim:sim --from=build \
    ./solar-system-stimulation/build ./app

COPY --chown=sim:sim --from=build \
    ./solar-system-stimulation/data ./data

ENTRYPOINT [ "/app/solar_system_stimulation" ]