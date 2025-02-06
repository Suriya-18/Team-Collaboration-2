#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESPONSES 100
#define MAX_LENGTH 256

typedef struct {
    char question[MAX_LENGTH];
    char answer[MAX_LENGTH];
} ChatbotResponse;

ChatbotResponse responses[MAX_RESPONSES];
int response_count = 0;

void load_responses() {
    FILE *file = fopen("responses.txt", "r");
    if (!file) return;
    
    while (fscanf(file, " %[^"] " %[^"] ", responses[response_count].question, responses[response_count].answer) == 2) {
        response_count++;
        if (response_count >= MAX_RESPONSES) break;
    }
    fclose(file);
}

void save_responses() {
    FILE *file = fopen("responses.txt", "w");
    if (!file) return;
    
    for (int i = 0; i < response_count; i++) {
        fprintf(file, "%s\n%s\n", responses[i].question, responses[i].answer);
    }
    fclose(file);
}

char* get_response(char *input) {
    for (int i = 0; i < response_count; i++) {
        if (strcasecmp(responses[i].question, input) == 0) {
            return responses[i].answer;
        }
    }
    return NULL;
}

void add_response(char *question, char *answer) {
    if (response_count < MAX_RESPONSES) {
        strcpy(responses[response_count].question, question);
        strcpy(responses[response_count].answer, answer);
        response_count++;
        save_responses();
    }
}

int main() {
    char input[MAX_LENGTH], answer[MAX_LENGTH];
    
    printf("Welcome to Chatbot! Type 'exit' to quit.\n");
    load_responses();
    
    while (1) {
        printf("You: ");
        fgets(input, MAX_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline
        
        if (strcasecmp(input, "exit") == 0) break;
        
        char *response = get_response(input);
        if (response) {
            printf("Bot: %s\n", response);
        } else {
            printf("Bot: I don't know how to respond. Teach me! What should I say?\n");
            printf("You: ");
            fgets(answer, MAX_LENGTH, stdin);
            answer[strcspn(answer, "\n")] = 0;
            add_response(input, answer);
            printf("Bot: Got it! I'll remember that.\n");
        }
    }
    
    printf("Goodbye!\n");
    return 0;
}
