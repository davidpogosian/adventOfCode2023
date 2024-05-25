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

int main(int argc, char** argv) {
    
    
    return 0;
}