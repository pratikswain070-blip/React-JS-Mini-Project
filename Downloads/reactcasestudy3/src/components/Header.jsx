import telegraphImg from '../assets/telegraph.png';

function Header() {
  return (
    <header className="card-header">
      <img src={telegraphImg} alt="Telegraph machine" className="logo-image" />
      <h1>Morse Code Translator</h1>
      <p className="subtitle">Type English text and see it converted to Morse code instantly</p>
    </header>
  );
}

export default Header;
