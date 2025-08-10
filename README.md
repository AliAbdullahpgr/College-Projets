# Two-Candidate Polling App

A tiny Flask app where users can vote between two candidates and see live-updating results.

## Run locally

```bash
python3 -m pip install --user -r requirements.txt
python3 app.py
```

The server listens on `http://0.0.0.0:5000`.

## Configuration (optional)

- `CANDIDATE_A`: name for candidate A (default: `Alice`)
- `CANDIDATE_B`: name for candidate B (default: `Bob`)
- `RESET_SECRET`: if set, the reset endpoint requires matching secret
- `PORT`: server port (default: `5000`)
- `DATABASE_PATH`: path to SQLite DB file (default: `/workspace/poll.db`)

Example:

```bash
CANDIDATE_A="Cats" CANDIDATE_B="Dogs" python3 app.py
```

## Resetting votes

Use the form at the bottom of the page. If `RESET_SECRET` is set, enter it in the input field.

## Project structure

- `app.py`: Flask application
- `templates/index.html`: page template
- `static/main.js`: JS for voting and live results
- `static/styles.css`: styling
- `poll.db`: SQLite database (auto-created)
