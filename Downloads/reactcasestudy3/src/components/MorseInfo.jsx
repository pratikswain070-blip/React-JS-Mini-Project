import morseHistoryImg from '../assets/morse-history.png';
import morseChartImg from '../assets/morse-chart.png';
import './MorseInfo.css';

const quickRef = [
  { char: 'S O S', morse: '··· ——— ···', note: 'Universal distress signal' },
  { char: 'H E L L O', morse: '···· · ·-·· ·-·· ———', note: 'Common greeting' },
  { char: 'L O V E', morse: '·-·· ——— ···- ·', note: 'Popular message' },
];

const funFacts = [
  {

    title: 'Titanic SOS',
    text: 'The Titanic\'s distress signal in 1912 was one of the most famous uses of Morse code. Operators sent "CQD" and the newer "SOS" to call for help.',
  },
  {
    emoji: '⚡',
    title: 'First Message',
    text: '"What hath God wrought?" — the first official Morse code message sent by Samuel Morse on May 24, 1844, from Washington D.C. to Baltimore.',
  },
  {

    title: 'Still in Use',
    text: 'Morse code is still used today by amateur radio operators, aviation, and the military. It was officially retired from maritime use only in 1999.',
  },
  {

    title: 'Accessibility',
    text: 'Morse code helps people with disabilities communicate. Google\'s Gboard keyboard supports Morse input for users with limited mobility.',
  },
];

const timeline = [
  { year: '1836', event: 'Samuel Morse develops the first practical telegraph system' },
  { year: '1838', event: 'Morse code alphabet is created with Alfred Vail' },
  { year: '1844', event: 'First telegraph message sent: "What hath God wrought?"' },
  { year: '1851', event: 'International Morse Code standardized for global use' },
  { year: '1865', event: 'International Telegraph Union founded (now ITU)' },
  { year: '1912', event: 'Titanic sinking popularizes SOS distress signal worldwide' },
  { year: '1999', event: 'Maritime Morse code officially retired (replaced by GMDSS)' },
  { year: 'Today', event: 'Still used in amateur radio, aviation, and assistive technology' },
];

