FROM fedora:latest AS build

# Install necessary packages
RUN dnf update -y && \
    dnf install -y \
    gcc \
    gcc-c++ \
    cmake \
    git \
    vtk-devel \
    java-latest-openjdk-devel \
    python3 && \
    dnf clean all

# Set the working directory
WORKDIR /solar-system-stimulation

# Copy the necessary files
COPY data/ ./data/
COPY src/ ./src/
COPY test/ ./test/
COPY CMakeLists.txt .

RUN sed -i '/set(VTK_DIR/c\set(VTK_DIR /usr/lib64/cmake/vtk)' CMakeLists.txt

# Set the build directory
WORKDIR /solar-system-stimulation/build

# Run cmake and build the project
RUN cmake -DCMAKE_BUILD_TYPE=Release  \
    -DVTK_MODULE_ENABLE_VTK_GuiSupportQt=DONT_WANT \
    -DVTK_MODULE_ENABLE_VTK_ViewsQt=DONT_WANT \
    .. && \
    cmake --build .

# Run tests
RUN ./solar_system_stimulation_test

# Final stage
FROM fedora:latest

# Install necessary runtime libraries
RUN dnf update -y && \
    dnf install -y \
    libstdc++ \
    vtk && \
    dnf clean all

# Create a user and group
RUN groupadd -r sim && useradd -r -g sim sim
USER sim

# Copy the built application and data
COPY --chown=sim:sim --from=build /solar-system-stimulation/build /app
COPY --chown=sim:sim --from=build /solar-system-stimulation/data /data

# Set the entrypoint
#ENTRYPOINT [ "/app/solar_system_stimulation" ]