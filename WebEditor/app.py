import os
import shutil
import uuid
from flask import Flask, request

app = Flask(__name__,
            static_url_path="",
            static_folder="statics",
            template_folder="templates")
temp_folder = "temp"
if not os.path.exists(temp_folder):
    os.mkdir(temp_folder)

@app.route("/")
def home():
    return app.send_static_file("index.html")

@app.route("/api/preview", methods=["POST"])
def preview():
    files = request.get_json()
    folder_name = str(uuid.uuid4())
    os.mkdir(temp_folder + "/" + folder_name)
    for file in files:
        f = open(temp_folder + "/" + folder_name + "/" + file, "w")
        f.write(files[file])
        f.close()

    # Save the files to the folder

    shutil.rmtree(temp_folder + "/" + folder_name)
    return "OK"

@app.route("/api/render", methods=["POST"])
def render():
    files = request.get_json()
    folder_name = str(uuid.uuid4())
    os.mkdir(temp_folder + "/" + folder_name)
    for file in files:
        f = open(temp_folder + "/" + folder_name + "/" + file, "w")
        f.write(files[file])
        f.close()
    
    shutil.rmtree(temp_folder + "/" + folder_name)
    return "OK"