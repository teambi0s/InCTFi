FROM python:3.6-stretch

ADD flask-server /code
WORKDIR /code
RUN pip3 install -r requirements.txt
CMD ["python3", "app.py"]