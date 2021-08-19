FROM python:3.6-stretch

ADD flask-server /code
WORKDIR /code
RUN pip install -r requirements.txt
CMD ["python", "app.py"]