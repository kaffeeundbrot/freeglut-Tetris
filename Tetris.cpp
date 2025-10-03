#include <GL/freeglut.h>

// ======================
// Globals
// ======================
float squareSize = 0.2f;
float moveX = 0.0f;
bool piecePlaced = false;
bool JPiecePlaced = false;
bool TPiecePlaced = false;
bool IPiecePlaced = false;
bool tetrisClear = false;
void WhitePieces(int);
void OriginalPieces(int);

float green[3] = { 0.0f, 1.0f, 0.0f };
float purple[3] = { 1.0f, 0.0f, 1.0f };
float red[3] = { 1.0f, 0.0f, 0.0f };
float yellow[3] = { 1.0f, 1.0f, 0.0f };
float blue[3] = { 0.0f, 0.0f, 1.0f };
float orange[3] = { 1.0f, 0.5f, 0.0f };
float cyan[3] = { 0.2f, 0.7f, 1.0f };
float white[3] = { 1.0f, 1.0f, 1.0f };

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

// ======================
// Pieces
// ======================

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

// ======================
// Rotated Pieces
// ======================

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

void drawTPieceDown(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;

    // Bottom row (3 squares)
    drawSquare(x, y, s);       // left
    drawSquare(x + s, y, s);   // middle
    drawSquare(x + 2 * s, y, s); // right

    // Bottom middle square
    drawSquare(x + s, y - s, s);
}

// Rotated na IPiece
void drawIPieceVertical(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    for (int i = 0; i < 4; i++)
        drawSquare(x, y - i * s, s);
}

//display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

		if (!tetrisClear) {
			
			// ======================
			// Pre Placed Blocks
			// ======================
			
			drawSPiece(-0.8f, -1.0f, green);     // fixed S piece
	    drawTPieceRight(-1.0f, -1.0f, purple);    // fixed T piece
	    drawZPiece(-1.0f, -0.6f, red); // fixed Z piece
	    drawOPiece(0.4f, -0.8f, yellow); // fixed o piece
	    drawLPiece(0.2f, -1.0f, orange); // fixed L piece
	    drawJPiece(0.8f, -1.0f, blue); // fixed j piece
	    drawIPiece(0.2f, -0.4f, cyan); // fixed i peice
		
			// ======================
			// Pieces Hardcoded Animation 
			// ======================
	
			// Third Piece
			if (TPiecePlaced && !IPiecePlaced) {
				 if (squareY > 0.9f) {
		    	drawIPiece(squareX, squareY, cyan);
				} else if (squareX < 0.0f) {
					moveX = 0.02f; // move right by x increment
					drawIPieceVertical(squareX, squareY, cyan);
				} else if (squareY > -0.4f) {
					moveX = 0.0f; // stop
					drawIPieceVertical(squareX, squareY, cyan);
				} else {
					drawIPieceVertical(0.0f, -0.4f, cyan);
					piecePlaced = IPiecePlaced = true;
					tetrisClear = true;
				}
			} else if (TPiecePlaced) {
				drawIPieceVertical(0.0f, -0.4f, cyan);
			}
	
			// Second Piece
	    if (JPiecePlaced && !TPiecePlaced) {
		    if (squareY > 0.6f) {
		    	drawTPiece(squareX, squareY, purple);
				} else if (squareX > -0.2f) {
					moveX = -0.02f; // move left by x increment
					drawTPieceRight(squareX, squareY, purple);
				} else if (squareX > -0.4f && squareY > -0.5f) {
					moveX = -0.02f; // move left by x increment
					drawTPieceDown(squareX, squareY, purple);
				} else if (squareX > -0.59f && squareY > -0.4f) {
					drawTPieceDown(squareX, squareY, purple);
				} else if (squareY > -0.4f) {
					moveX = 0.0f; // stop 
					drawTPieceDown(squareX, squareY, purple);
				} else {
					drawTPieceDown(-0.6f, -0.4f, purple);
					piecePlaced = TPiecePlaced = true;
					squareY = 1.0f;
					squareX = -0.4f;
				}
			} else if (JPiecePlaced) {
				drawTPieceDown(-0.6f, -0.4f, purple);
			}
	
			// First Piece
			if (!JPiecePlaced) {
				if (squareY > -1.0f) {
		    	drawJPiece(squareX, squareY, blue);
				} else if (squareX > -0.2f) {
					moveX = -0.02f; // move left by x increment
					drawJPiece(squareX, squareY, blue);
				} else {
					drawJPiece(-0.2f, -1.0f, blue);
					piecePlaced = JPiecePlaced = true;
				}
			} else {
				drawJPiece(-0.2f, -1.0f, blue);
			}
		} else {
			
			// ======================
			// Tetris Clear Animation
			// ======================
			
        glutTimerFunc(1000, WhitePieces, 0);
        glutTimerFunc(1500, OriginalPieces, 0);
        glutTimerFunc(2000, WhitePieces, 0);
		}
    glutSwapBuffers();
}

void WhitePieces(int value) {
		drawSPiece(-0.8f, -1.0f, white);     
    drawTPieceRight(-1.0f, -1.0f, white);    
    drawZPiece(-1.0f, -0.6f, white); 
    drawOPiece(0.4f, -0.8f, white);
    drawLPiece(0.2f, -1.0f, white); 
    drawJPiece(0.8f, -1.0f, white); 
    drawIPiece(0.2f, -0.4f, white); 
		drawJPiece(-0.2f, -1.0f, white);
		drawTPieceDown(-0.6f, -0.4f, white);
		drawIPieceVertical(0.0f, -0.4f, white);
		glClear(GL_COLOR_BUFFER_BIT);

}

void OriginalPieces(int value) {
		drawSPiece(-0.8f, -1.0f, green);
    drawTPieceRight(-1.0f, -1.0f, purple);
    drawZPiece(-1.0f, -0.6f, red); 
    drawOPiece(0.4f, -0.8f, yellow); 
    drawLPiece(0.2f, -1.0f, orange); 
    drawJPiece(0.8f, -1.0f, blue); 
    drawIPiece(0.2f, -0.4f, cyan); 
   	drawJPiece(-0.2f, -1.0f, blue);
		drawTPieceDown(-0.6f, -0.4f, purple);
		drawIPieceVertical(0.0f, -0.4f, cyan);
		glClear(GL_COLOR_BUFFER_BIT);
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

void update(int value)
{
    const float stepY = 0.02f; // smaller step for smoother movement
    squareY -= stepY;           // move down automatically
		squareX += moveX;


    if (squareY <= -1.0f) {
        squareY = -1.0f;
        
				if (piecePlaced) {
					piecePlaced = false;
					squareX = 0.0f; 
					moveX = 0.0f;
					squareY = 1.0f;       	
				}
    } // prevent going below


    glutPostRedisplay();       // redraw the screen
    glutTimerFunc(50, update, 0); // call update again in 50ms
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

    glutTimerFunc(50, update, 0); // start automatic movement

    glutMainLoop();
    return 0;
}
