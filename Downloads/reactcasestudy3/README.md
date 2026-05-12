# Morse Code Translator (React)

A beginner-friendly React app that converts English text to Morse code in real time.

## Features
- Live translation of typed text to Morse code
- Copy output to clipboard and clear input
- Light/dark theme toggle
- Educational `MorseInfo` sections with history, timeline, tips, and quick reference

## Quick Start
1. Install dependencies:

```bash
npm install
```

2. Run the development server:

```bash
npm run dev
```

3. Build for production:

```bash
npm run build
```

4. (Optional) Preview the production build locally:

```bash
npm run preview
```

## Key Files
- `src/App.jsx` — main app and state management
- `src/components/` — UI components (`TextInput`, `MorseOutput`, `MorseInfo`, etc.)
- `src/utils/morseCode.jsx` — translation logic
- `src/components/MorseInfo.jsx` and `src/components/MorseInfo.css` — educational content and styles

## Contributing
Open issues or pull requests. Keep changes small and verify with `npm run build`.

---
Simple and clear, intended for learners to read and modify.
