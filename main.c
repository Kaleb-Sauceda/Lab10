#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    struct TrieNode* children[26];
    int count;
};

// Initializes a trie node
struct TrieNode* createTrieNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->count = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Inserts a word into the trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* curr = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createTrieNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// Returns the number of occurrences of a word in the trie
int numberOfOccurrences(struct TrieNode* root, char* word) {
    struct TrieNode* curr = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocates the trie nodes
void deallocateTrie(struct TrieNode* root) {
    if (root == NULL) {
        free(root);
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            deallocateTrie(root->children[i]);
        }
    }
}

// Reads the dictionary file and returns the number of words
int readDictionary(char* filename, char** pInWords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the dictionary file.\n");
        return 0;
    }
    int numWords = 0;
    char word[256];
    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\n")] = '\0'; // remove newline character
        pInWords[numWords] = strdup(word);
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void) {
    char* inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    struct TrieNode* root = createTrieNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    deallocateTrie(&root);
    if (root != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}