#include <stdio.h>
#include <ctype.h>

void count_characters(FILE *file, int *vowels, int *consonants, int *punctuation, int *total_chars) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            ch = tolower(ch);
            if (ch == 'a') {
                vowels[0]++;
            } else if (ch == 'e') {
                vowels[1]++;
            } else if (ch == 'i') {
                vowels[2]++;
            } else if (ch == 'o') {
                vowels[3]++;
            } else if (ch == 'u') {
                vowels[4]++;
            } else {
                (*consonants)++;
            }
            (*total_chars)++;
        } else if (ispunct(ch)) {
            (*punctuation)++;
            (*total_chars)++;
        }
        // Ignore spaces and newlines
    }
}

void calculate_and_write_results(int *vowels, int consonants, int punctuation, int total_chars) {
    FILE *output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Error creating output file.\n");
        return;
    }

    fprintf(output, "Percentages of various characters:\n\n");
    printf("Percentages of various characters:\n\n");

    char vowel_letters[] = "aeiou";
    for (int i = 0; i < 5; i++) {
        double percent = ((double)vowels[i] * 100.0) / (double)total_chars;
        fprintf(output, "%c  %d%% ; ", vowel_letters[i], (int)(percent + 0.5));
        printf("%c  %d%% ; ", vowel_letters[i], (int)(percent + 0.5));
    }

    double consonant_percent = ((double)consonants * 100.0) / (double)total_chars;
    double punct_percent = ((double)punctuation * 100.0) / (double)total_chars;

    fprintf(output, "consonants  %d%% ; punct %d%%\n", (int)(consonant_percent + 0.5), (int)(punct_percent + 0.5));
    printf("consonants  %d%% ; punct %d%%\n", (int)(consonant_percent + 0.5), (int)(punct_percent + 0.5));

    fclose(output);
}


int main() {
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    int vowels[5] = {0}; // Counts for a, e, i, o, u
    int consonants = 0, punctuation = 0, total_chars = 0;

    count_characters(file, vowels, &consonants, &punctuation, &total_chars);
    fclose(file);

    if (total_chars == 0) {
        printf("No valid characters found in the file.\n");
        return 1;
    }

    calculate_and_write_results(vowels, consonants, punctuation, total_chars);

    return 0;
}
