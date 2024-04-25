#include "Validator.h"
#include "User.h"
Validator::Validator()
{
}

bool Validator::UsedUserName(string username)
{
	vector<User> users = User::RetrieveUsersFromDatabase();

	for (const auto& existingUser : users)
	{
		if (existingUser.userName == username)
		{
			return true;
		}
	}
	return false;
}
bool Validator::ExistingPassword(string password, string username)
{
	vector<User> users = User::RetrieveUsersFromDatabase();
	for (const auto& existingUser : users)
	{
		if (existingUser.password == password && username == existingUser.userName)
		{
			return true;
		}
	}
	return false;

}

bool Validator::isStrongPassword(string password)
{
	bool hasSpecialLetter = false;
	bool hasUpperLetter = false;
	bool haslowerLetter = false;
	bool hasnumber = false;
	bool strong = false;

	if (password.size() < 8)
		return strong;

	for (char letter : password)
	{
		if (isupper(letter))
			hasUpperLetter = true;
		else if (islower(letter))
			haslowerLetter = true;
		else if (isdigit(letter))
			hasnumber = true;
		else if (ispunct(letter))
			hasSpecialLetter = true;

		if (hasUpperLetter && haslowerLetter && hasnumber && hasSpecialLetter)
		{
			strong = true;
			break;
		}
	}

	return strong;
}

bool Validator::isTheCorrectPassword(User user,string password)
{
	bool correct = false;
	if (password == user.password)
		correct = true;

	return correct;
}

/*The isValidEmail function takes a string email as input and uses a regular expression pattern to check if the email format is valid.
The regular expression pattern ([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}) is used for basic email validation.
It checks for one or more alphanumeric characters, dots, underscores, percentage signs, plus signs, 
and hyphens before the "@" symbol, followed by an "@" symbol, domain name (alphanumeric characters, dots, and hyphens),
and a top-level domain (at least 2 characters long).
The std::regex_match function is used to match the input email string against the regular expression pattern.
In the main function, the user is prompted to enter an email address, and the program checks if it's a valid 
email address using the isValidEmail function and prints the appropriate message.
*/
bool Validator::isValidEmailAddress(string& email)
{
	const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return regex_match(email, pattern);

}

