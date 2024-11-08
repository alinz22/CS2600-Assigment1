#include <stdio.h>
#include <ctype.h>

void count_characters(FILE *file, int *vowels, int *consonants, int *punctuation, int *total_chars) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            (*total_chars)++;
            ch = tolower(ch);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowels[ch - 'a']++;
            } else {
                (*consonants)++;
            }
        } else if (ispunct(ch)) {
            (*punctuation)++;
            (*total_chars)++;
        }
    }
}

void calculate_and_write_results(int *vowels, int consonants, int punctuation, int total_chars) {
    FILE *output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Error creating output file.\n");
        return;
    }

    fprintf(output, "Percentages of various characters:\n");
    printf("Percentages of various characters:\n");

    char vowel_letters[] = "aeiou";
    for (int i = 0; i < 5; i++) {
        int percent = (vowels[i] * 100) / total_chars;
        fprintf(output, "%c %d%%; ", vowel_letters[i], percent);
        printf("%c %d%%; ", vowel_letters[i], percent);
    }

    int consonant_percent = (consonants * 100) / total_chars;
    int punct_percent = (punctuation * 100) / total_chars;

    fprintf(output, "consonants %d%%; punct %d%%\n", consonant_percent, punct_percent);
    printf("consonants %d%%; punct %d%%\n", consonant_percent, punct_percent);

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

    int vowels[5] = {0}; // a, e, i, o, u
    int consonants = 0, punctuation = 0, total_chars = 0;

    count_characters(file, vowels, &consonants, &punctuation, &total_chars);
    fclose(file);

    calculate_and_write_results(vowels, consonants, punctuation, total_chars);

    return 0;
}
