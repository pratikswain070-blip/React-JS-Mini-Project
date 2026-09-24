# Library Management API

A simple **Library Management System REST API** built with Node.js, Express.js, and Firebase Firestore.

This project allows students to borrow and return books, and librarians to manage books and users.

---

## Features

- User registration and login with JWT authentication
- Role-based access control (Student & Librarian)
- Book management (CRUD operations)
- Book borrowing and returning system
- Transaction tracking
- User management for librarians
- Input validation
- Rate limiting
- Request logging
- Swagger API documentation
- Security headers with Helmet
- CORS enabled

---

## Technologies Used

| Technology       | Purpose                          |
| ---------------- | -------------------------------- |
| Node.js          | Runtime environment              |
| Express.js       | Web framework                    |
| Firebase Admin   | Firestore database               |
| JWT              | Authentication tokens            |
| bcryptjs         | Password hashing                 |
| express-validator| Input validation                 |
| express-rate-limit| Rate limiting                   |
| Swagger          | API documentation                |
| Helmet           | Security headers                 |
| CORS             | Cross-origin requests            |
| dotenv           | Environment variables            |
| nodemon          | Development auto-restart         |

---

## Folder Structure

```
Pratik Swain assignment 6/
│
├── server.js                      # Entry point
├── package.json                   # Dependencies and scripts
├── .env                           # Environment variables (not committed)
├── .env.example                   # Example environment variables
├── .gitignore                     # Files to ignore in git
├── README.md                      # This file
│
├── src/
│   ├── config/
│   │   ├── firebase.js            # Firebase Admin SDK setup
│   │   └── swagger.js             # Swagger configuration
│   │
│   ├── middleware/
│   │   ├── auth.js                # JWT authentication middleware
│   │   ├── role.js                # Role-based access middleware
│   │   ├── logger.js              # Request logging middleware
│   │   ├── rateLimiter.js         # Rate limiting middleware
│   │   ├── validator.js           # Validation middleware
│   │   └── errorHandler.js        # Global error handler
│   │
│   ├── routes/
│   │   ├── authRoutes.js          # Auth endpoints
│   │   ├── bookRoutes.js          # Book endpoints
│   │   ├── transactionRoutes.js   # Transaction endpoints
│   │   └── userRoutes.js          # User management endpoints
│   │
│   ├── controllers/
│   │   ├── authController.js      # Auth logic
│   │   ├── bookController.js      # Book logic
│   │   ├── transactionController.js # Transaction logic
│   │   └── userController.js      # User management logic
│   │
│   ├── models/
│   │   ├── userModel.js           # User Firestore operations
│   │   ├── bookModel.js           # Book Firestore operations
│   │   └── transactionModel.js    # Transaction Firestore operations
│   │
│   └── utils/
│       ├── jwt.js                 # JWT helper functions
│       └── validation.js          # Validation rules
│
└── docs/
    └── swagger.yaml               # API documentation
```

---

## Installation

### Step 1: Clone or download the project

```bash
cd "Pratik Swain assignment 6"
```

### Step 2: Install dependencies

```bash
npm install
```

---

## Firebase Setup

### Step 1: Create a Firebase project

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Click **Add Project**
3. Give it a name and create it

### Step 2: Enable Firestore

1. In your Firebase project, go to **Build > Firestore Database**
2. Click **Create Database**
3. Choose **Start in test mode** (for development)
4. Select a region and click **Enable**

### Step 3: Get Service Account Key

1. Go to **Project Settings** (gear icon)
2. Click **Service Accounts** tab
3. Click **Generate new private key**
4. A JSON file will download — open it and copy the values

### Step 4: Update .env file

Copy the values from the downloaded JSON file to your `.env` file:

```
FIREBASE_PROJECT_ID=your-project-id
FIREBASE_CLIENT_EMAIL=firebase-adminsdk-xxxxx@your-project-id.iam.gserviceaccount.com
FIREBASE_PRIVATE_KEY="-----BEGIN PRIVATE KEY-----\nYOUR_ACTUAL_KEY_HERE\n-----END PRIVATE KEY-----\n"
```

**Important:** The `FIREBASE_PRIVATE_KEY` must be wrapped in double quotes and keep the `\n` characters.

