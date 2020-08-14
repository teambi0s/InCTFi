FROM ubuntu:18.04

# Install dependencies
RUN apt-get -y update && apt-get install -y \
	xinetd \
	python \
	python-pip

# Add Python dependencies
COPY requirements.txt /tmp/
RUN pip install --requirement /tmp/requirements.txt

# Create ctf user to handle the challenge
ENV HOME /home/ctf

RUN groupadd -r ctf && useradd -r -g ctf ctf
RUN mkdir -p $HOME

# Handle xinetd
ADD run.sh $HOME
RUN chmod +x $HOME/run.sh && \
	chown -R root:ctf $HOME && \
	chmod -R 750 $HOME/*

ADD ecchallenge.xinetd /etc/xinetd.d/ecchallenge
RUN service xinetd restart

# Set Python stream unbuffered
ENV PYTHONUNBUFFERED TRUE
COPY flag.py ansi931.py  ecc.py  encrypt.py  pow.py  prng.py $HOME/ 
CMD ["/usr/sbin/xinetd", "-dontfork"]


