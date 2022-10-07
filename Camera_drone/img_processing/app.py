from flask import Flask

app = Flask(__name__)
data = lengthData = ""

@app.route("/")
def index(dados):
    print()

@app.route("/data")
def getData():
    data = input()
    return "çalskdf"

@app.route("/legnthData")
def getLengthData():
    lengthData = input()
    return

if __name__ == "__main__":
    app.run()