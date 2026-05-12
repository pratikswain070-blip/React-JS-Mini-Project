function ActionButtons({ morseCode, inputText, copied, onCopy, onClear }) {
  return (
    <div className="actions">
      <button
        className={`btn btn-copy ${copied ? 'btn-copied' : ''}`}
        onClick={onCopy}
        disabled={!morseCode}
        id="copy-btn"
      >
        {copied ? '✓  Copied!' : '📋  Copy to Clipboard'}
      </button>

      <button
        className="btn btn-clear"
        onClick={onClear}
        disabled={!inputText}
        id="clear-btn"
      >
        🗑️  Clear
      </button>
    </div>
  );
}

export default ActionButtons;
