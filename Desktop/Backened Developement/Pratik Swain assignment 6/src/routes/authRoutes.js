const express = require("express");
const router = express.Router();
const { register, login, getProfile, updateProfile } = require("../controllers/authController");
const auth = require("../middleware/auth");
const { registerRules, loginRules, validate } = require("../middleware/validator");

router.post("/register", registerRules, validate, register);
router.post("/login", loginRules, validate, login);

router.get("/profile", auth, getProfile);
router.put("/profile", auth, updateProfile);

module.exports = router;
