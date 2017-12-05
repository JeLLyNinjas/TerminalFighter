FROM ubuntu:xenial as setup


# Apt packages
RUN apt-get update
RUN DEBIAN_FRONTEND=non-interactive apt-get install -yq doxygen graphviz

FROM setup

WORKDIR /documentation
ADD . /documentation
