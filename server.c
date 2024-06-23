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

#define PORT 8080

typedef struct User {
    char username[50];
    char password[100];
    char role[10];
} User;

typedef struct Channel {
    char name[50];
    struct Channel *next;
} Channel;

typedef struct Room {
    char name[50];
    struct Room *next;
} Room;

Channel *channels = NULL;

void handle_client(int new_socket);
void register_user(int new_socket, const char *username, const char *hashed_password);
int user_exists(const char *username);
int user_password_matches(const char *username, const char *hashed_password);
void list_channels(int new_socket);
void list_rooms(int new_socket, const char *channel_name);
void list_users(int new_socket, const char *channel_name);
void join_channel(int new_socket, const char *username, const char *channel_name);
void join_room(int new_socket, const char *channel_name, const char *room_name);

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
    char *username = strtok(NULL, " ");
    char *hashed_password = strtok(NULL, " ");

    if (strcmp(command, "REGISTER") == 0) {
        register_user(new_socket, username, hashed_password);
    } else if (strcmp(command, "LOGIN") == 0) {
        if (user_password_matches(username, hashed_password)) {
            char response[256];
            snprintf(response, sizeof(response), "%s berhasil login\n", username);
            send(new_socket, response, strlen(response), 0);
        } else {
            send(new_socket, "Invalid username or password\n", strlen("Invalid username or password\n"), 0);
        }
    } else if (strcmp(command, "LIST CHANNEL") == 0) {
        list_channels(new_socket);
    } else if (strcmp(command, "LIST ROOM") == 0) {
        char *channel_name = strtok(NULL, " ");
        list_rooms(new_socket, channel_name);
    } else if (strcmp(command, "LIST USER") == 0) {
        char *channel_name = strtok(NULL, " ");
        list_users(new_socket, channel_name);
    } else if (strcmp(command, "JOIN CHANNEL") == 0) {
        char *channel_name = strtok(NULL, " ");
        join_channel(new_socket, username, channel_name);
    } else if (strcmp(command, "JOIN ROOM") == 0) {
        char *channel_name = strtok(NULL, " ");
        char *room_name = strtok(NULL, " ");
        join_room(new_socket, channel_name, room_name);
    }

    printf("Client disconnected\n");
    close(new_socket);
}

void register_user(int new_socket, const char *username, const char *hashed_password) {
    if (user_exists(username)) {
        char response[256];
        snprintf(response, sizeof(response), "%s sudah terdaftar\n", username);
        send(new_socket, response, strlen(response), 0);
        return;
    }

    // Open the file in append mode
    FILE *file = fopen("DiscorIT/users.csv", "a");
    if (file == NULL) {
        perror("Could not open users.csv");
        return;
    }

    // Write the username and hashed password to the file
    fprintf(file, "%s,%s,USER\n", username, hashed_password);

    // Close the file
    fclose(file);
    char response[256];
    snprintf(response, sizeof(response), "%s berhasil register\n", username);
    send(new_socket, response, strlen(response), 0);
    printf("User %s registered with password hash %s\n", username, hashed_password);
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

void list_channels(int new_socket) {
    Channel *current = channels;
    char response[1024] = {0};

    while (current != NULL) {
        strcat(response, current->name);
        strcat(response, " ");
        current = current->next;
    }

    send(new_socket, response, strlen(response), 0);
}

void list_rooms(int new_socket, const char *channel_name) {
    Channel *current = channels;
    char response[1024] = {0};

    while (current != NULL) {
        if (strcmp(current->name, channel_name) == 0) {
            Room *room = current->rooms;
            while (room != NULL) {
                strcat(response, room->name);
                strcat(response, " ");
                room = room->next;
            }
            break;
        }
        current = current->next;
    }

    send(new_socket, response, strlen(response), 0);
}

void list_users(int new_socket, const char *channel_name) {
    Channel *current = channels;
    char response[1024] = {0};

    while (current != NULL) {
        if (strcmp(current->name, channel_name) == 0) {
            User *user = current->users;
            while (user != NULL) {
                strcat(response, user->username);
                strcat(response, " ");
                user = user->next;
            }
            break;
        }
        current = current->next;
    }

    send(new_socket, response, strlen(response), 0);
}

void join_channel(int new_socket, const char *username, const char *channel_name) {
    Channel *current = channels;
    while (current != NULL) {
        if (strcmp(current->name, channel_name) == 0) {
            // Add user to channel
            User *user = malloc(sizeof(User));
            strcpy(user->username, username);
            user->next = current->users;
            current->users = user;

            char response[256];
            snprintf(response, sizeof(response), "%s joined channel %s\n", username, channel_name);
            send(new_socket, response, strlen(response), 0);
            return;
        }
        current = current->next;
    }

    // Channel not found, create a new one
    Channel *new_channel = malloc(sizeof(Channel));
    strcpy(new_channel->name, channel_name);
    new_channel->next = channels;
    new_channel->rooms = NULL;
    new_channel->users = NULL;
    channels = new_channel;

    // Add user to new channel
    User *user = malloc(sizeof(User));
    strcpy(user->username, username);
    user->next = new_channel->users;
    new_channel->users = user;

    char response[256];
    snprintf(response, sizeof(response), "%s joined channel %s\n", username, channel_name);
    send(new_socket, response, strlen(response), 0);
}

void join_room(int new_socket, const char *channel_name, const char *room_name) {
    Channel *current = channels;
    while (current != NULL) {
        if (strcmp(current->name, channel_name) == 0) {
            Room *room = current->rooms;
            while (room != NULL) {
                if (strcmp(room->name, room_name) == 0) {
                    char response[256];
                    snprintf(response, sizeof(response), "Joined room %s\n", room_name);
                    send(new_socket, response, strlen(response), 0);
                    return;
                }
                room = room->next;
            }

            // Room not found, create a new one
            Room *new_room = malloc(sizeof(Room));
            strcpy(new_room->name, room_name);
            new_room->next = current->rooms;
            current->rooms = new_room;

            char response[256];
            snprintf(response, sizeof(response), "Joined room %s\n", room_name);
            send(new_socket, response, strlen(response), 0);
            return;
        }
        current = current->next;
    }

    send(new_socket, "Channel not found\n", strlen("Channel not found\n"), 0);
}
