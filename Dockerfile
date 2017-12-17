FROM ubuntu:xenial

COPY installer.sh /

ENV DEBIAN_FRONTEND non-interactive
# We don't want any interactive prompts
RUN apt-get update
RUN apt-get install -qq doxygen
RUN apt-get install -qq graphviz
RUN apt-get install -qq patch
RUN apt-get install -qq wget
RUN apt-get install -qq git
RUN apt-get install -qq cmake
RUN apt-get install -qq build-essential
RUN apt-get install -qq pkg-config
RUN ./installer.sh

# Set WORKDIR
WORKDIR /TerminalFighter/
