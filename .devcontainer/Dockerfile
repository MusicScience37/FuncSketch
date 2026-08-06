FROM registry.gitlab.com/musicscience37projects/docker/my-cpp-env-docker:clang22

RUN sudo apt-get update && \
    sudo apt-get install -y \
    # For running Kivy GUI in Docker container.
    libmtdev1 \
    # For running tests without GUI.
    xvfb \
    && \
    sudo apt-get autoremove -y && \
    sudo apt-get autoclean && \
    sudo rm -r /var/lib/apt/lists/*
