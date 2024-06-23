#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <crypt.h>
#include <errno.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"  // Pastikan ini mengarah ke IP yang benar

void register_user(const char *username, const char *password) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Buat socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // Konversi alamat IP dari text ke binary
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Hubungkan ke server
    printf("Connecting to server at %s:%d...\n", SERVER_IP, SERVER_PORT);
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // Enkripsi password
    char salt[] = "$6$rounds=5000$abcdefghijk$";  // Ganti salt sesuai kebutuhan
    char *hashed_password = crypt(password, salt);

    // Kirim request register ke server
    snprintf(buffer, sizeof(buffer), "REGISTER %s %s", username, hashed_password);
    send(sock, buffer, strlen(buffer), 0);
    printf("Sent: %s\n", buffer);

    // Terima response dari server
    int valread = read(sock, buffer, sizeof(buffer) - 1);
    buffer[valread] = '\0';
    printf("Received: %s\n", buffer);

    close(sock);
}

void login_user(const char *username, const char *password) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Buat socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // Konversi alamat IP dari text ke binary
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Hubungkan ke server
    printf("Connecting to server at %s:%d...\n", SERVER_IP, SERVER_PORT);
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // Enkripsi password
    char salt[] = "$6$rounds=5000$abcdefghijk$";  // Ganti salt sesuai kebutuhan
    char *hashed_password = crypt(password, salt);

    // Kirim request login ke server
    snprintf(buffer, sizeof(buffer), "LOGIN %s %s", username, hashed_password);
    send(sock, buffer, strlen(buffer), 0);
    printf("Sent: %s\n", buffer);

    // Terima response dari server
    int valread = read(sock, buffer, sizeof(buffer) - 1);
    buffer[valread] = '\0';
    printf("Received: %s\n", buffer);

    close(sock);
}

//FUNGSI JOIN BELUM AKU COBA
//FUNGSI JOIN BELUM AKU COBA
void send_join_command(int sockfd, char *username, char *channel, char *key) {
    char command[MAX_COMMAND_SIZE];
    if (key == NULL) {
        snprintf(command, sizeof(command), "JOIN %s", channel);
    } else {
        snprintf(command, sizeof(command), "JOIN %s %s", channel, key);
    }

    send_message(sockfd, username, command);
}

// Fungsi untuk menangani perintah JOIN dari pengguna
void handle_join_command(int sockfd, char *username) {
    char channel[MAX_CHANNEL_NAME_SIZE];
    char key[MAX_KEY_SIZE];

    printf("[%s] JOIN channel\n", username);
    printf("Channel: ");
    scanf("%s", channel);

    // Cek apakah channel memiliki key atau tidak
    printf("Key (leave blank if none): ");
    scanf("%s", key);
    if (strlen(key) == 0) {
        key = NULL;
    }

    send_join_command(sockfd, username, channel, key);
}

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <REGISTER|LOGIN> <username> -p <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "REGISTER") == 0 && strcmp(argv[3], "-p") == 0) {
        register_user(argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && strcmp(argv[3], "-p") == 0) {
        login_user(argv[2], argv[4]);
    } else {
        fprintf(stderr, "Invalid command\n");
        return EXIT_FAILURE;
    }

    return 0;
}
