from flask import Flask, render_template, request, jsonify
import json
from datetime import datetime

timestamp = datetime.now()

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/form', methods=['POST', 'GET'])
def data():
    light01 = request.form.get('light01')
    light02 = request.form.get('light02')
    light03 = request.form.get('light03')
    digital01 = request.form.get('digital01')
    digital02 = request.form.get('digital02')
    digital03 = request.form.get('digital03')
    analog01 = request.form.get('analog01')

    result = {
    "lights": {
        "light01":bool(light01),
        "light02":bool(light02),
        "light03":bool(light03)
    },

    "digitaldevices": {
        "digital01":bool(digital01),
        "digital02":bool(digital02),
        "digital03":bool(digital03)
    },
        "analog" : analog01
    }

    with open("output.json", "w") as outfile:
        json.dump(result, outfile)
    return jsonify(result)

@app.route('/api')
def api():
    with open("output.json") as json_file:
        content = json.load(json_file)
    return jsonify(content)


if __name__ == "__main__":
    app.run(debug=True)
