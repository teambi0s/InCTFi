FROM ubuntu:20.04

ENV TZ=Asia/Kolkata
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -y update && \
    apt-get -y install tzdata && \
    apt-get -y install xinetd && \
    apt-get -y install qemu-system


RUN useradd -m ctf

ADD start.sh /root
ADD chall /home/ctf/chall
ADD run.sh /home/ctf
ADD chall.xinetd /etc/xinetd.d/chall
ADD bzImage /home/ctf
ADD rootfs.cpio /home/ctf

RUN chmod +x /root/start.sh && \
    chmod +x /home/ctf/run.sh && \
    chmod +x /home/ctf/chall && \
    chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf/   && \
    chmod 755 /tmp 

ENTRYPOINT  /root/start.sh
