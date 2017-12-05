FROM ubuntu:xenial as setup

# Apt packages
RUN apt-get update
# We don't want any interactive prompts
RUN DEBIAN_FRONTEND=non-interactive apt-get install -yq doxygen graphviz

# Multistage docker
FROM setup

# Set WORKDIR
WORKDIR /documentation

# Copy all files from this project root host computer to /documentation in the docker container
ADD . /documentation
