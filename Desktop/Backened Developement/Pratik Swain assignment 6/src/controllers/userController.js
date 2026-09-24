const { getAllUsers, getUserById, updateUser, deleteUser } = require("../models/userModel");

async function getAll(req, res, next) {
  try {
    const users = await getAllUsers();

    const usersWithoutPasswords = users.map((user) => {
      return {
        userId: user.userId,
        name: user.name,
        email: user.email,
        role: user.role,
        createdAt: user.createdAt,
        updatedAt: user.updatedAt,
      };
    });

    res.status(200).json({
      message: "Users fetched successfully",
      count: usersWithoutPasswords.length,
      users: usersWithoutPasswords,
    });
  } catch (error) {
    next(error);
  }
}

async function getById(req, res, next) {
  try {
    const user = await getUserById(req.params.id);

    if (!user) {
      return res.status(404).json({ message: "User not found" });
    }

    res.status(200).json({
      user: {
        userId: user.userId,
        name: user.name,
        email: user.email,
        role: user.role,
        createdAt: user.createdAt,
        updatedAt: user.updatedAt,
      },
    });
  } catch (error) {
    next(error);
  }
}

async function updateRole(req, res, next) {
  try {
    const userId = req.params.id;
    const { role } = req.body;

    const user = await getUserById(userId);
    if (!user) {
      return res.status(404).json({ message: "User not found" });
    }

    const updatedUser = await updateUser(userId, { role: role });

    res.status(200).json({
      message: "User role updated successfully",
      user: {
        userId: updatedUser.userId,
        name: updatedUser.name,
        email: updatedUser.email,
        role: updatedUser.role,
      },
    });
  } catch (error) {
    next(error);
  }
}

async function removeUser(req, res, next) {
  try {
    const userId = req.params.id;

    const deleted = await deleteUser(userId);

    if (!deleted) {
      return res.status(404).json({ message: "User not found" });
    }

    res.status(200).json({ message: "User deleted successfully" });
  } catch (error) {
    next(error);
  }
}

module.exports = { getAll, getById, updateRole, removeUser };
