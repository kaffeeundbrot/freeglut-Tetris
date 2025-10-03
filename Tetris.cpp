#include <GL/freeglut.h>

// ======================
// Globals
// ======================
float squareSize = 0.2f;

// Movable piece controlled by arrow keys
float squareX = 0.0f;
float squareY = 0.0f;
float currentColor[3] = { 0.2f, 0.7f, 1.0f };

// ======================
// Helper Functions
// ======================
void drawSquare(float x, float y, float s)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + s, y);
    glVertex2f(x + s, y + s);
    glVertex2f(x, y + s);
    glEnd();
}

// O piece
void drawOPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x + s, y + s, s);
}

// I piece
void drawIPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    for (int i = 0; i < 4; i++)
        drawSquare(x + i * s, y, s);
}

// T piece
void drawTPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x + 2 * s, y, s);
    drawSquare(x + s, y + s, s);
}

// S Piece
void drawSPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x + s, y + s, s);
    drawSquare(x + 2 * s, y + s, s);
}

// Z piece
void drawZPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x + s, y, s);
    drawSquare(x + 2 * s, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x + s, y + s, s);
}

// L piece
void drawLPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x, y + 2 * s, s);
    drawSquare(x + s, y, s);
}

// J Piece
void drawJPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x, y + 2 * s, s);
    drawSquare(x - s, y, s);
}

// rotated na T piece
void drawTPieceRight(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;

    // Original T (horizontal top) looks like:
    // [ ][ ][ ]
    //    [ ]
    // Rotated right (clockwise):
    // [ ]
    // [ ][ ]
    // [ ]

    drawSquare(x, y, s);       // top
    drawSquare(x, y + s, s);   // middle left
    drawSquare(x + s, y + s, s); // middle right
    drawSquare(x, y + 2 * s, s); // bottom
}


//display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // pre placed blockss
    float green[3] = { 0.0f, 1.0f, 0.0f };
    float purple[3] = { 1.0f, 0.0f, 1.0f };
    float red[3] = { 1.0f, 0.0f, 0.0f };
    float yellow[3] = { 1.0f, 1.0f, 0.0f };
    float blue[3] = { 0.0f, 0.0f, 1.0f };
    float orange[3] = { 1.0f, 0.5f, 0.0f };
    float cyan[3] = { 0.2f, 0.7f, 1.0f };

    drawSPiece(-0.8f, -1.0f, green);     // fixed S piece
    drawTPieceRight(-1.0f, -1.0f, purple);    // fixed T piece
    drawZPiece(-1.0f, -0.6f, red); // fixed Z piece
    drawOPiece(0.4f, -0.8f, yellow); // fixed o piece
    drawLPiece(0.2f, -1.0f, orange); // fixed L piece
    drawJPiece(0.8f, -1.0f, blue); // fixed j piece
    drawIPiece(0.2f, -0.4f, cyan);

    // dito yung moveable pieces
    drawJPiece(squareX, squareY, blue);

    glutSwapBuffers();
}

// ======================
// Keyboard Handling
// ======================
void handleSpecialKeys(int key, int, int)
{
    const float step = 0.2f;
    switch (key) {
    case GLUT_KEY_LEFT:  squareX -= step; break;
    case GLUT_KEY_RIGHT: squareX += step; break;
    case GLUT_KEY_UP:    squareY += step; break;
    case GLUT_KEY_DOWN:  squareY -= step; break;
    }
    glutPostRedisplay();
}

void handleNormalKeys(unsigned char key, int, int)
{
    switch (key) {
    case 'r': case 'R': currentColor[0] = 1.0f; currentColor[1] = 0.1f; currentColor[2] = 0.1f; break;
    case 'g': case 'G': currentColor[0] = 0.2f; currentColor[1] = 1.0f; currentColor[2] = 0.2f; break;
    case 'b': case 'B': currentColor[0] = 0.2f; currentColor[1] = 0.5f; currentColor[2] = 1.0f; break;
    case 'c': case 'C':
        currentColor[0] = 0.2f; currentColor[1] = 0.7f; currentColor[2] = 1.0f;
        squareX = 0.0f; squareY = 0.0f;
        break;
    case 27: glutLeaveMainLoop(); return;
    }
    glutPostRedisplay();
}

// ======================
// Main
// ======================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 520);
    glutCreateWindow("Pre-placed & Movable Tetromino Example");

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleNormalKeys);
    glutSpecialFunc(handleSpecialKeys);

    glutMainLoop();
    return 0;
}
