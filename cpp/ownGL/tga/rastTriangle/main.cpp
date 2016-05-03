#include <vector>
#include <cmath>
#include <cstdlib>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"


void line(const Vec2i, const Vec2i, TGAImage&, const TGAColor);

void triangle(Vec2i, Vec2i, Vec2i, TGAImage&, TGAColor);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor orange = TGAColor(255, 128, 0,   255);
const TGAColor blue = TGAColor(150, 150, 255,   255);

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
    const Vec3f light_dir(0, 0, -1);

    for (int i = 0; i < model->nfaces(); ++i) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; ++j) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1) * half_w, (v.y + 1) * half_h);
            world_coords[j] = v;
        }
        Vec3f n = (world_coords[2] - world_coords[0]) ^
            (world_coords[1] - world_coords[0]);
        n.normalize();
        float br = n * light_dir;
        if (br > 0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2],
                    image, TGAColor(br * 255, br * 255, br * 255, 255));
        }
    }


    /*
     * testing triangles
    Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 70)};
    Vec2i t1[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

    triangle(t0[0], t0[1], t0[2], image, red);
    triangle(t1[0], t1[1], t1[2], image, white);
    triangle(t2[0], t2[1], t2[2], image, green);
    */

	image.flip_vertically(); //set the origin at the left bottom corner
    image.write_tga_file("output.tga");

    delete model;

	return 0;
}

void line(const Vec2i t0, const Vec2i t1, TGAImage &img, const TGAColor color)
{

    int x0 = t0.x, x1 = t1.x, y0 = t0.y, y1 = t1.y;

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

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &img, TGAColor color) {

    if (t0.y == t1.y && t1.y == t2.y) return; // avoid dots

    // sorting the vertices in the ascending order
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);

    int y0 = t0.y, y1 = t1.y, y2 = t2.y;
    const int x0 = t0.x, x1 = t1.x, x2 = t2.x;

    const int h = y2 - y0; // max height
    const int dx01 = x1 - x0, dx02 = x2 - x0, dx12 = x2 - x1;
    const int dy01 = y1 - y0, dy12 = y2 - y1;
    const bool y01 = y0 == y1;

    for (int y = 0; y < h; ++y) {
        int xa = x0 + dx02 * (static_cast<float>(y) / h);
        int xb = (y > dy01 || y01) ? // which part of the triangle
            x1 + dx12 * (static_cast<float>(y - dy01) / dy12) :
            x0 + dx01 * (static_cast<float>(y) / dy01);
        if (xa > xb) std::swap(xa, xb);

        // filling the triangle
        for (int x = xa; x <= xb; ++x)
            img.set(x, y0 + y, color);
    }

}

