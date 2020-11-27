#include <stdio.h>
#include <time.h>
#include <GL/gl.h>
#include <string.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "../include/utils.h"

/** Representa um ponto. */
typedef struct _point
{

    GLfloat x, y;                         /** Coordenda do ponto. */

} point_t;

/** Representa um segmento de reta. */
typedef struct _segment
{

    point_t str;                          /** Ponto inicial. */
    point_t end;                          /** Ponto final.   */

} segment_t;

size_t size = 0;
int segmentsCount = 0;

segment_t *segments = NULL;

void usage(void);

void display(void);

bool ccw(point_t A, point_t B, point_t C);
bool intersect(point_t A, point_t B, point_t C, point_t D);
bool isValid(point_t A, point_t B);
void generateSegment(void);

int main(int argc, char **argv)
{

    if (argc != 4)
        usage();

    int height = atoi(argv[1]);
    int width = atoi(argv[2]);
    segmentsCount = atoi(argv[3]);

    ensure(height > 0, "Altura inválida.");
    ensure(width > 0, "Largura inválida.");
    ensure(segmentsCount >= 0, "Quantidade de segmentos inválida.");

    srand(time(NULL));

    segments = (segment_t *)calloc(segmentsCount + 1, sizeof(segment_t));
    _alloc_check(segments, "Falha ao alocar vetor de segmentos.");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutCreateWindow("Segmentos Aleatorios");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, -1.0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void display(void)
{

    // segment_t lines[] = {{{0.7, 0.7}, {-0.3, -0.2}}, {{0.2, 0.9}, {0.6, 0.1}}};
    generateSegment();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(point_t), segments);
    glDrawArrays(GL_LINES, 0, size << 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

bool ccw(point_t A, point_t B, point_t C)
{

    return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

bool intersect(point_t A, point_t B, point_t C, point_t D)
{

    return (ccw(A, C, D) != ccw(B, C, D)) && (ccw(A, B, C) != ccw(A, B, D));
}

bool isValid(point_t A, point_t B)
{

    for (size_t i = 0; i < size; ++i)
        if (intersect(A, B, segments[i].str, segments[i].end))
            return false;

    return true;
}

void generateSegment(void)
{

    point_t start = {0};
    point_t end = {0};
    int signal[] = {-1, 1};

    size = 0;

    for (size_t i = 0; i < (size_t)segmentsCount; ++i)
    {

        do
        {

            int cco[4] = {0};
            for (size_t j = 0; j < 4; ++j)
                cco[j] = rand();

            start.x = (cco[0] / (GLfloat)RAND_MAX) * signal[cco[0] % 2];
            start.y = (cco[1] / (GLfloat)RAND_MAX) * signal[cco[1] % 2];
            end.x = (cco[2] / (GLfloat)RAND_MAX) * signal[cco[2] % 2];
            end.y = (cco[3] / (GLfloat)RAND_MAX) * signal[cco[3] % 2];

        } while (!isValid(start, end));

        segments[size].str = start;
        segments[size].end = end;

        ++size;
    }
}

void usage(void)
{

    puts("main <ALTURA_DA_JANELA> <LARGURA_DA_JANELA> <QUANTIDADE_DE_SEGMENTOS>");
    exit(1);
}