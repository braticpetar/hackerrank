#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Defining maximum length
#define MAX_LENGTH 999999

// We keep track of our current text (string), each individual change (array of strings) and the total amount of changes in our history
typedef struct {
    char *text;
    char **history;
    int history_count;
} TextEditor;

// Function that initializes our TextEditor structure
void initEditor(TextEditor *editor) {
    editor->text = (char *)calloc(1, MAX_LENGTH);
    editor->history = (char **)malloc(MAX_LENGTH * sizeof(char *));
    editor->history_count = 0;
}

// Function that adds current text to the history
void saveHistory(TextEditor *editor) {
    editor->history[editor->history_count] = strdup(editor->text);
    editor->history_count++;
}

// Function that saves history and then appends user's input to our current text
void append(TextEditor *editor, const char *string) {
    saveHistory(editor);
    size_t new_len = strlen(editor->text) + strlen(string) + 1;
    editor->text = (char *)realloc(editor->text, new_len);
    strcat(editor->text, string);
}

// Function that prints a character in a specified index
void print(TextEditor *editor, int char_index) {
    if (char_index > 0 && char_index <= (int)strlen(editor->text)) {
        printf("%c\n", editor->text[char_index - 1]);
    }
}

// Function that deletes a characters at specified index
void delete(TextEditor *editor, int char_index) {
    size_t len = strlen(editor->text);
    if (char_index > len) {
        return;
    }
    saveHistory(editor);
    editor->text[len - char_index] = '\0';
}

// Function that undoes the last thing we've done
void undo(TextEditor *editor) {
    if (editor->history_count > 0) {
        editor->history_count--;
        free(editor->text);
        editor->text = strdup(editor->history[editor->history_count]);
    }
}

// Frees the memory
void freeEditor(TextEditor *editor) {
    free(editor->text);
    for (int i = 0; i < editor->history_count; i++) {
        free(editor->history[i]);
    }
    free(editor->history);
    free(editor);
}

// Function for handling user inpu
void handleInput() {
    int q, operation, char_index;
    char temp[MAX_LENGTH];

    TextEditor *editor = malloc(sizeof(TextEditor));
    initEditor(editor);

    scanf("%d", &q);
    getchar();

    while (q--) {
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%s", temp);
                append(editor, temp);
                break;
            case 2:
                scanf("%d", &char_index);
                delete(editor, char_index);
                break;
            case 3:
                scanf("%d", &char_index);
                print(editor, char_index);
                break;
            case 4:
                undo(editor);
                break;
            default:
                printf("Invalid operation, try again!\n");
                break;
        }
    }

    freeEditor(editor);
}

int main() {
    handleInput();
    return 0;
}

