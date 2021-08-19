FROM ubuntu:20.04

ENV TZ=Asia/Kolkata
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone


RUN apt-get -y update && \
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
