from flask import Flask, render_template, jsonify, request
import subprocess, os, stat

# Ensure executable permissions
os.chmod('./code/aes.exe', os.stat('./code/aes.exe').st_mode | stat.S_IEXEC)

app = Flask(__name__)

@app.route('/', methods=['GET'])
def home():
    return render_template('index.html')

@app.route('/encrypt', methods=['POST'])
def encrypt():
    data = request.json
    key = data['key']
    plainText = data['text']

    # cpp file
    result = subprocess.run(['./code/aes.exe', key, plainText, "encrypt"], capture_output=True, text=True)

    # if result.returncode != 0:
    #     return jsonify({'error': 'C++ program failed', 'stderr': result.stderr}), 500

    return jsonify({'cipherText' : result.stdout.strip()})


@app.route('/decrypt', methods=['POST'])
def decrypt():
    data = request.json
    key = data['key']
    cipherText = data['text']

    #cpp file
    result = subprocess.run(['code/aes.exe', key, cipherText, "decrypt"], capture_output=True, text=True)

    return jsonify({'plainText':result.stdout.strip()})


if (__name__ == '__main__'):
    port = int(os.environ.get("PORT", 10000))  # Get Render's assigned port
    app.run(host="0.0.0.0", port=port, debug=False)  # Bind to 0.0.0.0