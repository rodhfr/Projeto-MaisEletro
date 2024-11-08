# include <stdio.h>


int main() {
    FILE *file;
    int data[5] = {10, 20, 30, 40, 50};

    file = fopen("data.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    size_t written = fwrite(data, sizeof(int), 5, file);
    if (written != 5) {
        perror("Erro ao escrever os dados");
    }

    fclose(file);
    return 0;
}