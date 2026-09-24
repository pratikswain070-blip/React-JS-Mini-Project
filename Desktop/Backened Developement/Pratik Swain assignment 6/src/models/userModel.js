const { db } = require("../config/firebase");

const usersCollection = db.collection("users");

async function createUser(userData) {
  const userRef = usersCollection.doc();
  const userId = userRef.id;

  const newUser = {
    userId: userId,
    name: userData.name,
    email: userData.email,
    password: userData.password,
    role: userData.role,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString(),
  };

  await userRef.set(newUser);
  return newUser;
}

async function getUserByEmail(email) {
  const snapshot = await usersCollection.where("email", "==", email).get();

  if (snapshot.empty) {
    return null;
  }

  return snapshot.docs[0].data();
}

async function getUserById(userId) {
  const snapshot = await usersCollection.where("userId", "==", userId).get();

  if (snapshot.empty) {
    return null;
  }

  return snapshot.docs[0].data();
}

async function getAllUsers() {
  const snapshot = await usersCollection.get();
  const users = [];

  snapshot.forEach((doc) => {
    users.push(doc.data());
  });

  return users;
}

async function updateUser(userId, updateData) {
  const snapshot = await usersCollection.where("userId", "==", userId).get();

  if (snapshot.empty) {
    return null;
  }

  const docRef = snapshot.docs[0].ref;
  updateData.updatedAt = new Date().toISOString();

  await docRef.update(updateData);

  const updatedDoc = await docRef.get();
  return updatedDoc.data();
}

async function deleteUser(userId) {
  const snapshot = await usersCollection.where("userId", "==", userId).get();

  if (snapshot.empty) {
    return false;
  }

  await snapshot.docs[0].ref.delete();
  return true;
}

module.exports = {
  createUser,
  getUserByEmail,
  getUserById,
  getAllUsers,
  updateUser,
  deleteUser,
};
