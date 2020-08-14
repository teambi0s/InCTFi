FROM ubuntu:16.04

RUN apt-get -y update && \
    apt-get -y upgrade && \
	apt-get -y install xinetd



RUN useradd -m ctf
RUN apt-get -y install openssl

ADD start.sh /root
ADD chall /home/ctf
ADD flag.txt /home/ctf
ADD key.txt /home/ctf
ADD run.sh /home/ctf
ADD chall.xinetd /etc/xinetd.d/chall

RUN chmod +x /root/start.sh && \
	chmod +x /home/ctf/chall && \
	chmod +x /home/ctf/run.sh && \
	chown -R root:ctf /home/ctf/ && \
	chmod -R 750 /home/ctf/ && \
	chown root:ctf /home/ctf/flag.txt && \
	chown root:ctf /home/ctf/key.txt && \
	chmod 440 /home/ctf/flag.txt && \
	chmod 440 /home/ctf/key.txt && \
	chmod 755 /tmp

ENTRYPOINT /root/start.sh
