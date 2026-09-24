const {
  createBook,
  getBookById,
  getAllBooks,
  searchBooks,
  updateBook,
  deleteBook,
} = require("../models/bookModel");
const {
  createTransaction,
  getActiveTransaction,
  updateTransaction,
} = require("../models/transactionModel");

async function getAll(req, res, next) {
  try {
    const filters = {};
    if (req.query.category) filters.category = req.query.category;
    if (req.query.status) filters.status = req.query.status;
    if (req.query.author) filters.author = req.query.author;

    const books = await getAllBooks(filters);

    res.status(200).json({
      message: "Books fetched successfully",
      count: books.length,
      books: books,
    });
  } catch (error) {
    next(error);
  }
}

async function getById(req, res, next) {
  try {
    const book = await getBookById(req.params.id);

    if (!book) {
      return res.status(404).json({ message: "Book not found" });
    }

    res.status(200).json({ book: book });
  } catch (error) {
    next(error);
  }
}

async function search(req, res, next) {
  try {
    const query = req.query.query;

    if (!query) {
      return res.status(400).json({ message: "Please provide a search query" });
    }

    const books = await searchBooks(query);

    res.status(200).json({
      message: "Search results",
      count: books.length,
      books: books,
    });
  } catch (error) {
    next(error);
  }
}

async function addBook(req, res, next) {
  try {
    const { title, author, isbn, category, quantity } = req.body;

    const newBook = await createBook({
      title,
      author,
      isbn,
      category,
      quantity: parseInt(quantity),
    });

    res.status(201).json({
      message: "Book added successfully",
      book: newBook,
    });
  } catch (error) {
    next(error);
  }
}

async function editBook(req, res, next) {
  try {
    const bookId = req.params.id;
    const { title, author, isbn, category, quantity, status } = req.body;

    const existingBook = await getBookById(bookId);
    if (!existingBook) {
      return res.status(404).json({ message: "Book not found" });
    }

    const updateData = {};
    if (title) updateData.title = title;
    if (author) updateData.author = author;
    if (isbn) updateData.isbn = isbn;
    if (category) updateData.category = category;
    if (quantity !== undefined) updateData.quantity = parseInt(quantity);
    if (status) updateData.status = status;

    const updatedBook = await updateBook(bookId, updateData);

    res.status(200).json({
      message: "Book updated successfully",
      book: updatedBook,
    });
  } catch (error) {
    next(error);
  }
}

async function removeBook(req, res, next) {
  try {
    const bookId = req.params.id;

    const deleted = await deleteBook(bookId);

    if (!deleted) {
      return res.status(404).json({ message: "Book not found" });
    }

    res.status(200).json({ message: "Book deleted successfully" });
  } catch (error) {
    next(error);
  }
}

async function borrowBook(req, res, next) {
  try {
    const bookId = req.params.id;
    const userId = req.user.userId;

    const book = await getBookById(bookId);
    if (!book) {
      return res.status(404).json({ message: "Book not found" });
    }

    if (book.quantity <= 0) {
      return res.status(400).json({ message: "Book is not available for borrowing" });
    }

    const existingTransaction = await getActiveTransaction(userId, bookId);
    if (existingTransaction) {
      return res.status(400).json({ message: "You have already borrowed this book" });
    }

    const newQuantity = book.quantity - 1;
    const newStatus = newQuantity === 0 ? "borrowed" : "available";

    await updateBook(bookId, {
      quantity: newQuantity,
      status: newStatus,
    });

    const borrowDate = new Date().toISOString();
    const dueDate = new Date();
    dueDate.setDate(dueDate.getDate() + 14);

    const transaction = await createTransaction({
      userId: userId,
      bookId: bookId,
      type: "borrow",
      borrowDate: borrowDate,
      returnDate: null,
      dueDate: dueDate.toISOString(),
      status: "active",
    });

    res.status(200).json({
      message: "Book borrowed successfully",
      transaction: transaction,
    });
  } catch (error) {
    next(error);
  }
}

async function returnBook(req, res, next) {
  try {
    const bookId = req.params.id;
    const userId = req.user.userId;

    const transaction = await getActiveTransaction(userId, bookId);
    if (!transaction) {
      return res.status(400).json({
        message: "You don't have an active borrow for this book",
      });
    }

    const returnDate = new Date().toISOString();
    await updateTransaction(transaction.transactionId, {
      type: "return",
      returnDate: returnDate,
      status: "returned",
    });

    const book = await getBookById(bookId);
    const newQuantity = book.quantity + 1;

    await updateBook(bookId, {
      quantity: newQuantity,
      status: "available",
    });

    res.status(200).json({
      message: "Book returned successfully",
    });
  } catch (error) {
    next(error);
  }
}

module.exports = {
  getAll,
  getById,
  search,
  addBook,
  editBook,
  removeBook,
  borrowBook,
  returnBook,
};
