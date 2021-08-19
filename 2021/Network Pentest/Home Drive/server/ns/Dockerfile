FROM sameersbn/bind:9.16.1-20200524

COPY ./requirements.txt ./requirements.txt

RUN apt-get update && \
    apt-get install -y python3 python3-pip git
    # rm -rf /var/lib/apt/lists/*

RUN pip3 install -r requirements.txt

COPY zonerender.py /usr/bin/

EXPOSE 53/udp 53/tcp
ENV WEBMIN_ENABLED=false

RUN mkdir /tmp/ns
RUN chown ${BIND_USER} /tmp/ns
RUN chown -R bind:bind /tmp/ns
WORKDIR /tmp/ns
COPY zone.j2 named.conf.j2 ./

ENTRYPOINT ["python3", "/usr/bin/zonerender.py", "/sbin/entrypoint.sh"]