#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_NAME_LENGTH 50

void handle_commands(int sock, const char *username) {
    char buffer[BUF_SIZE] = {0};
    char channel[MAX_NAME_LENGTH] = {0};
    char room[MAX_NAME_LENGTH] = {0};
    int key_prompt = 0;
    int in_channel = 0;
    int in_room = 0;

    while (1) {
        if (key_prompt) {
            printf("Key: ");
            fflush(stdout);
            key_prompt = 0;
        } else if (in_channel && in_room) {
            printf("[%s/%s/%s] ", username, channel, room);
        } else if (in_channel) {
            printf("[%s/%s] ", username, channel);
        } else {
            printf("[%s] ", username);
        }

        if (fgets(buffer, BUF_SIZE, stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "EXIT") == 0) {
            send(sock, buffer, strlen(buffer), 0);
            if (in_room) {
                in_room = 0;
                memset(room, 0, sizeof(room));
            } else if (in_channel) {
                in_channel = 0;
                memset(channel, 0, sizeof(channel));
            } else {
                break;
            }
        } else {
            char command[BUF_SIZE] = {0};
            char name[MAX_NAME_LENGTH] = {0};

            if (sscanf(buffer, "%s %s", command, name) == 2 && strcmp(command, "JOIN") == 0) {
                if (in_channel && !in_room) {
                    snprintf(room, sizeof(room), "%s", name);
                    in_room = 1;
                } else if (!in_channel) {
                    snprintf(channel, sizeof(channel), "%s", name);
                    in_channel = 1;
                }
            }

            if (send(sock, buffer, strlen(buffer), 0) == -1) {
                perror("Send failed");
                break;
            }
        }

        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(sock, buffer, BUF_SIZE - 1);
        if (bytes_read <= 0) {
            perror("Read failed");
            break;
        }
        buffer[bytes_read] = '\0';

        if (strstr(buffer, "masuk channel")) {
            char *channel_name = strstr(buffer, "bergabung dengan channel ") + strlen("bergabung dengan channel ");
            strncpy(channel, channel_name, sizeof(channel) - 1);
            channel[sizeof(channel) - 1] = '\0';
            in_channel = 1;
        } else if (strstr(buffer, "masuk room")) {
            char *room_name = strstr(buffer, "bergabung dengan room ") + strlen("bergabung dengan room ");
            strncpy(room, room_name, sizeof(room) - 1);
            room[sizeof(room) - 1] = '\0';
            in_room = 1;
        } else if (strstr(buffer, "Key:")) {
            key_prompt = 1;
        }

        printf("%s\n", buffer);
    }
}

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if (argc < 5) {
        printf("Usage: ./discorit REGISTER/LOGIN username -p password\n");
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    if (strcmp(argv[1], "REGISTER") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "REGISTER %s -p %s", argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "LOGIN %s -p %s", argv[2], argv[4]);
    } else {
        printf("Invalid command\n");
        close(sock);
        return 1;
    }

    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    int bytes_read = read(sock, buffer, BUF_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
        if (strstr(buffer, "Login successful") != NULL || strstr(buffer, "Registered successfully") != NULL) {
            handle_commands(sock, argv[2]);
        }
    }

    close(sock);
    return 0;
}
