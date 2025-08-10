function setStatus(message, type) {
  const status = document.getElementById('status');
  status.textContent = message;
  status.className = `status ${type || ''}`;
  if (message) {
    setTimeout(() => {
      status.textContent = '';
      status.className = 'status';
    }, 2000);
  }
}

async function postVote(candidate) {
  try {
    const response = await fetch('/vote', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
        'Accept': 'application/json'
      },
      body: `candidate=${encodeURIComponent(candidate)}`
    });
    if (!response.ok) throw new Error('Failed');
    await response.json();
    setStatus('Vote recorded!', 'success');
    await refreshResults();
  } catch (err) {
    setStatus('Error recording vote', 'error');
  }
}

async function refreshResults() {
  try {
    const response = await fetch('/results');
    if (!response.ok) throw new Error('Failed');
    const data = await response.json();

    const countA = document.getElementById('countA');
    const countB = document.getElementById('countB');
    const total = document.getElementById('total');
    const barA = document.getElementById('barA');
    const barB = document.getElementById('barB');

    countA.textContent = data.candidateA.votes;
    countB.textContent = data.candidateB.votes;
    total.textContent = data.total;

    const denom = Math.max(1, data.total);
    barA.style.width = `${(data.candidateA.votes / denom) * 100}%`;
    barB.style.width = `${(data.candidateB.votes / denom) * 100}%`;
  } catch (err) {
    // no-op for periodic refresh failures
  }
}

document.addEventListener('DOMContentLoaded', () => {
  const btnA = document.getElementById('btnA');
  const btnB = document.getElementById('btnB');

  btnA.addEventListener('click', () => postVote('A'));
  btnB.addEventListener('click', () => postVote('B'));

  refreshResults();
  setInterval(refreshResults, 4000);
});