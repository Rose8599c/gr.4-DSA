#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

struct Agent {
    char name[50];
    struct Agent* left;
    struct Agent* right;
    int commission;
};

struct JVieNFriends {
    struct Agent* root;
};

struct Agent* create_agent(const char* name) {
    struct Agent* new_agent = (struct Agent*)malloc(sizeof(struct Agent));
    strcpy(new_agent->name, name);
    new_agent->left = NULL;
    new_agent->right = NULL;
    new_agent->commission = 0;
    return new_agent;
}

void add_agent(struct JVieNFriends* network, const char* name) {
    struct Agent* new_agent = create_agent(name);
    if (network->root == NULL) {
        network->root = new_agent;
    } else {
        struct Agent* current = network->root;
        while (1) {
            if (current->left == NULL) {
                current->left = new_agent;
                current->commission += 500;
                break;
            } else if (current->right == NULL) {
                current->right = new_agent;
                current->commission += 500;
                break;
            } else {
                current = current->left ? current->left : current->right;
            }
        }

        int root_commission = (new_agent->commission * 5)/100;
        network->root->commission += root_commission;
    }
}

void display_tree(struct Agent* agent, int level) {
    if (agent == NULL) return;
    printf(BLUE"%*s%s (Money: %d)\n"RESET, level * 4, "", agent->name, agent->commission);
    display_tree(agent->left, level + 1);
    display_tree(agent->right, level + 1);
}

void display_downlines(struct Agent* agent) {
    if (agent == NULL) return;
    if (agent->left) {
        printf(GREEN "Agent: %s, Money: %d\n" RESET, agent->left->name, agent->left->commission);
        display_downlines(agent->left);
    }
    if (agent->right) {
        printf(GREEN "Agent: %s, Money: %d\n" RESET, agent->right->name, agent->right->commission);
        display_downlines(agent->right);
    }
}

struct Agent* find_agent(struct Agent* agent, const char* name) {
    if (agent == NULL) return NULL;
    if (strcmp(agent->name, name) == 0) return agent;

    struct Agent* found_agent = find_agent(agent->left, name);
    if (found_agent) return found_agent;
    return find_agent(agent->right, name);
}

int login() {
    const char* username = "BSIT";
    const char* password = "2B-NIGHT";
    char input_username[50];
    char input_password[50];

    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnter username: " );
    scanf("%s" , input_username);
    printf("\t\t\t\t\tEnter password: " );
    scanf( "%s", input_password);

    return (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0);
}

void display_menu() {
    printf(BLUE "\t\t\t\t\t+-------------------------------+\n" RESET);
    printf("\t\t\t\t\t|" YELLOW "JVieNFriends Network Management" RESET "|\n");
    printf(BLUE "\t\t\t\t\t+-------------------------------+\n" RESET);
    printf(GREEN"\t\t\t\t\t| 1. Add Agent                  |\n"RESET);
    printf(GREEN"\t\t\t\t\t| 2. Display Network Tree       |\n"RESET);
    printf(GREEN"\t\t\t\t\t| 3. Display Downlines of Agent |\n"RESET);
    printf(GREEN"\t\t\t\t\t| 4. Exit                       |\n"RESET);
    printf(BLUE "\t\t\t\t\t+-------------------------------+\n" RESET);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    struct JVieNFriends network;
    network.root = NULL;
    int choice;

    if (!login()) {
        printf("Invalid username or password. Exiting...\n");
        return 1;
    }

    do {
        clear_screen();
        display_menu();
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf ("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                char agent_name[50];
                printf("\t\t\t\t\tEnter agent name: ");
                scanf("%s", agent_name);
                add_agent(&network, agent_name);
                break;
            }
            case 2:
                printf(CYAN"\nJVieNFriends Tree:\n"RESET);
                printf("\n");
                display_tree(network.root, 0);
                break;
            case 3: {
                char agent_name[50];
                printf("\n\nEnter agent name to display downlines: ");
                scanf("%s", agent_name);
                struct Agent* agent = find_agent(network.root, agent_name);
                if (agent) {
                    printf(CYAN"\nDownlines for %s:\n" RESET, agent_name);
                    display_downlines(agent);
                    getchar();
                } else {
                    printf( "Agent %s not found.\n", agent_name);
                }
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf( "Invalid choice. Please try again.\n");
        }
        printf("\n\nPress Enter to continue...");
        getchar();
    } while (choice != 4);
    return 0;
}
