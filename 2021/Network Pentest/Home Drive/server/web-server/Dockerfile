FROM python

RUN apt update; apt -y --autoremove full-upgrade
ARG DEBIAN_FRONTEND=noninteractive
RUN apt install gcc dnsutils -y

COPY . /app
WORKDIR /app

RUN pip install -r requirements.txt

COPY algorithms.py /usr/local/lib/python3.9/site-packages/jwt/algorithms.py


EXPOSE 5000
ENV DB_PATH /app/todo.db
ENV PRIVATE_KEY /app/mykey.pem
ENV PUBLIC_KEY /app/mykey.pub
RUN ["python", "-c", "from app import db; db.create_all();exit()"]
CMD ["python", "app.py" ]