#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 999999

typedef struct {
    char *text;
    char **history;
    int history_count;
} TextEditor;

void initEditor(TextEditor *editor) {
    editor->text = (char *)calloc(1, MAX_LENGTH);
    editor->history = (char **)malloc(MAX_LENGTH * sizeof(char *));
    editor->history_count = 0;
}

void saveHistory(TextEditor *editor) {
    editor->history[editor->history_count] = strdup(editor->text);
    editor->history_count++;
}

void append(TextEditor *editor, const char *string) {
    saveHistory(editor);
    size_t new_len = strlen(editor->text) + strlen(string) + 1;
    editor->text = (char *)realloc(editor->text, new_len);
    strcat(editor->text, string);
}

void print(TextEditor *editor, int char_index) {
    if (char_index > 0 && char_index <= (int)strlen(editor->text)) {
        printf("%c\n", editor->text[char_index - 1]);
    }
}

void delete(TextEditor *editor, int char_index) {
    size_t len = strlen(editor->text);
    if (char_index > len) {
        return;
    }
    saveHistory(editor);
    editor->text[len - char_index] = '\0';
}

void undo(TextEditor *editor) {
    if (editor->history_count > 0) {
        editor->history_count--;
        free(editor->text);
        editor->text = strdup(editor->history[editor->history_count]);
    }
}

void freeEditor(TextEditor *editor) {
    free(editor->text);
    for (int i = 0; i < editor->history_count; i++) {
        free(editor->history[i]);
    }
    free(editor->history);
    free(editor);
}

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