---

## Environment Variables

Create a `.env` file in the root directory (copy from `.env.example`):

```
PORT=5000
JWT_SECRET=your_jwt_secret_here
JWT_EXPIRES_IN=1d
FIREBASE_PROJECT_ID=your-project-id
FIREBASE_CLIENT_EMAIL=your-service-account-email
FIREBASE_PRIVATE_KEY="your-private-key"
```

**Never commit your `.env` file to GitHub!**

---

## How to Run

### Development mode (with auto-restart)

```bash
npm run dev
```

### Production mode

```bash
npm start
```

The server will start on: **http://localhost:5000**

---

## API Endpoints

### Authentication

| Method | Endpoint            | Access  | Description          |
| ------ | ------------------- | ------- | -------------------- |
| POST   | /api/auth/register  | Public  | Register a new user  |
| POST   | /api/auth/login     | Public  | Login and get token  |
| GET    | /api/auth/profile   | Auth    | Get my profile       |
| PUT    | /api/auth/profile   | Auth    | Update my profile    |

### Books

| Method | Endpoint                | Access    | Description        |
| ------ | ----------------------- | --------- | ------------------ |
| GET    | /api/books              | Auth      | Get all books      |
| GET    | /api/books/search       | Auth      | Search books       |
| GET    | /api/books/:id          | Auth      | Get single book    |
| POST   | /api/books              | Librarian | Add a book         |
| PUT    | /api/books/:id          | Librarian | Update a book      |
| DELETE | /api/books/:id          | Librarian | Delete a book      |
| POST   | /api/books/:id/borrow   | Student   | Borrow a book      |
| POST   | /api/books/:id/return   | Student   | Return a book      |

### Transactions

| Method | Endpoint               | Access    | Description            |
| ------ | ---------------------- | --------- | ---------------------- |
| GET    | /api/transactions      | Librarian | Get all transactions   |
| GET    | /api/transactions/my   | Auth      | Get my transactions    |

### Users

| Method | Endpoint              | Access    | Description         |
| ------ | --------------------- | --------- | ------------------- |
| GET    | /api/users            | Librarian | Get all users       |
| GET    | /api/users/:id        | Librarian | Get single user     |
| PUT    | /api/users/:id/role   | Librarian | Update user role    |
| DELETE | /api/users/:id        | Librarian | Delete a user       |

---

## Authentication

This API uses **JWT (JSON Web Token)** for authentication.

### How it works:

1. Register or login to get a token
2. Include the token in the `Authorization` header of your requests:

```
Authorization: Bearer YOUR_TOKEN_HERE
```

---

## Permissions

| Endpoint              | Student | Librarian |
| --------------------- | ------- | --------- |
| Register              | ✅ Public | ✅ Public |
| Login                 | ✅ Public | ✅ Public |
| View Profile          | ✅       | ✅        |
| Update Profile        | ✅       | ✅        |
| View Books            | ✅       | ✅        |
| Search Books          | ✅       | ✅        |
| Add Book              | ❌       | ✅        |
| Update Book           | ❌       | ✅        |
| Delete Book           | ❌       | ✅        |
| Borrow Book           | ✅       | ❌        |
| Return Book           | ✅       | ❌        |
| My Transactions       | ✅       | ✅        |
| All Transactions      | ❌       | ✅        |
| View Users            | ❌       | ✅        |
| View User             | ❌       | ✅        |
| Change User Role      | ❌       | ✅        |
| Delete User           | ❌       | ✅        |

---

## Swagger Documentation

Open in your browser:

```
http://localhost:5000/api-docs
```

You can test all endpoints directly from the Swagger UI.

To authenticate in Swagger:
1. Login first to get a token
2. Click the **Authorize** button (lock icon)
3. Enter: `Bearer YOUR_TOKEN_HERE`
4. Click **Authorize**

---

## Postman Testing Guide

### Step 1: Register a Librarian

```
POST http://localhost:5000/api/auth/register
Content-Type: application/json

{
  "name": "Admin Librarian",
  "email": "librarian@gmail.com",
  "password": "123456",
  "role": "librarian"
}
```

### Step 2: Login as Librarian

```
POST http://localhost:5000/api/auth/login
Content-Type: application/json

{
  "email": "librarian@gmail.com",
  "password": "123456"
}
```

