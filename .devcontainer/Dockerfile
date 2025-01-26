FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && \
  apt-get install -y --no-install-recommends apt-utils && \
  apt-get install -y --no-install-recommends sudo ca-certificates pkg-config curl wget bzip2 xz-utils make libarchive-tools doxygen gnupg && \
  apt-get install -y --no-install-recommends git git-restore-mtime && \
  apt-get install -y --no-install-recommends rsync && \
  apt-get install -y --no-install-recommends cmake zip unzip ninja-build && \
  apt-get install -y --no-install-recommends python3 python-is-python3 python3-lz4 && \
  apt-get install -y --no-install-recommends locales && \
  apt-get install -y --no-install-recommends patch && \
  sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
  dpkg-reconfigure --frontend=noninteractive locales && \
  update-locale LANG=en_US.UTF-8 && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

RUN ln -s /proc/mounts /etc/mtab && \
  wget https://apt.devkitpro.org/install-devkitpro-pacman && \
  chmod +x ./install-devkitpro-pacman && \
  ./install-devkitpro-pacman && \
  rm ./install-devkitpro-pacman && \
  dkp-pacman -Syyu --noconfirm && \
  dkp-pacman -S --needed --noconfirm dkp-toolchain-vars dkp-meson-scripts && \
  yes | dkp-pacman -Scc


ENV LANG=en_US.UTF-8

ENV DEVKITPRO=/opt/devkitpro
ENV PATH=${DEVKITPRO}/tools/bin:$PATH
ENV PATH=${DEVKITPRO}/devkitPPC/bin/:$PATH

RUN dkp-pacman -Syyu --noconfirm gamecube-dev wii-dev wii-sdl2 && \
  dkp-pacman -S --needed --noconfirm ppc-portlibs gamecube-portlibs wii-portlibs && \
  dkp-pacman -S --needed --noconfirm devkitARM && \
  yes | dkp-pacman -Scc

ENV DEVKITPPC=${DEVKITPRO}/devkitPPC
ENV DEVKITARM=/opt/devkitpro/devkitARM

ENV PKG_CONFIG_PATH=${DEVKITPRO}/portlibs/wii/lib/pkgconfig:$PKG_CONFIG_PATH
ENV PKG_CONFIG_PATH=${DEVKITPRO}/portlibs/ppc/lib/pkgconfig:$PKG_CONFIG_PATH
