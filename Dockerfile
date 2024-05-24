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

FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs


COPY --chown=shs:shs --from=build \
    ./solar-system-stimulation/build ./app

COPY --chown=shs:shs --from=build \
    ./solar-system-stimulation/data ./data

ENTRYPOINT [ "/app/solar_system_stimulation" ]