function MorseInfo() {
  return (
    <div className="info-container">
      <section className="info-section" id="what-is-morse">
        <div className="section-badge">Learn</div>
        <h2>What is Morse Code?</h2>
        <p>
          Morse code is a method of encoding text characters using two different signal
          durations — <strong>dots</strong> (short signals, written as <code>·</code>) and
          <strong> dashes</strong> (long signals, written as <code>—</code>). Each letter,
          number, and some punctuation marks are represented by a unique combination of
          these dots and dashes.
        </p>
        <p>
          Unlike modern digital communication that relies on complex hardware and software,
          Morse code can be transmitted using the simplest of means — a flashlight, a
          whistle, tapping on a surface, or even blinking your eyes. This simplicity is
          what makes it one of the most resilient communication systems ever invented.
        </p>
        <div className="info-image-wrapper">
          <img src={morseChartImg} alt="Morse code alphabet reference chart showing A through Z" className="info-image" />
          <span className="image-caption">The complete Morse code alphabet — A to Z</span>
        </div>
      </section>
      <div className="other-sections">
        <section className="info-section" id="morse-history">
        <div className="section-badge">History</div>
        <h2>The Story Behind Morse Code</h2>
        <div className="info-image-wrapper hero-image">
          <img
            src={morseHistoryImg}
            alt="Samuel Morse sending the first telegraph message in 1844"
            className="info-image"
          />
          <span className="image-caption">Samuel Morse sending the first telegraph message, 1844</span>
        </div>
        <p>
          Morse code was developed in the 1830s by <strong>Samuel F.B. Morse</strong>, an
          American painter and inventor, along with his assistant <strong>Alfred Vail</strong>.
          Morse originally conceived the idea of an electric telegraph after learning that
          electromagnetic impulses could be sent through wires.
        </p>
        <p>
          On May 24, 1844, Morse sent the historic first message — <em>"What hath God
          wrought?"</em> — from the U.S. Capitol in Washington, D.C. to a railroad
          station in Baltimore, Maryland. This moment marked the birth of long-distance
          electronic communication and changed the world forever.
        </p>
        </section>
        <section className="info-section" id="morse-timeline">
        <div className="section-badge">Timeline</div>
        <h2>Key Moments in Morse Code History</h2>
        <div className="timeline">
          {timeline.map((item, i) => (
            <div className="timeline-item" key={i}>
              <div className="timeline-year">{item.year}</div>
              <div className="timeline-line">
                <span className="timeline-dot" />
              </div>
              <div className="timeline-event">{item.event}</div>
            </div>
          ))}
        </div>
        </section>
        <section className="info-section" id="why-morse">
        <div className="section-badge">Importance</div>
        <h2>Why Does Morse Code Still Matter?</h2>
        <div className="importance-grid">
          <div className="importance-card">
            <span className="importance-icon"></span>
            <h3>Emergency Survival</h3>
            <p>
              In emergencies where electronic communication fails, Morse code can save
              lives. SOS (··· ——— ···) can be signaled with a flashlight, mirror, or
              even by tapping — no batteries, no internet required.
            </p>
          </div>
          <div className="importance-card">
            <span className="importance-icon"></span>
            <h3>Radio Communication</h3>
            <p>
              Amateur (ham) radio operators worldwide still use Morse code daily. It
              can cut through noise and interference far better than voice, making it
              invaluable in poor signal conditions.
            </p>
          </div>
          <div className="importance-card">
            <span className="importance-icon"></span>
            <h3>Assistive Technology</h3>
            <p>
              Morse code empowers people with physical disabilities to communicate.
              Simple two-switch input devices let users type any message using just
              dots and dashes.
            </p>
          </div>
          <div className="importance-card">
            <span className="importance-icon"></span>
            <h3>Aviation & Navigation</h3>
            <p>
              Navigational beacons (VOR, NDB) at airports still identify themselves
              using Morse code. Pilots learn to recognize these signals as part of
              their training.
            </p>
          </div>
        </div>
        </section>
        <section className="info-section" id="fun-facts">
        <div className="section-badge">Did You Know?</div>
        <h2>Interesting Facts About Morse Code</h2>
        <div className="facts-grid">
          {funFacts.map((fact, i) => (
            <div className="fact-card" key={i}>
              <span className="fact-emoji">{fact.emoji}</span>
              <h3>{fact.title}</h3>
              <p>{fact.text}</p>
            </div>
          ))}
        </div>
        </section>
        <section className="info-section" id="quick-ref">
        <div className="section-badge">Reference</div>
        <h2>Popular Phrases in Morse Code</h2>
        <div className="ref-table-wrapper">
          <table className="ref-table">
            <thead>
              <tr>
                <th>Text</th>
                <th>Morse Code</th>
                <th>Note</th>
              </tr>
            </thead>
            <tbody>
              {quickRef.map((row, i) => (
                <tr key={i}>
                  <td className="ref-char">{row.char}</td>
                  <td className="ref-morse">{row.morse}</td>
                  <td className="ref-note">{row.note}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
        </section>
      </div>
      <section className="info-section" id="learn-morse">
        <div className="section-badge">Tips</div>
        <h2>How to Learn Morse Code</h2>
        <div className="tips-list">
          <div className="tip-item">
            <span className="tip-number">01</span>
            <div>
              <h3>Start with Common Letters</h3>
              <p>Learn E (·), T (—), A (·—), and I (··) first. These are the most frequently used letters in English.</p>
            </div>
          </div>
          <div className="tip-item">
            <span className="tip-number">02</span>
            <div>
              <h3>Use Mnemonics</h3>
              <p>Associate each letter with a word that matches its rhythm. For example, "Goo-gle" for G (— — ·) — two long, one short.</p>
            </div>
          </div>
          <div className="tip-item">
            <span className="tip-number">03</span>
            <div>
              <h3>Practice with This Translator</h3>
              <p>Type words above and study the output. Start with your name, then try short sentences. Repetition builds muscle memory.</p>
            </div>
          </div>
          <div className="tip-item">
            <span className="tip-number">04</span>
            <div>
              <h3>Listen to Morse Audio</h3>
              <p>Find Morse code audio practice tools online. Hearing the rhythm of dots and dashes is the fastest way to internalize the patterns.</p>
            </div>
          </div>
        </div>
      </section>
    </div>
  );
}

export default MorseInfo;
