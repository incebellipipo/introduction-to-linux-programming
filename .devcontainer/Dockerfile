FROM debian:trixie

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

ENV DEBIAN_FRONTEND=noninteractive

# Toolchain and tools used throughout the tutorial:
#   build-essential, cmake  -> building the examples
#   gdb, valgrind, strace   -> debugging (see 01-development-environment)
#   man-db, manpages-dev    -> `man 2 open`, `man 3 printf`, ...
#   netcat, iproute2        -> poking at the socket examples
#   procps, psmisc          -> ps, kill, pstree for process management
#   libsdl2-dev             -> 07-projects/02-musicmaker
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        cmake \
        file \
        gdb \
        git \
        iproute2 \
        less \
        libsdl2-dev \
        man-db \
        manpages \
        manpages-dev \
        netcat-openbsd \
        pkg-config \
        procps \
        psmisc \
        strace \
        sudo \
        valgrind \
        vim \
    && rm -rf /var/lib/apt/lists/*

# Non-root user so files created in the mounted workspace aren't owned by root
RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd --uid ${USER_UID} --gid ${USER_GID} --create-home --shell /bin/bash ${USERNAME} \
    && echo "${USERNAME} ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

USER ${USERNAME}
WORKDIR /workspaces
