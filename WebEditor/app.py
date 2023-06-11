import os
import shutil
import uuid
import subprocess
import base64

from flask import Flask, request, Response, send_file, jsonify

app = Flask(__name__,
            static_url_path="",
            static_folder="statics",
            template_folder="templates")
temp_folder = "temp"
static_temp_folder = "statics/temp"
app_exec_path = "../Release/GKOM_OpenGL_2.exe"
full_path = os.path.abspath(app_exec_path)

print("App executable path: " + full_path)

if not os.path.exists(temp_folder):
    os.mkdir(temp_folder)
if not os.path.exists(static_temp_folder):
    os.mkdir(static_temp_folder)

@app.route("/")
def home():
    return app.send_static_file("index.html")

def get_output(params):
    output = subprocess.run([full_path] + params.split(" "), capture_output=True, text=True).stdout
    print(output)
    sp = output.split("\n")
    for s in sp:
        if s.startswith("OUTPUT"):
            return s[7:]
    return None

@app.route("/api/frame/<frame>", methods=["POST"])
def frame(frame):
    files = request.get_json()
    folder_name = str(uuid.uuid4())
    os.mkdir(temp_folder + "/" + folder_name)
    for file in files:
        f = open(temp_folder + "/" + folder_name + "/" + file, "w")
        f.write(files[file])
        f.close()

    # Save the files to the folder
    full_path = os.path.abspath(temp_folder + "/" + folder_name)
    print("Files saved to " + full_path)
    output = get_output(full_path + " frame " + frame)
    if output is None:
        return Response("ERROR", status=500)
    
    encoded_string = None
    with open(output, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read())
    
    shutil.rmtree(temp_folder + "/" + folder_name)
    return encoded_string

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
    full_path = os.path.abspath(temp_folder + "/" + folder_name)
    print("Files saved to " + full_path)

    output = get_output(full_path + " preview")
    if output is None:
        return Response("ERROR", status=500)
    shutil.copy(output, 'statics/temp/'+folder_name+'.mp4')

    shutil.rmtree(temp_folder + "/" + folder_name)
    return jsonify({
        "path": "temp/"+folder_name+".mp4"
    })

@app.route("/api/render", methods=["POST"])
def render():
    files = request.get_json()
    folder_name = str(uuid.uuid4())
    os.mkdir(temp_folder + "/" + folder_name)
    for file in files:
        f = open(temp_folder + "/" + folder_name + "/" + file, "w")
        f.write(files[file])
        f.close()
    
    # Save the files to the folder
    full_path = os.path.abspath(temp_folder + "/" + folder_name)
    print("Files saved to " + full_path)

    output = get_output(full_path + " render")
    if output is None:
        return Response("ERROR", status=500)
    shutil.copy(output, 'statics/temp/'+folder_name+'.mp4')

    shutil.rmtree(temp_folder + "/" + folder_name)
    return jsonify({
        "path": "temp/"+folder_name+".mp4"
    })
