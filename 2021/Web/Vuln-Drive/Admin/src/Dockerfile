FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt install -qq -y mysql-server python3 python3-dev python3-pip apache2 \
    build-essential libssl-dev libffi-dev python3-setuptools python3-venv \
    libapache2-mod-php php-mysqli

COPY ssrf/requirements.txt /app/

RUN python3 -m venv /app/env
RUN /app/env/bin/pip3 install -r /app/requirements.txt

RUN echo "inctf{y0u_pr0v3d_th4t_1t_i5_n0t_53cur3_7765626861636b6572}" > /flag

COPY ./dump.sql .
COPY sqli /var/www/html
COPY ssrf /app
COPY ./85e370958684fc7627ec882d575465f9.sh .

EXPOSE 5000

CMD ./85e370958684fc7627ec882d575465f9.sh

