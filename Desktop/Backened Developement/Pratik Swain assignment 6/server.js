require("dotenv").config();

const express = require("express");
const cors = require("cors");
const helmet = require("helmet");
const swaggerUi = require("swagger-ui-express");

require("./src/config/firebase");

const logger = require("./src/middleware/logger");
const rateLimiter = require("./src/middleware/rateLimiter");
const errorHandler = require("./src/middleware/errorHandler");

const authRoutes = require("./src/routes/authRoutes");
const bookRoutes = require("./src/routes/bookRoutes");
const transactionRoutes = require("./src/routes/transactionRoutes");
const userRoutes = require("./src/routes/userRoutes");

const { swaggerSpec } = require("./src/config/swagger");

const app = express();

app.use(cors());
app.use(helmet());
app.use(express.json());
app.use(logger);
app.use(rateLimiter);

app.get("/", (req, res) => {
  res.status(200).json({
    message: "Library Management API is running",
  });
});

app.use("/api/auth", authRoutes);
app.use("/api/books", bookRoutes);
app.use("/api/transactions", transactionRoutes);
app.use("/api/users", userRoutes);

app.use("/api-docs", swaggerUi.serve, swaggerUi.setup(swaggerSpec));

app.use(errorHandler);

const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
  console.log(`API Docs: http://localhost:${PORT}/api-docs`);
});
