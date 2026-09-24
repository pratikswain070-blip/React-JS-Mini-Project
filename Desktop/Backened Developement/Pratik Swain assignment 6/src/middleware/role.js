function role(requiredRole) {
  return (req, res, next) => {
    if (!req.user) {
      return res.status(401).json({ message: "Please login first" });
    }

    if (req.user.role !== requiredRole) {
      return res.status(403).json({
        message: `Only ${requiredRole}s can perform this action`,
      });
    }

    next();
  };
}

module.exports = role;
