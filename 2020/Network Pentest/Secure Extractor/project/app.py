#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import zipfile
from flask import Flask, request, redirect, url_for, flash, render_template, send_file, abort
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = os.path.dirname(os.path.realpath(__file__)) + "/Uploads/"
ALLOWED_EXTENSIONS = set(['zip', 'tar', 'rar'])

app = Flask(__name__)
app.config['MAX_CONTENT_LENGTH'] = 30 * 1024

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def retext(filename):
    extension = filename.split(".",1)[1]
    return extension

def extract(filename, ext):
    if(ext == "zip"):
        os.system("unzip {}".format(filename))
    elif(ext == "tar"):
        os.system("tar xvf {}".format(filename))
    elif(ext == "rar"):
        os.system("unrar e {}".format(filename))


@app.route('/', methods=['GET', 'POST'], defaults={'req_path': ''})
@app.route('/<path:req_path>', methods=['GET', 'POST'])
def upload_file(req_path):
    if request.method == 'POST':
        print(request.files)
        if 'fileup' not in request.files:
            flash('No file part')
            return redirect(request.url)

        file = request.files['fileup']
        print(file)
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)

        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            os.chdir(UPLOAD_FOLDER)
            try:
                os.mkdir(filename.split(".",1)[1])
            except FileExistsError:
                print("File Exists")
                pass
            os.chdir(filename.split(".",1)[1])
            try:
                os.mkdir(filename.split(".",1)[0])
                os.chdir(filename.split(".",1)[0])
            except FileExistsError:
                abort(404, "File named {} Exists".format(filename))
            print("*****************")
            print(os.getcwd())
            print("*****************")
            file.save(filename)
            extract(filename, retext(filename))
            try:
                os.remove(filename)
            except FileNotFoundError:
                pass

            return redirect(url_for('upload_file', filename=filename))
    BASE_DIR = '/home/joyhopkins/project/Uploads'
    abs_path = os.path.join(BASE_DIR, req_path)
    if not os.path.exists(abs_path):
        return abort(404)
    if os.path.isfile(abs_path):
        return send_file(abs_path)
    files = os.listdir(abs_path)
    return render_template('index.html', files=files)


if __name__ == "__main__":
    #app.secret_key = 'someaprghaerg'
    app.run(host='0.0.0.0',port=5000, debug=True)
