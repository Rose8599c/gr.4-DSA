#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Agent {
    char name[50];
    struct Agent* left;
    struct Agent* right;
    int commission;
};

struct JvienFriendsNetwork {
    struct Agent* root;
};

// for Desabille
struct Agent* create_agent(const char* name) {
    struct Agent* new_agent = (struct Agent*)malloc(sizeof(struct Agent));
    strcpy(new_agent->name, name);
    new_agent->left = NULL;
    new_agent->right = NULL;
    new_agent->commission = 0;
    return new_agent;
}

// for Marlee
void add_agent(struct JvienFriendsNetwork* network, const char* name) {
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
    }
}

// for sheen
void display_tree(struct Agent* agent, int level) {
    if (agent == NULL) return;
    printf("%*s%s (Money: %d)\n", level * 4, "", agent->name, agent->commission);
    display_tree(agent->left, level + 1);
    display_tree(agent->right, level + 1);
}

// for cammile
void display_downlines(struct Agent* agent) {
    if (agent == NULL) return;
    if (agent->left) {
        printf("Agent: %s, Money: %d\n", agent->left->name, agent->left->commission);
        display_downlines(agent->left);
    }
    if (agent->right) {
        printf("Agent: %s, Money: %d\n", agent->right->name, agent->right->commission);
        display_downlines(agent->right);
    }
}

// for ezra
struct Agent* find_agent(struct Agent* agent, const char* name) {
    if (agent == NULL) return NULL;
    if (strcmp(agent->name, name) == 0) return agent;


    struct Agent* found_agent = find_agent(agent->left, name);
    if (found_agent) return found_agent;
    return find_agent(agent->right, name);
}

int main() {
    struct JvienFriendsNetwork network;
    network.root = NULL;
    int choice;
    char agent_name[50];

    do {
        printf("\n--- JvienFriends Network Management ---\n");
        printf("1. Add Agent\n");
        printf("2. Display Network Tree\n");
        printf("3. Display Downlines of an Agent\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Enter agent name: ");
                scanf("%s", agent_name);
                add_agent(&network, agent_name);
                break;
            case 2:
                printf("JvienFriends Network Tree:\n");
                display_tree(network.root, 0);
                break;
            case 3:
                printf("Enter agent name to display downlines: ");
                scanf("%s", agent_name);
                struct Agent* agent = find_agent(network.root, agent_name);
                if (agent) {
                    printf("\nDownlines for %s:\n ", agent_name);
                    display_downlines(agent);
                } else {
                    printf("Agent %s not found.\n", agent_name);
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}

