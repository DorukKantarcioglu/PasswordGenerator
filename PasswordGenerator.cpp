/**
 * @file PasswordGenerator.cpp
 * @author DorukKantarcioglu
 * @brief This program generates a random password with the specified length in the program argument, then copies the password to the clipboard.
 * @date 30.05.2021
 */

#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

const char charArr[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  /// Allowed characters in passwords
const int charCount = sizeof(charArr) - 1;  /// 94 characters

int main(int argc, char** argv)
{
    int passwordLength = atoi(argv[1]); /// Get the length of the password from the program argument
    char* password = new char[passwordLength];
    cout << "Password length to be generated: " << passwordLength << endl;
    cout << "Generated password: ";
    srand((unsigned int)time(NULL));    /// Use computer clock as the seed for accuracy
    for (int i = 0; i < passwordLength; i++) {
        password[i] = charArr[rand() % charCount];
        cout << password[i];
    }
    cout << endl;
    /// Empty the contents of the clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, passwordLength + 1);    /// Allocate sufficient bytes for the password
    if (handle) {
       	memcpy(GlobalLock(handle), password, passwordLength + 1);
        GlobalUnlock(handle);
        SetClipboardData(CF_TEXT, handle);  /// Copy the password to the clipboard
        GlobalFree(handle); /// Free the allocated memory
    }
    CloseClipboard();
    cout << "Password copied to clipboard." << endl;
    delete[] password;

    return 0;
}
