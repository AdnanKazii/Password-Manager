#Password Manager 

This is a simple console-based password management system written in C. It allows users to securely store, display, and delete credentials using a master password. The passwords are stored in an encrypted format to protect sensitive information.

#Prerequisites
- C Compiler (GCC or any standard C compiler)
- Basic understanding of terminal/command-line operations

#Compilation:
To compile the program, use a C compiler. For example, using GCC:
	gcc -o password_manager password_manager.c

#Usage:
1. Run the compiled program 
	./password_manager
2. Enter your master password to access the manager. The same master password is used for encryption and decryption of the stored passwords.
3. There are four options that you are greeted with: 
	1. Add a new credential: Enter details such as name, email, and password.
	2. Display current credentials: Displays stored credentials with decrypted passwords.
	3. Delete a credential: Remove a credential by entering its name.
	4. Exit: Exit the program.
