FROM ubuntu:16.04
RUN apt-get update
RUN apt-get install -y \
    socat python3

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf/chall
USER ctf

COPY chall .

ENTRYPOINT socat tcp-l:7478,fork,reuseaddr exec:'python3 run.py'
