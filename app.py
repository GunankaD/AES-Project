from flask import Flask, render_template, jsonify, request
import subprocess


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

if (__name__ == '__main__'):
    app.run(debug=True)