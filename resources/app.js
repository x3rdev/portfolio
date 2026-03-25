document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById('noise-canvas');
    const ctx = canvas.getContext('2d');

    function drawNoise() {
        const W = canvas.width  = window.innerWidth;
        const H = canvas.height = window.innerHeight;
        const img = ctx.createImageData(W, H);
        const data = img.data;
        for (let i = 0; i < data.length; i += 4) {
            const v = Math.random() * 255 | 0;
            data[i] = data[i+1] = data[i+2] = v;
            data[i+3] = (Math.random() * 45 | 0) + 45;
        }
        ctx.putImageData(img, 0, 0);
    }

    drawNoise();
    window.addEventListener('resize', drawNoise);
});

(function setupThemeToggle() {
    const body = document.body;
    const toggle = document.querySelector('[data-theme-toggle]');
    if (!toggle) return;

    const THEME_KEY = 'portfolio-theme';
    const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
    const savedTheme = localStorage.getItem(THEME_KEY);
    const initialTheme = savedTheme || (prefersDark ? 'dark' : 'light');

    function applyTheme(theme) {
        body.classList.toggle('theme-light', theme === 'light');
        toggle.setAttribute('aria-pressed', theme === 'light');
        toggle.innerHTML = theme === 'light'
            ? '<i data-lucide="sun"></i>'
            : '<i data-lucide="moon"></i>';
        if (window.lucide && typeof window.lucide.createIcons === 'function') {
            window.lucide.createIcons();
        }
        localStorage.setItem(THEME_KEY, theme);
    }

    applyTheme(initialTheme);

    toggle.addEventListener('click', () => {
        const current = body.classList.contains('theme-light') ? 'light' : 'dark';
        applyTheme(current === 'light' ? 'dark' : 'light');
    });
})();

const scrollLine = document.getElementById('scroll-line');
window.addEventListener('scroll', () => {
    const scrolled = window.scrollY;
    const total = document.documentElement.scrollHeight - window.innerHeight;
    scrollLine.style.transform = `scaleY(${scrolled / total})`;
});

const conCanvas = document.getElementById('constellation-canvas');
const conCtx = conCanvas.getContext('2d');

const DOTS = 120;
const MAX_DIST = 120;
let dots = [];

function initConstellation() {
    conCanvas.width  = window.innerWidth;
    conCanvas.height = window.innerHeight;
    dots = Array.from({ length: DOTS }, () => ({
        x: Math.random() * conCanvas.width,
        y: Math.random() * conCanvas.height,
        vx: (Math.random() - 0.5) * 0.4,
        vy: (Math.random() - 0.5) * 0.4,
        r: Math.random() * 1.5 + 0.4,
    }));
}

function drawConstellation() {
    const W = conCanvas.width, H = conCanvas.height;
    conCtx.clearRect(0, 0, W, H);

    for (let i = 0; i < dots.length; i++) {
        const a = dots[i];
        for (let j = i + 1; j < dots.length; j++) {
            const b = dots[j];
            const dx = a.x - b.x, dy = a.y - b.y;
            const dist = Math.sqrt(dx*dx + dy*dy);
            if (dist < MAX_DIST) {
                const alpha = (1 - dist / MAX_DIST) * 0.7;
                conCtx.beginPath();
                conCtx.strokeStyle = `rgba(255,40,40,${alpha})`;
                conCtx.lineWidth = 0.5;
                conCtx.moveTo(a.x, a.y);
                conCtx.lineTo(b.x, b.y);
                conCtx.stroke();
            }
        }
    }

    dots.forEach(d => {
        conCtx.beginPath();
        conCtx.arc(d.x, d.y, d.r, 0, Math.PI * 2);
        conCtx.fillStyle = 'rgba(255,40,40,0.4)';
        conCtx.fill();

        d.x += d.vx;
        d.y += d.vy;
        if (d.x < 0 || d.x > W) d.vx *= -1;
        if (d.y < 0 || d.y > H) d.vy *= -1;
    });

    requestAnimationFrame(drawConstellation);
}

initConstellation();
drawConstellation();
window.addEventListener('resize', initConstellation);
if (window.lucide && typeof window.lucide.createIcons === 'function') {
    window.lucide.createIcons();
}
