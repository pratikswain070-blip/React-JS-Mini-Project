import { useState } from 'react';
import { textToMorse } from './utils/morseCode.jsx';
import Header from './components/Header';
import ThemeToggle from './components/ThemeToggle';
import TextInput from './components/TextInput';
import MorseOutput from './components/MorseOutput';
import ActionButtons from './components/ActionButtons';
import MorseInfo from './components/MorseInfo';
import darkBg from './assets/dark-bg.png';
import lightBg from './assets/light-bg.png';
import './App.css';

const particles = ['·  —', '— · ·', '· · —', '— —', '· — ·', '— · — ·'];

function App() {
  const [inputText, setInputText] = useState('');
  const [copied, setCopied] = useState(false);
  const [darkMode, setDarkMode] = useState(true);

  const morseOutput = textToMorse(inputText);
  const handleInputChange = (e) => {
    setInputText(e.target.value);
    setCopied(false);
  };

  const handleCopy = async () => {
    if (!morseOutput) return;

    try {
      await navigator.clipboard.writeText(morseOutput);
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    } catch (err) {
      console.error('Failed to copy:', err);
    }
  };

  const handleClear = () => {
    setInputText('');
    setCopied(false);
  };

  const toggleTheme = () => setDarkMode((prev) => !prev);
  const bgImage = darkMode ? darkBg : lightBg;

  return (
    <div className={`app-wrapper ${darkMode ? 'dark' : 'light'}`}>
      <div
        className="bg-image"
        style={{ backgroundImage: `url(${bgImage})` }}
        aria-hidden="true"
      />
      <div className="bg-dots" aria-hidden="true" />

      <div className="floating-particles" aria-hidden="true">
        {particles.map((particle, index) => (
          <span className={`particle p${index + 1}`} key={index}>
            {particle}
          </span>
        ))}
      </div>

      <div className="page-content">
        <main className="card" id="translator-card">
          <ThemeToggle darkMode={darkMode} onToggle={toggleTheme} />
          <Header />

          <TextInput value={inputText} onChange={handleInputChange} />

          <div className="divider" aria-hidden="true">
            <span className="divider-icon">⚡</span>
          </div>

          <MorseOutput morseCode={morseOutput} />

          <ActionButtons
            morseCode={morseOutput}
            inputText={inputText}
            copied={copied}
            onCopy={handleCopy}
            onClear={handleClear}
          />

          <footer className="card-footer">Supports A–Z • 0–9 • Spaces ( / )</footer>
        </main>

        <MorseInfo />
      </div>
    </div>
  );
}

export default App;
