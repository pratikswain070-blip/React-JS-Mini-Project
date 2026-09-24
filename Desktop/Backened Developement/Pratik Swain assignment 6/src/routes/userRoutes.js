const express = require("express");
const router = express.Router();
const { getAll, getById, updateRole, removeUser } = require("../controllers/userController");
const auth = require("../middleware/auth");
const role = require("../middleware/role");
const { roleUpdateRules, validate } = require("../middleware/validator");

router.get("/", auth, role("librarian"), getAll);
router.get("/:id", auth, role("librarian"), getById);
router.put("/:id/role", auth, role("librarian"), roleUpdateRules, validate, updateRole);
router.delete("/:id", auth, role("librarian"), removeUser);

module.exports = router;
