#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

void monitor_room(const char *username, const char *channel, const char *room) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "DiscorIT/%s/%s/chat.csv", channel, room);
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Could not open chat file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main(int argc, char const *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <username> -channel <channel_name> -room <room_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[2], "-channel") == 0 && strcmp(argv[4], "-room") == 0) {
        monitor_room(argv[1], argv[3], argv[5]);
    } else {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }

    return 0;
}
