#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <crypt.h>
#include <errno.h>

#define PORT 8080               //FUNGSI REGISTER SAMA LOGIN SUDAH BISA
                                //FUNGSI JOIN BELUM ADA

void register_user(const char *username, const char *hashed_password) {
    // Open the file in append mode
    FILE *file = fopen("users.csv", "a");
    if (file == NULL) {
        perror("Could not open users.csv");
        return;
    }

    // Write the username and hashed password to the file
    fprintf(file, "%s,%s\n", username, hashed_password);
    printf("Debug: Writing to users.csv - %s,%s\n", username, hashed_password); // Debug statement

    // Close the file
    fclose(file);
    printf("User %s registered with password hash %s\n", username, hashed_password);
}

int user_exists(const char *username, const char *hashed_password) {
    FILE *file = fopen("users.csv", "r");
    if (file == NULL) {
        perror("Gagal membuka users.csv");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *file_username = strtok(line, ",");
        char *file_hashed_password = strtok(NULL, "\n");
        if (file_username != NULL && file_hashed_password != NULL) {
            if (strcmp(file_username, username) == 0 && strcmp(file_hashed_password, hashed_password) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Membuat socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Mengikat socket ke port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Bind successful\n");

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);

    while (1) {
        printf("Waiting for a client...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }
        printf("Client connected\n");

        int valread = read(new_socket, buffer, 1024);
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);

        char *command = strtok(buffer, " ");
        char *username = strtok(NULL, " ");
        char *hashed_password = strtok(NULL, " ");

        if (strcmp(command, "REGISTER") == 0) {
            register_user(username, hashed_password);
            send(new_socket, "User registered\n", strlen("User registered\n"), 0);
        } else if (strcmp(command, "LOGIN") == 0) {
            if (user_exists(username, hashed_password)) {
                send(new_socket, "Login successful\n", strlen("Login successful\n"), 0);
            } else {
                send(new_socket, "Invalid username or password\n", strlen("Invalid username or password\n"), 0);
            }
        }

        printf("Client disconnected\n");
        close(new_socket);
    }

    return 0;
}
