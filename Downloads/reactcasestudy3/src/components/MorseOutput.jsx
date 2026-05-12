function MorseOutput({ morseCode }) {
  return (
    <section className="output-section" aria-label="Morse code output">
      <label className="section-label">Morse Code</label>

      <div className="morse-output" id="morse-output">
        {morseCode || (
          <span className="placeholder-text">
            Your Morse code will appear here…
          </span>
        )}
      </div>
    </section>
  );
}

export default MorseOutput;
