FROM wsmoses/598ape:latest
RUN apt update
RUN apt install -y htop
RUN rm -f /usr/bin/perf
RUN ln -s /usr/lib/linux-tools/6.8.0-52-generic/perf /usr/bin/perf