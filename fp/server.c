#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <crypt.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <dirent.h>

#define PORT 8080

// Function declarations
void handle_client(int new_socket);
void register_user(int new_socket, const char *username, const char *hashed_password);
int user_exists(const char *username);
int user_password_matches(const char *username, const char *hashed_password);
void list_channels(int new_socket);
void list_rooms(int new_socket, const char *channel_name);
void list_users(int new_socket, const char *channel_name);
void join_channel(int new_socket, const char *username, const char *channel_name, const char *key);
void join_room(int new_socket, const char *username, const char *channel_name, const char *room_name);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
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

        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, (void *)handle_client, (void *)(intptr_t)new_socket) != 0) {
            perror("Failed to create thread");
        }
    }

    return 0;
}

void handle_client(int new_socket) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    buffer[valread] = '\0';
    printf("Received: %s\n", buffer);

    char *command = strtok(buffer, " ");
    char *arg1 = strtok(NULL, " ");
    char *arg2 = strtok(NULL, " ");
    char *arg3 = strtok(NULL, " ");

    if (strcmp(command, "REGISTER") == 0) {
        register_user(new_socket, arg1, arg2);
    } else if (strcmp(command, "LOGIN") == 0) {
        if (user_password_matches(arg1, arg2)) {
            char response[256];
            snprintf(response, sizeof(response), "%s berhasil login\n", arg1);
            send(new_socket, response, strlen(response), 0);
        } else {
            send(new_socket, "Invalid username or password\n", strlen("Invalid username or password\n"), 0);
        }
    } else if (strcmp(command, "LIST") == 0) {
        if (strcmp(arg1, "CHANNEL") == 0) {
            list_channels(new_socket);
        } else if (strcmp(arg1, "ROOM") == 0) {
            list_rooms(new_socket, arg2);
        } else if (strcmp(arg1, "USER") == 0) {
            list_users(new_socket, arg2);
        }
    } else if (strcmp(command, "JOIN") == 0) {
        if (arg1 && arg2 && !arg3) {
            join_channel(new_socket, "default_user", arg2, arg1); // Assuming a logged-in user named "default_user"
        } else if (arg1 && arg2 && arg3) {
            join_room(new_socket, "default_user", arg1, arg3); // Assuming a logged-in user named "default_user"
        }
    }

    printf("Client disconnected\n");
    close(new_socket);
}

void list_channels(int new_socket) {
    DIR *d;
    struct dirent *dir;
    char response[1024] = {0};
    d = opendir("DiscorIT");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                strcat(response, dir->d_name);
                strcat(response, " ");
            }
        }
        closedir(d);
    } else {
        perror("Could not open DiscorIT directory");
        send(new_socket, "Failed to list channels\n", strlen("Failed to list channels\n"), 0);
        return;
    }

    strcat(response, "\n");
    send(new_socket, response, strlen(response), 0);
}

void list_rooms(int new_socket, const char *channel_name) {
    char path[1024];
    snprintf(path, sizeof(path), "DiscorIT/%s", channel_name);
    DIR *d = opendir(path);
    struct dirent *dir;
    char response[1024] = {0};

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                strcat(response, dir->d_name);
                strcat(response, " ");
            }
        }
        closedir(d);
    } else {
        snprintf(response, sizeof(response), "Channel %s not found\n", channel_name);
        send(new_socket, response, strlen(response), 0);
        return;
    }

    strcat(response, "\n");
    send(new_socket, response, strlen(response), 0);
}

void list_users(int new_socket, const char *channel_name) {
    char response[1024] = "Available users:\n";
    // Implement the logic to list users
    // ...
    send(new_socket, response, strlen(response), 0);
}

void join_channel(int new_socket, const char *username, const char *channel_name, const char *key) {
    char response[256];

    // Implement logic to verify if the user already has access to the channel
    // If the key is correct, increase access level
    // ...

    snprintf(response, sizeof(response), "%s joined channel %s\n", username, channel_name);
    send(new_socket, response, strlen(response), 0);
}

void join_room(int new_socket, const char *username, const char *channel_name, const char *room_name) {
    char response[256];
    snprintf(response, sizeof(response), "%s joined room %s\n", username, room_name);
    send(new_socket, response, strlen(response), 0);
}

void register_user(int new_socket, const char *username, const char *hashed_password) {
    if (user_exists(username)) {
        char response[256];
        snprintf(response, sizeof(response), "%s sudah terdaftar\n", username);
        send(new_socket, response, strlen(response), 0);
        return;
    }

    FILE *file = fopen("DiscorIT/users.csv", "a");
    if (file == NULL) {
        perror("Could not open users.csv");
        return;
    }

    fprintf(file, "%s,%s,USER\n", username, hashed_password);
    fclose(file);

    char response[256];
    snprintf(response, sizeof(response), "%s berhasil register\n", username);
    send(new_socket, response, strlen(response), 0);
}

int user_exists(const char *username) {
    FILE *file = fopen("DiscorIT/users.csv", "r");
    if (file == NULL) {
        perror("Could not open users.csv");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *file_username = strtok(line, ",");
        if (file_username != NULL) {
            if (strcmp(file_username, username) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int user_password_matches(const char *username, const char *hashed_password) {
    FILE *file = fopen("DiscorIT/users.csv", "r");
    if (file == NULL) {
        perror("Could not open users.csv");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *file_username = strtok(line, ",");
        char *file_hashed_password = strtok(NULL, ",");
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
