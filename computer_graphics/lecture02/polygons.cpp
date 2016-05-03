#include <GL/glew.h>
#include <GL/glut.h>
#include <png.h>
#include <cstdio>
#include <string>
#include <iostream>

#define TEXTURE_LOAD_ERROR 0

using namespace std;

GLuint loadTexture(const string filename, int &width, int &height)
{
    // header for testing if file is .png
    png_byte header[8];

    // open file as binary
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        return TEXTURE_LOAD_ERROR;

    // read the header
    fread(header, 1, 8, fp);

    // test if png
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            nullptr, nullptr, nullptr);

    if (!png_ptr) {
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)nullptr,
                (png_infopp)nullptr);
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)nullptr);
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // png error stuff, not sure libpng man suggests this
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 twidth, theight;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
            nullptr, nullptr, nullptr);

    // update width and height based on png info
    width = twidth;
    height = theight;

    // update the png info struct
    png_read_update_info(png_ptr, info_ptr);

    // row size in bytes
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];

    cout << image_data[27] << endl;

    if (!image_data) {
        // clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // row_pointers is for pointing to image_data for reading png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    if (!row_pointers) {
        // clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete [] image_data;
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    // set the indivdual row_pointers to point at correct offsets of image_data
    for (int i = 0; i < height; ++i)
        row_pointers[height - 1 - i] = image_data + i * rowbytes;

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // generate the OpenGL texture object
    GLuint texture;
    glGenTextures(GL_TEXTURE_2D, &texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, (GLvoid *) image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete [] image_data;
    delete [] row_pointers;
    fclose(fp);

    return texture;
}

void draw_tri() {
    float vertices[] = {0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };
    // GLuint is a cross-platform substitute for unsigned int
    GLuint vbo;
    glGenBuffers(1, &vbo); // generate 1 buffer
    // activate using binding
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // copy the vertex data. Note: doesn't use the id of vbo but the active
    // array buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
#if 0
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]){2.0, 2.0, 2.0, 0.0});
    // glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[]){1.0, 1.0, 1.0, 0.0});

    int img_w = 0, img_h = 0;
    GLuint texture = loadTexture("building.png", img_w, img_h);
    cout << sizeof(texture) << endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // fov, aspect, near, far
    gluPerspective(60, 1, 1, 10);
    gluLookAt(0, 0, -2, // eye
            0, 0, 2, // center
            0, 1, 0); //up
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


#endif
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, 600, 400, 0, -1, 1);
    glColor4ub(255, 255, 255, 255);

    int img_w = 0, img_h = 0;
    GLuint texture = loadTexture("building.png", img_w, img_h);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    /*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(0.0, 0.0);
    glTexCoord2d(1, 0); glVertex2f(0.0, 1.0);
    glTexCoord2d(1, 1); glVertex2f(1.0, 1.0);
    glTexCoord2d(0, 1); glVertex2f(1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glFlush();

    */
    // get window center coordinates
    // int w = glutGet(GLUT_WINDOW_WIDTH);
    // int h = glutGet(GLUT_WINDOW_HEIGHT);

    /* end */
    glutSwapBuffers();
}

void init() {
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polygons");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
