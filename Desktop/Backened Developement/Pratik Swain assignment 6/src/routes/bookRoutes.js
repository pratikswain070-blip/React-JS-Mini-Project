const express = require("express");
const router = express.Router();
const {
  getAll,
  getById,
  search,
  addBook,
  editBook,
  removeBook,
  borrowBook,
  returnBook,
} = require("../controllers/bookController");
const auth = require("../middleware/auth");
const role = require("../middleware/role");
const { bookRules, validate } = require("../middleware/validator");

router.get("/search", auth, search);

router.get("/", auth, getAll);
router.get("/:id", auth, getById);

router.post("/", auth, role("librarian"), bookRules, validate, addBook);
router.put("/:id", auth, role("librarian"), editBook);
router.delete("/:id", auth, role("librarian"), removeBook);

router.post("/:id/borrow", auth, role("student"), borrowBook);
router.post("/:id/return", auth, role("student"), returnBook);

module.exports = router;
