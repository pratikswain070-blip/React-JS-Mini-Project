const {
  getAllTransactions,
  getUserTransactions,
} = require("../models/transactionModel");

async function getAll(req, res, next) {
  try {
    const transactions = await getAllTransactions();

    res.status(200).json({
      message: "All transactions fetched successfully",
      count: transactions.length,
      transactions: transactions,
    });
  } catch (error) {
    next(error);
  }
}

async function getMyTransactions(req, res, next) {
  try {
    const userId = req.user.userId;
    const transactions = await getUserTransactions(userId);

    res.status(200).json({
      message: "Your transactions fetched successfully",
      count: transactions.length,
      transactions: transactions,
    });
  } catch (error) {
    next(error);
  }
}

module.exports = { getAll, getMyTransactions };
