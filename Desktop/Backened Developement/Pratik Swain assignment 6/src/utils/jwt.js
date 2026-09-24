const jwt = require("jsonwebtoken");

function generateToken(payload) {
  const secret = process.env.JWT_SECRET;
  const expiresIn = process.env.JWT_EXPIRES_IN || "1d";

  const token = jwt.sign(payload, secret, { expiresIn });
  return token;
}

function verifyToken(token) {
  const secret = process.env.JWT_SECRET;

  const decoded = jwt.verify(token, secret);
  return decoded;
}

module.exports = { generateToken, verifyToken };
