FROM ubuntu:19.04

RUN sed -i -e 's|disco|eoan|g' /etc/apt/sources.list
RUN apt-get -y update &&\
    apt-get -y install xinetd


RUN useradd -m ctf

ADD start.sh /root
ADD chall /home/ctf
ADD flag /home/ctf
ADD run.sh /home/ctf
ADD chall.xinetd /etc/xinetd.d/chall

RUN chmod +x /root/start.sh && \
    chmod +x /home/ctf/chall && \
    chmod +x /home/ctf/run.sh && \
    chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf/   && \
    chown root:ctf /home/ctf/flag && \
    chmod 440 /home/ctf/flag  && \
    chmod 755 /tmp 

ENTRYPOINT  /root/start.sh

