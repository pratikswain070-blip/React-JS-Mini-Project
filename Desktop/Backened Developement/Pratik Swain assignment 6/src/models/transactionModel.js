const { db } = require("../config/firebase");

const transactionsCollection = db.collection("transactions");

async function createTransaction(transactionData) {
  const transRef = transactionsCollection.doc();
  const transactionId = transRef.id;

  const newTransaction = {
    transactionId: transactionId,
    userId: transactionData.userId,
    bookId: transactionData.bookId,
    type: transactionData.type,
    borrowDate: transactionData.borrowDate,
    returnDate: transactionData.returnDate || null,
    dueDate: transactionData.dueDate,
    status: transactionData.status,
  };

  await transRef.set(newTransaction);
  return newTransaction;
}

async function getTransactionById(transactionId) {
  const snapshot = await transactionsCollection
    .where("transactionId", "==", transactionId)
    .get();

  if (snapshot.empty) {
    return null;
  }

  return snapshot.docs[0].data();
}

async function getAllTransactions() {
  const snapshot = await transactionsCollection.get();
  const transactions = [];

  snapshot.forEach((doc) => {
    transactions.push(doc.data());
  });

  return transactions;
}

async function getUserTransactions(userId) {
  const snapshot = await transactionsCollection
    .where("userId", "==", userId)
    .get();

  const transactions = [];

  snapshot.forEach((doc) => {
    transactions.push(doc.data());
  });

  return transactions;
}

async function getActiveTransaction(userId, bookId) {
  const snapshot = await transactionsCollection
    .where("userId", "==", userId)
    .where("bookId", "==", bookId)
    .where("status", "==", "active")
    .get();

  if (snapshot.empty) {
    return null;
  }

  return snapshot.docs[0].data();
}

async function updateTransaction(transactionId, updateData) {
  const snapshot = await transactionsCollection
    .where("transactionId", "==", transactionId)
    .get();

  if (snapshot.empty) {
    return null;
  }

  const docRef = snapshot.docs[0].ref;
  await docRef.update(updateData);

  const updatedDoc = await docRef.get();
  return updatedDoc.data();
}

module.exports = {
  createTransaction,
  getTransactionById,
  getAllTransactions,
  getUserTransactions,
  getActiveTransaction,
  updateTransaction,
};
