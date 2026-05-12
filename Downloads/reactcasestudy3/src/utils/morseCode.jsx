// morseCode.jsx — Utility file for Morse code mapping and conversion

// Each letter (A–Z) and digit (0–9) maps to its Morse code equivalent.
const MORSE_CODE_MAP = {
  A: '.-',    B: '-...',  C: '-.-.',  D: '-..',
  E: '.',     F: '..-.',  G: '--.',   H: '....',
  I: '..',    J: '.---',  K: '-.-',   L: '.-..',
  M: '--',    N: '-.',    O: '---',   P: '.--.',
  Q: '--.-',  R: '.-.',   S: '...',   T: '-',
  U: '..-',   V: '...-',  W: '.--',   X: '-..-',
  Y: '-.--',  Z: '--..',
  0: '-----', 1: '.----', 2: '..---', 3: '...--',
  4: '....-', 5: '.....', 6: '-....', 7: '--...',
  8: '---..', 9: '----.',
};

// Converts a plain-text string into Morse code.
// - Uppercase conversion so both 'a' and 'A' work.
// - Spaces between words become ' / '.
// - Unsupported characters are silently ignored.
export function textToMorse(text) {
  return text
    .toUpperCase()
    .split('')
    .map((char) => {
      if (char === ' ') return '/';
      return MORSE_CODE_MAP[char] || '';
    })
    .filter((code) => code !== '')
    .join(' ');
}

export default MORSE_CODE_MAP;
