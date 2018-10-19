FROM php:7.2-apache
COPY . /var/www/html
EXPOSE 80
WORKDIR /
RUN mkdir sandboxed_bin;cp /bin/cat sandboxed_bin