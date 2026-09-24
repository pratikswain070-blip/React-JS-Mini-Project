const express = require("express");
const router = express.Router();
const { getAll, getMyTransactions } = require("../controllers/transactionController");
const auth = require("../middleware/auth");
const role = require("../middleware/role");

router.get("/my", auth, getMyTransactions);
router.get("/", auth, role("librarian"), getAll);

module.exports = router;
