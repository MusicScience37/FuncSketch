FROM registry.gitlab.com/musicscience37projects/docker/my-cpp-env-docker:clang22

RUN sudo apt-get update && \
    sudo apt-get install -y \
    libmtdev1 \
    && \
    sudo apt-get autoremove -y && \
    sudo apt-get autoclean && \
    sudo rm -r /var/lib/apt/lists/*
