from flask import Flask, render_template, request, redirect, url_for, jsonify
import os
import sqlite3
from pathlib import Path

DATABASE_PATH = os.environ.get("DATABASE_PATH", "/workspace/poll.db")
PORT = int(os.environ.get("PORT", 5000))
CANDIDATE_A_NAME = os.environ.get("CANDIDATE_A", "Alice")
CANDIDATE_B_NAME = os.environ.get("CANDIDATE_B", "Bob")
RESET_SECRET = os.environ.get("RESET_SECRET")

app = Flask(__name__)


def get_db_connection() -> sqlite3.Connection:
    connection = sqlite3.connect(DATABASE_PATH)
    connection.row_factory = sqlite3.Row
    return connection


def ensure_schema() -> None:
    Path(DATABASE_PATH).parent.mkdir(parents=True, exist_ok=True)
    connection = get_db_connection()
    try:
        connection.execute(
            """
            CREATE TABLE IF NOT EXISTS votes (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                candidate TEXT NOT NULL CHECK(candidate IN ('A', 'B')),
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
            """
        )
        connection.commit()
    finally:
        connection.close()


ensure_schema()


@app.get("/")
def index():
    return render_template(
        "index.html",
        candidate_a=CANDIDATE_A_NAME,
        candidate_b=CANDIDATE_B_NAME,
    )


@app.post("/vote")
def vote():
    candidate = request.form.get("candidate")
    if candidate not in ("A", "B"):
        return ("Invalid candidate", 400)

    connection = get_db_connection()
    try:
        connection.execute("INSERT INTO votes(candidate) VALUES (?)", (candidate,))
        connection.commit()
    finally:
        connection.close()

    if request.headers.get("Accept") == "application/json" or request.is_json:
        return jsonify({"success": True})

    return redirect(url_for("index"))


@app.get("/results")
def results():
    connection = get_db_connection()
    try:
        cursor = connection.execute(
            "SELECT candidate, COUNT(*) AS count FROM votes GROUP BY candidate"
        )
        rows = cursor.fetchall()
    finally:
        connection.close()

    counts = {"A": 0, "B": 0}
    for row in rows:
        counts[row["candidate"]] = row["count"]

    total_votes = counts["A"] + counts["B"]

    return jsonify(
        {
            "candidateA": {
                "key": "A",
                "name": CANDIDATE_A_NAME,
                "votes": counts["A"],
            },
            "candidateB": {
                "key": "B",
                "name": CANDIDATE_B_NAME,
                "votes": counts["B"],
            },
            "total": total_votes,
        }
    )


@app.post("/reset")
def reset():
    if RESET_SECRET and request.form.get("secret") != RESET_SECRET:
        return ("Unauthorized", 401)

    connection = get_db_connection()
    try:
        connection.execute("DELETE FROM votes")
        connection.commit()
    finally:
        connection.close()

    if request.headers.get("Accept") == "application/json":
        return jsonify({"success": True})

    return redirect(url_for("index"))


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=PORT, debug=True)