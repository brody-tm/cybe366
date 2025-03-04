#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define REAL_PASSWORD "096fd892a63da24334e8256d45dec6979b6cec670c7ec8193666124fc369b4a4"

char* caeser_cipher(char* text, int shift);
char* caeser_decipher(char* text, int shift);
void hash_password(const char *password, char *hashed_str);

int main() {
    char input_password[100];
    char hashed_input[SHA256_DIGEST_LENGTH * 2 + 1];

    // Prompt user for password
    printf("Enter password: ");
    scanf(" %[^\n]", input_password);

    // Hash the input password
    hash_password(input_password, hashed_input);

    // Compare hashed input with stored hash
    if (strcmp(hashed_input, REAL_PASSWORD) != 0) {
        printf("Access Denied\n");
        return 1;
    }

    printf("Access Granted\n");

    int key_size;

    printf("Enter key size: ");
    scanf("%d", &key_size);

    if (key_size < 1 || key_size > 94) {
        printf("Invalid key size\n");
        return 1;
    }
    {
        /* code */
    }
    
    int option;
    
    printf("1. Encrypt\n2. Decrypt\n> ");
    scanf("%d", &option);

    if (option == 1) {
        // Encrypt
        int input_or_file;
        printf("1. Enter input manually\n2. Read from file\n> ");
        scanf("%d", &input_or_file);

        if (input_or_file == 1) {
            // Input
            char text[100];
            printf("Enter text: ");
            scanf(" %[^\n]", text);
            printf("Encrypted text: %s\n", caeser_cipher(text, key_size));
        } else if (input_or_file == 2) {
            // File
            char file_name[100];
            printf("Enter file name: ");
            scanf(" %[^\n]", file_name);

            FILE* file = fopen(file_name, "r");
            if (file == NULL) {
                printf("File not found\n");
                return 1;
            }

            char text[100];
            fscanf(file, " %[^\n]", text);
            printf("Encrypted text: %s\n", caeser_cipher(text, key_size));
        } else {
            printf("Invalid option\n");
            return 1;
        }
    } else if (option == 2) {
        // Decrypt
        int input_or_file;
        printf("1. Enter input manually\n2. Read from file\n> ");
        scanf("%d", &input_or_file);

        if (input_or_file == 1) {
            // Input
            char text[100];
            printf("Enter text: ");
            scanf(" %[^\n]", text);
            printf("Decrypted text: %s\n", caeser_decipher(text, key_size));
        } else if (input_or_file == 2) {
            // File
            char file_name[100];
            printf("Enter file name: ");
            scanf(" %[^\n]", file_name);

            FILE* file = fopen(file_name, "r");
            if (file == NULL) {
                printf("File not found\n");
                return 1;
            }

            char text[100];
            fscanf(file, " %[^\n]", text);
            printf("Decrypted text: %s\n", caeser_decipher(text, key_size));
        } else {
            printf("Invalid option\n");
            return 1;
        }
    } else
    {
        printf("Invalid option\n");
        return 1;
    }

    return 0;
}

char* caeser_cipher(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= ' ' && text[i] <= '~') {
            text[i] = (text[i] - ' ' + shift) % 95 + ' ';
        }
    }
    return text;
}

char* caeser_decipher(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= ' ' && text[i] <= '~') {
            text[i] = (text[i] - ' ' - shift + 95) % 95 + ' ';
        }
    }
    return text;
}

void hash_password(const char *password, char *hashed_str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Compute SHA-256 hash
    SHA256((unsigned char *)password, strlen(password), hash);

    // Convert binary hash to hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_str[i * 2], "%02x", hash[i]);
    }

    hashed_str[SHA256_DIGEST_LENGTH * 2] = '\0';  // Null-terminate the string
}