const { db } = require("../config/firebase");

const booksCollection = db.collection("books");

async function createBook(bookData) {
  const bookRef = booksCollection.doc();
  const bookId = bookRef.id;

  const newBook = {
    bookId: bookId,
    title: bookData.title,
    author: bookData.author,
    isbn: bookData.isbn,
    category: bookData.category,
    status: "available",
    quantity: bookData.quantity,
    createdAt: new Date().toISOString(),
  };

  await bookRef.set(newBook);
  return newBook;
}

async function getBookById(bookId) {
  const snapshot = await booksCollection.where("bookId", "==", bookId).get();

  if (snapshot.empty) {
    return null;
  }

  return snapshot.docs[0].data();
}

async function getAllBooks(filters = {}) {
  let query = booksCollection;

  if (filters.category) {
    query = query.where("category", "==", filters.category);
  }
  if (filters.status) {
    query = query.where("status", "==", filters.status);
  }
  if (filters.author) {
    query = query.where("author", "==", filters.author);
  }

  const snapshot = await query.get();
  const books = [];

  snapshot.forEach((doc) => {
    books.push(doc.data());
  });

  return books;
}

async function searchBooks(searchQuery) {
  const snapshot = await booksCollection.get();
  const books = [];
  const lowerQuery = searchQuery.toLowerCase();

  snapshot.forEach((doc) => {
    const book = doc.data();
    if (
      book.title.toLowerCase().includes(lowerQuery) ||
      book.author.toLowerCase().includes(lowerQuery)
    ) {
      books.push(book);
    }
  });

  return books;
}

async function updateBook(bookId, updateData) {
  const snapshot = await booksCollection.where("bookId", "==", bookId).get();

  if (snapshot.empty) {
    return null;
  }

  const docRef = snapshot.docs[0].ref;
  await docRef.update(updateData);

  const updatedDoc = await docRef.get();
  return updatedDoc.data();
}

async function deleteBook(bookId) {
  const snapshot = await booksCollection.where("bookId", "==", bookId).get();

  if (snapshot.empty) {
    return false;
  }

  await snapshot.docs[0].ref.delete();
  return true;
}

module.exports = {
  createBook,
  getBookById,
  getAllBooks,
  searchBooks,
  updateBook,
  deleteBook,
};
