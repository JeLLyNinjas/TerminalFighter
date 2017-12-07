FROM ubuntu:xenial

# Apt packages
# We don't want any interactive prompts
RUN apt-get update && DEBIAN_FRONTEND=non-interactive apt-get install -yq doxygen graphviz

# Set WORKDIR
WORKDIR /documentation
