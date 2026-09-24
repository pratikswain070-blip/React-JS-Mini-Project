const { body, validationResult } = require("express-validator");

const registerRules = [
  body("name")
    .notEmpty()
    .withMessage("Name is required")
    .trim(),
  body("email")
    .isEmail()
    .withMessage("Please provide a valid email")
    .normalizeEmail(),
  body("password")
    .isLength({ min: 6 })
    .withMessage("Password must be at least 6 characters long"),
  body("role")
    .isIn(["student", "librarian"])
    .withMessage("Role must be either student or librarian"),
];

const loginRules = [
  body("email")
    .notEmpty()
    .withMessage("Email is required")
    .isEmail()
    .withMessage("Please provide a valid email"),
  body("password")
    .notEmpty()
    .withMessage("Password is required"),
];

const bookRules = [
  body("title")
    .notEmpty()
    .withMessage("Title is required")
    .trim(),
  body("author")
    .notEmpty()
    .withMessage("Author is required")
    .trim(),
  body("isbn")
    .notEmpty()
    .withMessage("ISBN is required")
    .trim(),
  body("category")
    .notEmpty()
    .withMessage("Category is required")
    .trim(),
  body("quantity")
    .isInt({ min: 0 })
    .withMessage("Quantity must be a non-negative number"),
];

const roleUpdateRules = [
  body("role")
    .isIn(["student", "librarian"])
    .withMessage("Role must be either student or librarian"),
];

function validate(req, res, next) {
  const errors = validationResult(req);

  if (!errors.isEmpty()) {
    const errorMessages = errors.array().map((err) => err.msg);
    return res.status(400).json({
      message: "Validation failed",
      errors: errorMessages,
    });
  }

  next();
}

module.exports = {
  registerRules,
  loginRules,
  bookRules,
  roleUpdateRules,
  validate,
};
