FROM php:7.2.6-apache
# Compile and install fresh ffmpeg from sources:
# See: https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
RUN apt-get update && apt-get install -y \
    ffmpeg

RUN apt-get install -y \
    libimage-exiftool-perl
