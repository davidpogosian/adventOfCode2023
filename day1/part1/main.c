#include <stdio.h>
#include <stdlib.h>

char* loadFile(const char* filename, long* size) {
    FILE *file = fopen(filename, "rb");
    char *buffer;
    
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    
    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);  // Rewind to the beginning of the file
    
    // Allocate memory for the file content
    buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }
    
    // Read the file into the buffer
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';  // Null-terminate the buffer
    
    fclose(file);
    
    if (size) {
        *size = fileSize;
    }
    
    return buffer;
}

int isDigit(char character) {
        if ((int)character >= 48 && (int)character <= 57) {
                return 1;
        }

        return 0;
}

int main(int argc, char** argv) {
        char* filename = "input.txt";
        long fileSize;
        char* fileContent = loadFile(filename, &fileSize);

        int firstDigit = -1;
        int lastDigit = -1;

        int sum = 0;

        for (int i = 0; i < fileSize; ++i) {
                char character = fileContent[i];
                //printf("character: %c \n", character);

                if (character == '\n') {
                        if (firstDigit == -1) {
                                // No digits found.
                                continue;
                        }

                        int concatenation = firstDigit * 10 + lastDigit;
                        printf("%d \n", concatenation);
                        sum += concatenation;

                        // Reset.
                        firstDigit = -1;
                        lastDigit = -1;
                        continue;
                }

                if (isDigit(character)) {
                        //printf("Digit. \n");
                        if (firstDigit == -1) {
                                firstDigit = (int)character - 48;
                        }
                        lastDigit = (int)character - 48;
                }
        }

        // Last line.
        if (firstDigit != -1) {
                int concatenation = firstDigit * 10 + lastDigit;
                printf("%d \n", concatenation);
                sum += concatenation;
        }

        printf("sum: %d \n", sum);
        free(fileContent);
        return 0;
}