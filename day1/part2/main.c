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

int spelledDigit(char character, char* fileContent, long fileSize, int i) {
        switch (character) {
                case 'z': // zero
                        if (i + 3 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'e' && fileContent[i + 2] == 'r' && fileContent[i + 3] == 'o') {
                                //*index += 3;
                                return 0;
                        } 

                        return -1;
                case 'o': // one
                        if (i + 2 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'n' && fileContent[i + 2] == 'e') {
                                //*index += 2;
                                return 1;
                        }

                        return -1;
                case 't': // two | three
                        if (i + 2 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'w' && fileContent[i + 2] == 'o') {
                                //*index += 2;
                                return 2;
                        }

                        if (i + 4 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'h' && fileContent[i + 2] == 'r' && fileContent[i + 3] == 'e' && fileContent[i + 4] == 'e') {
                                //*index += 4;
                                return 3;
                        }

                        return -1;
                case 'f': // four | five
                        if (i + 3 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'o' && fileContent[i + 2] == 'u' && fileContent[i + 3] == 'r') {
                                //*index += 3;
                                return 4;
                        }

                        if (fileContent[i + 1] == 'i' && fileContent[i + 2] == 'v' && fileContent[i + 3] == 'e') {
                                //*index += 3;
                                return 5;
                        }

                        return -1;
                case 's': // six | seven
                        if (i + 2 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'i' && fileContent[i + 2] == 'x') {
                                //*index += 2;
                                return 6;
                        }

                        if (i + 4 >= fileSize) {
                                break;
                        }

                        if (fileContent[i + 1] == 'e' && fileContent[i + 2] == 'v' && fileContent[i + 3] == 'e' && fileContent[i + 4] == 'n') {
                                //*index += 4;
                                return 7;
                        }

                        return -1;
                case 'e': // eight
                        if (i + 4 >= fileSize) {
                                return -1;
                        }

                        if (fileContent[i + 1] == 'i' && fileContent[i + 2] == 'g' && fileContent[i + 3] == 'h' && fileContent[i + 4] == 't') {
                                //*index += 4;
                                return 8;
                        }

                        return -1;
                case 'n': // nine
                        if (i + 3 >= fileSize) {
                                return -1;                                
                        }

                        if (fileContent[i + 1] == 'i' && fileContent[i + 2] == 'n' && fileContent[i + 3] == 'e') {
                                //*index += 3;
                                return 9;
                        }

                        return -1;
        }

        return -1;
}

int main(int argc, char** argv) {
        char* filename = "input.txt";
        long fileSize;
        char* fileContent = loadFile(filename, &fileSize);

        int firstDigit = -1;
        int lastDigit = -1;

        int line = 1;
        int sum = 0;

        int i = 0;
        while (i < fileSize) {
                char character = fileContent[i];

                if (character == '\n') {
                        if (firstDigit == -1) {
                                // No digits found.
                                continue;
                        }

                        int concatenation = firstDigit * 10 + lastDigit;
                        printf("%d: %d \n", line, concatenation);
                        sum += concatenation;

                        // Reset.
                        firstDigit = -1;
                        lastDigit = -1;

                        line += 1;
                } else if (isDigit(character)) {
                        if (firstDigit == -1) {
                                firstDigit = (int)character - 48;
                        }

                        lastDigit = (int)character - 48;
                } else {
                        int charDigit = spelledDigit(character, fileContent, fileSize, i);
                        if (charDigit != -1) {
                                if (firstDigit == -1) {
                                        firstDigit = charDigit;
                                }

                                lastDigit = charDigit;
                        }
                }

                ++i;
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