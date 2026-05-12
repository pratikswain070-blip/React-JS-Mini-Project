function TextInput({ value, onChange }) {
  return (
    <section className="input-section" aria-label="English text input">
      <label htmlFor="english-input" className="section-label">
        English Text
      </label>

      <textarea
        id="english-input"
        className="text-input"
        placeholder="Type something… e.g. HELLO WORLD"
        value={value}
        onChange={onChange}
        rows={4}
        autoFocus
      />

      <div className="char-counter" id="char-counter">
        <span className="counter-dot" />
        {value.length} character{value.length !== 1 ? 's' : ''}
      </div>
    </section>
  );
}

export default TextInput;
