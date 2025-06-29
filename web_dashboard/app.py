# web_dashboard/app.py

from flask import Flask, render_template
import sqlite3

app = Flask(__name__)

@app.route('/')
def view_logs():
    conn = sqlite3.connect('../securebridge_logs.db')
    cursor = conn.cursor()
    cursor.execute("SELECT filename, operation, status, timestamp FROM logs ORDER BY id DESC")
    logs = cursor.fetchall()
    conn.close()
    return render_template('logs.html', logs=logs)

if __name__ == '__main__':
    app.run(debug=True)
