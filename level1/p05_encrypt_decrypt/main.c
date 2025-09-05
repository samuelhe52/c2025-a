#include <printf.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* encrypt(const char* plain_text, const char* pass_phrase) {
    unsigned char salt[16];
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Unable to open random device");
        return NULL;
    }
    fread(salt, 1, sizeof(salt), fp);
    fclose(fp);

    const size_t pass_len = strlen(pass_phrase);
    const size_t combined_size = sizeof(salt) + pass_len;
    unsigned char *combined = (unsigned char *)malloc(combined_size);
    if (combined == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    memcpy(combined, salt, sizeof(salt));
    memcpy(combined + sizeof(salt), pass_phrase, pass_len);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(combined, combined_size, hash);
    free(combined);

    const size_t text_len = strlen(plain_text);
    char* cipher_text = malloc(text_len + sizeof(salt) + 1);
    if (cipher_text == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    memcpy(cipher_text, salt, sizeof(salt));

    for (size_t i = 0; i < text_len; i++) {
        // XOR encryption
        cipher_text[sizeof(salt) + i] = plain_text[i] ^ hash[i % SHA256_DIGEST_LENGTH];
    }
    cipher_text[sizeof(salt) + text_len] = '\0';
    return cipher_text;
}

char* decrypt(const char* cipher_text, const char * pass_phrase) {
    unsigned char salt[16];
    memcpy(salt, cipher_text, sizeof(salt));

    const size_t cipher_text_len = strlen(cipher_text);
    const size_t pass_len = strlen(pass_phrase);
    const size_t combined_size = sizeof(salt) + pass_len;

    unsigned char *combined = malloc(combined_size);
    if (combined == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    memcpy(combined, salt, sizeof(salt));
    memcpy(combined + sizeof(salt), pass_phrase, pass_len);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(combined, combined_size, hash);
    free(combined);

    char *plain_text = malloc(cipher_text_len - sizeof(salt));
    for (size_t i = 0; i < cipher_text_len - sizeof(salt); i++) {
        plain_text[i] = cipher_text[i + sizeof(salt)] ^ hash[i % SHA256_DIGEST_LENGTH];
    }

    plain_text[cipher_text_len - sizeof(salt)] = '\0';
    return plain_text;
}

int main() {
    const char* plain_text = "This is a random plain text for testing";
    const char* pass_phrase = "147258369";
    const char* cipher_text = encrypt(plain_text, pass_phrase);
    printf("Plain Text: %s\n", plain_text);
    printf("Cipher Text: %s\n", cipher_text);
    char* decrypted = decrypt(cipher_text, pass_phrase);
    printf("Decrypted Text: %s\n", decrypted);
    return 0;
}