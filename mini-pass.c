#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 50
#define MAX_FIELD   100

typedef struct {
    char site[MAX_FIELD];
    char username[MAX_FIELD];
    char password[MAX_FIELD];
} Entry;

Entry entries[MAX_ENTRIES];
int entry_count = 0;

const char *DATA_FILE = "pass.dat";

void load() {
    FILE *f = fopen(DATA_FILE, "r");
    if (!f) return;

    while (entry_count < MAX_ENTRIES &&
           fscanf(f, "%99[^|]|%99[^|]|%99[^\n]\n",
                  entries[entry_count].site,
                  entries[entry_count].username,
                  entries[entry_count].password) == 3) {
        entry_count++;
    }
    fclose(f);
}

void save() {
    FILE *f = fopen(DATA_FILE, "w");
    if (!f) {
        printf("Cannot save file!\n");
        return;
    }
    for (int i = 0; i < entry_count; i++) {
        fprintf(f, "%s|%s|%s\n",
                entries[i].site,
                entries[i].username,
                entries[i].password);
    }
    fclose(f);
}

void add(const char *site, const char *user, const char *pass) {
    if (entry_count >= MAX_ENTRIES) {
        printf("Full!\n");
        return;
    }
    strncpy(entries[entry_count].site, site, MAX_FIELD-1);
    strncpy(entries[entry_count].username, user, MAX_FIELD-1);
    strncpy(entries[entry_count].password, pass, MAX_FIELD-1);
    entry_count++;
    save();
    printf("Added → %s\n", site);
}

void list() {
    if (entry_count == 0) {
        printf("Empty.\n");
        return;
    }
    printf("\nAccounts:\n");
    for (int i = 0; i < entry_count; i++) {
        printf("%d. %s  (%s)\n", i+1, entries[i].site, entries[i].username);
    }
    printf("\n");
}

void get(const char *site) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].site, site) == 0) {
            printf("\nSite:     %s\n", entries[i].site);
            printf("Username: %s\n", entries[i].username);
            printf("Password: %s\n\n", entries[i].password);
            return;
        }
    }
    printf("  ./mini-pass delete <site>\n");
}

int main(int argc, char **argv) {
    load();

    if (argc < 2) {
        printf("Commands:\n");
        printf("  ./mini-pass add github user123 pass123\n");
        printf("  ./mini-pass get github\n");
        printf("  ./mini-pass list\n");
        return 1;
    }

    char *cmd = argv[1];

    if (strcmp(cmd, "add") == 0 && argc == 5) {
        add(argv[2], argv[3], argv[4]);
    }
    else if (strcmp(cmd, "get") == 0 && argc == 3) {
        get(argv[2]);
    }
    else if (strcmp(cmd, "list") == 0) {
        list();
    }
    else if (strcmp(cmd, "delete") == 0 && argc == 3) {
    int found = 0;
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].site, argv[2]) == 0) {
            // Shift remaining entries left
            for (int j = i; j < entry_count-1; j++) {
                entries[j] = entries[j+1];
            }
            entry_count--;
            save();
            printf("Deleted: %s\n", argv[2]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Not found: %s\n", argv[2]);
    }
}
    else {
        printf("Wrong command.\n");
    }

    return 0;
}