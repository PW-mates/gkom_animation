from flask import Flask

app = Flask(__name__,
            static_url_path="",
            static_folder="statics",
            template_folder="templates")

@app.route("/")
def home():
    return app.send_static_file("index.html")
