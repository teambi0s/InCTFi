FROM ubuntu:20.04
RUN apt update
RUN apt install -yqq python3 python3-dev python3-pip mysql-server wget
RUN pip3 install pyCryptodome mysql-connector-python dataclasses
RUN apt-get autoremove
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
COPY server /opt/blackStab/
RUN pip3 install /opt/blackStab/package/

RUN touch /var/log/blackStab.log
RUN echo "inctf{redacted}" > /redacted
COPY run.sh /
RUN chmod +x /run.sh
EXPOSE 9999
CMD "/run.sh"
