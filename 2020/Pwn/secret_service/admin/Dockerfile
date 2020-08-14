FROM ubuntu:20.04

RUN  apt-get update && \
     apt-get -y upgrade && \
     apt-get install -y libseccomp-dev && \
     apt-get install -y xinetd

RUN useradd -m ctf

WORKDIR /home/ctf

ADD chall /home/ctf
ADD flag /home/ctf
ADD start.sh /root
ADD run.sh /home/ctf
ADD chall.xinetd /etc/xinetd.d/chall
ADD libseccomp.so.2 /home/ctf

RUN chmod +x /root/start.sh && \
    chmod +x /home/ctf/chall && \
    chmod +x /home/ctf/run.sh && \
    chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf/   && \
    chown root:ctf /home/ctf/flag && \
    chmod 440 /home/ctf/flag  && \
    chmod +x libseccomp.so.2 && \
    chmod 755 /tmp

RUN cp libseccomp.so.2 /usr/lib/x86_64-linux-gnu/

ENTRYPOINT  ["bash", "/root/start.sh"]
