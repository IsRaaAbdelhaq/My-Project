//








#include <iostream>
#include <limits>
#include <cctype>
#include <string>

using namespace std;


int charToAscii (char ch)
{
    return toupper (ch) ;
}

char asciiToChar (int code)
{
    return (code % 26) + 'A' ;
}

bool isalphabetic (string str)
{
    return ( str.begin(),str.end(),[] (char ch) {return isalpha (ch); });
}

string generatedkey (string message , string key){
    int message_length = message.length();
    int key_length = key.length();
    string repeated_key = "";
    for (int i = 0; i < message_length; i++){
        repeated_key += key[i % key_length];
    }
    return repeated_key;
}

string get_input (const string&prompt , int maxlength)
{
    string input;

    while (true)
    {
        cout << prompt ;
        getline (cin,input);
        if (input.length () > maxlength)
        {
            cout << "ERROR : input execced max length of " << maxlength << "characters" << endl;
            continue;
        }

        else if (!isalpha(input[0]))
        {
            cout << "ERROR : Input must contain alphabetic characters. " << endl;
            continue;
        }
        else if (!(input.begin(), input.end(), [](char ch) { return isalpha(ch); })) {
            cout << "ERROR: Input must contain only alphabetic characters." << endl;
            continue;
        }
        else if (input.empty()) {  // Check for empty input
            cout << "ERROR: Input cannot be empty." << endl;
            continue;
        }
        else
        {
            break;
        }

    }
    return input;
    
}


string encrypted (string message , string key)
{
    string repeated_key = generatedkey  (message , key);
    string encrypted_message = "";
    for (int i=0; i < message.length(); i++)
    {
        if (isalpha (message[i]))
        {
            int message_code = charToAscii(message[i]);
            int key_code = charToAscii(repeated_key[i]);
            int encrypted_code = (message_code + key_code) % 26 ;
            encrypted_message += asciiToChar(encrypted_code);
        }
        else 
        {
            encrypted_message += message[i];

        }
    }
    return encrypted_message;
}

string decrypted (string cipher , string key)
{
    string repeated_key = generatedkey  (cipher , key);
    string decrypted_message = "";
    for (int i = 0; i < cipher.length(); i++)
    {
        if (isalpha (cipher[i]))
        {
            int cipher_code = charToAscii(cipher[i]);
            int key_code = charToAscii(repeated_key[i]);
            int decrypted_code = (cipher_code - key_code + 26) % 26 ;
            decrypted_message += asciiToChar(decrypted_code);
        }
        else 
        {
            decrypted_message += cipher[i];

        }
    }
    return decrypted_message;
    
}

int main ()
{
    cout << "                                              WELCOME DEAR                                    ";
    string message , key , choice ;
    message = get_input("\nEnter your message (max 80 characters): " , 80);
    key = get_input("Enter the key (max 8 characters, alphabetic only): " , 8);
    cout <<"Enter 'E' for encryption or 'D' for decryption: ";
    getline (cin,choice);

    if (choice == "E"){
        string encrypted_message = encrypted(message,key);
        cout << "Encrypted Message: " << encrypted_message << endl;
    }
    else if (choice == "D")
    {
        string decrypted_message = decrypted(message,key);
        cout << "Decrypted Message: " << decrypted_message << endl;
    }
    else 
    {
        cout << "invalid choice" << endl;
    }
    
    return 0;
}

