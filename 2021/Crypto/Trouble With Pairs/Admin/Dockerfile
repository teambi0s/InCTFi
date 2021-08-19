FROM ubuntu:20.04

RUN apt-get -y update && \
    apt-get -y upgrade

RUN apt update && apt install -y git \
    python3-pip


RUN git clone -n https://github.com/ethereum/py_ecc.git && \
    cd py_ecc && \
    git checkout -b poc 8ddea32b693f7c71fff3b68fca9fd8804ebf33cb && \
    pip install .


RUN useradd -m ctf
#RUN echo "ctf:ctf" | chpasswd

ADD ynetd /home/ctf
ADD BLS.py /home/ctf
ADD secret.py /home/ctf
ADD server.py /home/ctf
ADD run.sh /home/ctf


WORKDIR /home/ctf

RUN chown -R ctf:ctf /home/ctf


RUN chmod +x run.sh
RUN chmod +x ynetd

USER ctf
EXPOSE 1337

CMD ./ynetd -p 1337 ./run.sh
