#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

void line(int, int, int, int, TGAImage&, TGAColor);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
// Model *model = NULL;
const int width = 800;
const int height = 800;

int main(int argc, char** argv) {

    Model *model = NULL;
    if (argc == 2)
        model = new Model(argv[1]);
    else
        model = new Model("obj/african_head.obj");

	TGAImage image(width, height, TGAImage::RGB);

    const float half_w = width * 0.5, half_h = height * 0.5;

    for (int i = 0; i < model->nfaces(); ++i) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; ++j) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            // int x0 = (v0.x + 1.0) * half_w, y0 = (v0.y + 1.0) * half_h;
            // int x1 = (v1.x + 1.0) * half_w, y1 = (v1.y + 1.0) * half_h;
            line((v0.x + 1.0) * half_w, (v0.y + 1.0) * half_h,
                    (v1.x + 1.0) * half_w, (v1.y + 1.0) * half_h, image, green);
        }
    }

	image.flip_vertically(); //set the origin at the left bottom corner
    image.write_tga_file("output.tga");

    delete model;

	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color) {

    int dx = std::abs(x0 - x1), dy = std::abs(y0 - y1);
    const bool steep = dy > dx;

    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(dx, dy);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const int incrdy = dy + dy, incrdx = dx + dx, ystep = (y0 < y1) ? 1 : -1;
    int e = dx;

    for (int x = x0; x <= x1; ++x) {
        if (steep)
            img.set(y0, x, color);
        else
            img.set(x, y0, color);

        // e -= incrdy;
        if ((e -= incrdy) < 0) {
            y0 += ystep;
            e += incrdx;
        }
    }
}