Copy the `token` from the response.

### Step 3: Add Books (use librarian token)

```
POST http://localhost:5000/api/books
Authorization: Bearer YOUR_LIBRARIAN_TOKEN
Content-Type: application/json

{
  "title": "JavaScript Basics",
  "author": "John Smith",
  "isbn": "123456789",
  "category": "Programming",
  "quantity": 5
}
```

### Step 4: Register a Student

```
POST http://localhost:5000/api/auth/register
Content-Type: application/json

{
  "name": "Rahul Student",
  "email": "rahul@gmail.com",
  "password": "123456",
  "role": "student"
}
```

### Step 5: Login as Student

```
POST http://localhost:5000/api/auth/login
Content-Type: application/json

{
  "email": "rahul@gmail.com",
  "password": "123456"
}
```

Copy the student `token`.

### Step 6: View Books (use student token)

```
GET http://localhost:5000/api/books
Authorization: Bearer YOUR_STUDENT_TOKEN
```

### Step 7: Borrow a Book

```
POST http://localhost:5000/api/books/BOOK_ID/borrow
Authorization: Bearer YOUR_STUDENT_TOKEN
```

Replace `BOOK_ID` with the actual book ID from Step 6.

### Step 8: Check My Transactions

```
GET http://localhost:5000/api/transactions/my
Authorization: Bearer YOUR_STUDENT_TOKEN
```

### Step 9: Return the Book

```
POST http://localhost:5000/api/books/BOOK_ID/return
Authorization: Bearer YOUR_STUDENT_TOKEN
```

### Step 10: Check All Transactions (librarian)

```
GET http://localhost:5000/api/transactions
Authorization: Bearer YOUR_LIBRARIAN_TOKEN
```

### Step 11: Test Unauthorized Access

Try accessing a librarian route with a student token:

```
POST http://localhost:5000/api/books
Authorization: Bearer YOUR_STUDENT_TOKEN
Content-Type: application/json

{
  "title": "Test Book",
  "author": "Test",
  "isbn": "999",
  "category": "Test",
  "quantity": 1
}
```

Expected response: `403 - Only librarians can perform this action`

### Step 12: Test Rate Limiting

Send more than 100 requests within 15 minutes to see the rate limit message.

### Step 13: Open Swagger

Visit `http://localhost:5000/api-docs` in your browser to test endpoints visually.

---

## Example Responses

### Successful Registration

```json
{
  "message": "User registered successfully",
  "user": {
    "userId": "abc123",
    "name": "Rahul",
    "email": "rahul@gmail.com",
    "role": "student",
    "createdAt": "2026-09-02T10:30:00.000Z"
  }
}
```

### Successful Login

```json
{
  "message": "Login successful",
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

### Error Response

```json
{
  "message": "Book not found"
}
```

### Validation Error

```json
{
  "message": "Validation failed",
  "errors": ["Password must be at least 6 characters long"]
}
```

---

## Common Errors and Fixes

| Error | Cause | Fix |
| ----- | ----- | --- |
| `Firebase connected successfully` not showing | Wrong Firebase credentials | Check your `.env` file |
| `Cannot find module` | Dependencies not installed | Run `npm install` |
| `401 Unauthorized` | Missing or expired token | Login again to get a new token |
| `403 Forbidden` | Wrong role for the endpoint | Use the correct user role |
| `FIREBASE_PRIVATE_KEY` error | Key format issue | Make sure the key is in double quotes with `\n` characters |
| Port already in use | Another app using port 5000 | Change PORT in `.env` or stop the other app |

---

## Borrow/Return Logic

### Borrowing a Book:
1. Student sends a borrow request with the book ID
2. System checks if the book exists and has quantity > 0
3. System checks if the student already borrowed this book
4. Book quantity is decreased by 1
5. If quantity becomes 0, book status changes to "borrowed"
6. A transaction is created with status "active" and a 14-day due date

### Returning a Book:
1. Student sends a return request with the book ID
2. System finds the active transaction for this student and book
3. Transaction status is changed to "returned" with the return date
4. Book quantity is increased by 1
5. Book status changes back to "available"

---

## Author

**Pratik Swain**
