# Shopping Portal Project

## Overview

This project is developed as part of the CS-2001 Data Structures course (Fall 2023) and serves as a comprehensive e-commerce platform. It demonstrates the practical applications of various data structures and algorithms to optimize performance for product search, sorting, inventory management, and user sessions.

## Project Goals

- **Efficient Data Handling:** Utilize multiple data structures (e.g., Binary Search Trees, Hash Tables, Linked Lists, Graphs, etc.) for fast and efficient operations.
- **User-Friendly Interface:** Provide a seamless interface for both customers and sellers.
- **Robust Functionality:** Support essential e-commerce operations such as browsing products, managing shopping carts, processing payments, and securing user information.
- **Practical Demonstration:** Showcase real-world applications of data structure concepts.

## Features & Implemented Data Structures

- **Product Catalog:**

  - _Data Structure:_ Binary Search Tree (BST)
  - _Algorithm:_ Efficient BST search for quick product retrieval.

- **User Account Management:**

  - _Data Structure:_ Hash Table
  - _Algorithm:_ Fast lookup and secure authentication for user credentials.

- **Shopping Cart:**

  - _Data Structure:_ Linked List
  - _Algorithm:_ Dynamically add, remove, and update items in the cart.

- **Product Recommendations:**

  - _Data Structure:_ Graph and Max Heap (for ratings)
  - _Algorithm:_ Graph-based recommendations and max heap operations for displaying top-rated products.
  - _Code Reference:_ See the MaxHeap implementation citeturn0file1.

- **Inventory Management:**

  - _Data Structure:_ Array / Hash Map
  - _Algorithm:_ Track product quantities and update stock levels accordingly.

- **Sorting Products:**

  - _Data Structures & Algorithms:_ QuickSort or MergeSort for organizing products by various criteria (name, ID, price).

- **Search Functionality:**

  - _Data Structure:_ Trie
  - _Algorithm:_ Enable efficient keyword-based search across the product catalog.

- **Reviews & Ratings:**

  - _Data Structure:_ Binary Heap
  - _Algorithm:_ Manage and display user reviews and top-rated products efficiently.

- **Payment Processing:**

  - _Integration:_ External Payment Gateway (no internal data structure required).

- **Order History:**

  - _Data Structure:_ Doubly Linked List
  - _Algorithm:_ Maintain a history of user orders for easy navigation.

- **User Session Management:**
  - _Data Structures:_ Stack or Queue
  - _Algorithm:_ Track active user sessions and control access.

## Tools & Technologies

- **Programming Language:** C++
- **Development Environment:** Visual Studio
- **Framework:** .NET Framework 4.x (Windows Form Application)
- **Data Management:**
  - Inventory is maintained via `inventory.csv`
  - User credentials and session data are stored in `UserTable.dat` (secured through encryption)
  - See the encryption utility for details citeturn0file3.

## Project Structure

The repository is organized as follows:

```
│   README.md
│
├───bin
│       Shopping-Portal.exe       // Main application executable
│       userTableEncrypt.exe      // Utility for encrypting UserTable.dat
│
├───data
│       inventory.csv             // Product inventory data
│       UserTable.dat             // Encrypted user credentials
│
├───docs
│       ChangeLog.txt             // Record of changes made to the project
│
└───src
        Shopping-Portal.cpp       // Main application logic
```

## Installation & Usage

1. **Setup & Build:**

   - Open the solution in Visual Studio.
   - Build the project to compile the source files located in the `src` directory.

2. **Executable Files:**

   - Upon successful build, locate `Shopping-Portal.exe` and `userTableEncrypt.exe` in the `bin` folder.

3. **Data Files:**

   - Ensure that `inventory.csv` and `UserTable.dat` are correctly placed in the `data` directory (adjacent to the executable) for proper functionality.

4. **Running the Application:**

   - Launch `Shopping-Portal.exe` to start the portal.
   - Follow the on-screen prompts to log in as a customer or seller, browse products, manage the shopping cart, and access other features.

5. **Securing User Data:**
   - Use `userTableEncrypt.exe` to encrypt the `UserTable.dat` file after updating user data for added security.

## Detailed Code Overview

- **Main Portal Functionality:**  
  The `Shopping_Portal` class (implemented in `Shopping-Portal.cpp`) manages user logins, product searches, inventory management, shopping cart operations, and overall transaction processing.  
  _Refer to the detailed implementation in citeturn0file2._

- **Encryption Utility:**  
  The encryption and decryption routines in `userTableEncrypt.cpp` provide simple file-level security for the user data file (`UserTable.dat`).  
  _See encryption details citeturn0file3._

## Development Schedule

- **Submission Deadline:** The project is scheduled for submission one week before the final exam of the Fall 2023 semester.
- **Milestones & Deliverables:** Check the project timeline documented in the project requirements for details on milestones.

## Acknowledgements

This project has been developed by:

- Heo Juseong
- Asim Majeed
- Muhammad Muzammil

Special thanks to our course instructor, Basit Ali, for guidance and support throughout the project.
