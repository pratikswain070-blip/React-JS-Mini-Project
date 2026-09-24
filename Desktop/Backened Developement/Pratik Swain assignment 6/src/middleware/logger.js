function logger(req, res, next) {
  const now = new Date();
  const timestamp = now.toISOString().replace("T", " ").substring(0, 19);

  const method = req.method;
  const url = req.originalUrl;

  const userId = req.user ? req.user.userId : "Guest";

  console.log(`[${timestamp}] ${method} ${url} User: ${userId}`);

  next();
}

module.exports = logger;
