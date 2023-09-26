#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Point;

double calculatePolygonArea(Point vertices[], int numVertices) {
    double area = 0.0;
    for (int i = 0; i < numVertices; i++) {
        int j = (i + 1) % numVertices;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }
    area = area / 2.0;
    return area;
}

int main() {
    FILE *file;
    int numVertices;
    file = fopen("vertices.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }
    fscanf(file, "%d", &numVertices);
    Point *vertices = (Point *)malloc(numVertices * sizeof(Point));
    if (vertices == NULL) {
        perror("Erro de alocação de memória");
        fclose(file);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < numVertices; i++) {
        fscanf(file, "%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    fclose(file);
    double area = calculatePolygonArea(vertices, numVertices);
    if (area < 0) {
        area = -area;
    }
    printf("A área do polígono é %.2lf\n", area);
    free(vertices);
    return EXIT_SUCCESS;
}
