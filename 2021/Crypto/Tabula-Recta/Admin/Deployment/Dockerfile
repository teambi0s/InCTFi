FROM ubuntu:20.04

RUN apt-get -y update && \
    apt-get -y upgrade 

RUN useradd -d /home/tabula/ -m -p tabula -s /bin/bash tabula

WORKDIR /home/tabula

COPY server.py .
COPY dict.py .
COPY run.sh .

RUN chmod +x /home/tabula/server.py && \
    chmod +x /home/tabula/run.sh && \
    chmod 440 /home/dict.py && \
    chown -R root:root /home/tabula

USER tabula
EXPOSE 1222

CMD ./ynetd -p 1222 ./run.sh
