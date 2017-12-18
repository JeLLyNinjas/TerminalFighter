FROM ubuntu:xenial

COPY installer.sh /

ENV DEBIAN_FRONTEND non-interactive

RUN apt-get -qq update && \
	apt-get -qq install \
		doxygen \
		graphviz \
		patch \
		wget \
		git \
		cmake \
		build-essential \
		pkg-config && \
	./installer.sh

WORKDIR /TerminalFighter/
