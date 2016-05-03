#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

void triangle(Vec3i, Vec3i, Vec3i, Vec2i, Vec2i, Vec2i, TGAImage&, float, int*);
void rasterize(Vec2i, Vec2i, TGAImage&, const TGAColor, int[]);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor orange = TGAColor(255, 128, 0,   255);
const TGAColor blue = TGAColor(150, 150, 255,   255);

Model *model = NULL;
int *zbuf = NULL;
const int width = 800;
const int height = 800;
const int depth = 255;

int main(int argc, char** argv) {

    if (argc == 2)
        model = new Model(argv[1]);
    else
        model = new Model("obj/african_head.obj");

    // --- 2D render ---
    zbuf = new int[width * height];
    for (int i = 0; i < width * height; ++i)
        zbuf[i] = std::numeric_limits<int>::min();

    {// draw the model
        TGAImage img(width, height, TGAImage::RGB);

        const float half_w = width * 0.5, half_h = height * 0.5,
              half_d = depth * 0.5;
        const Vec3f light_dir(0, 0, -1);

        for (int i = 0; i < model->nfaces(); ++i) {
            std::vector<int> face = model->face(i);
            Vec3i screen_coords[3];
            Vec3f world_coords[3];
            for (int j = 0; j < 3; ++j) {
                Vec3f v = model->vert(face[j]);
                screen_coords[j] = Vec3i((v.x + 1.0) * half_w,
                        (v.y + 1.0) * half_h, (v.z + 1.0) * half_d);
                world_coords[j] = v;
            }
            Vec3f n = (world_coords[2] - world_coords[0]) ^
                (world_coords[1] - world_coords[0]);
            n.normalize();
            float br = n * light_dir; // brightness, light intensity
            if (br > 0) {
                Vec2i uv[3];
                for (int k = 0; k < 3; ++k)
                    uv[k] = model->uv(i, k);
                triangle(screen_coords[0], screen_coords[1], screen_coords[2],
                        uv[0], uv[1], uv[2], img, br, zbuf);
            }
        }

        img.flip_vertically(); //set the origin at the left bottom corner
        img.write_tga_file("output.tga");
    }

    delete model;

    {// z-buffer (for debugging)
        TGAImage zbimage(width, height, TGAImage::GRAYSCALE);
        for (int i = 0; i < width; ++i)
            for (int j = 0; j < height; ++j)
                zbimage.set(i, j, TGAColor(zbuf[i + j * width], 1));

        zbimage.flip_vertically(); //set the origin at the left bottom corner
        zbimage.write_tga_file("zbuffer.tga");

        delete [] zbuf;
    }

    /*
     * scene testing
    // --- scene ---
    TGAImage scene(width, height, TGAImage::RGB);

    // lines for "2D mesh"
    line(Vec2i(20, 34), Vec2i(744, 400), scene, red);
    line(Vec2i(120, 434), Vec2i(444, 400), scene, green);
    line(Vec2i(330, 463), Vec2i(594, 200), scene, blue);

    // screen line
    line(Vec2i(10, 10), Vec2i(790, 10), scene, white);

    scene.flip_vertically(); //set the origin at the left bottom corner
    scene.write_tga_file("scene.tga");
    // --- scene done ---

    // --- render ---
    TGAImage render(width, 16, TGAImage::RGB);
    int ybuffer[width];
    for (int i = 0; i < width; ++i)
    ybuffer[i] = std::numeric_limits<int>::min();

    rasterize(Vec2i(20, 34), Vec2i(744, 400), render, red, ybuffer);
    rasterize(Vec2i(120, 434), Vec2i(444, 400), render, green, ybuffer);
    rasterize(Vec2i(330, 463), Vec2i(594, 200), render, blue, ybuffer);

    // widen the image
    for (int i = 0; i < width; ++i)
    for (int j = 1; j < 16; ++j)
    render.set(i, j, render.get(i, 0));

    render.flip_vertically(); //set the origin at the left bottom corner
    render.write_tga_file("render.tga");
    // --- render done ---
     * scene testing done
     */

    return 0;
}

void triangle(Vec3i t0, Vec3i t1, Vec3i t2, Vec2i uv0, Vec2i uv1, Vec2i uv2,
        TGAImage &img, float br, int *zbuf) {

    if (t0.y==t1.y && t0.y==t2.y) return; // avoid dots
    if (t0.y>t1.y) {
        std::swap(t0, t1);
        std::swap(uv0, uv1);
    }
    if (t0.y>t2.y){
        std::swap(t0, t2);
        std::swap(uv0, uv2);
    }
    if (t1.y>t2.y) {
        std::swap(t1, t2);
        std::swap(uv1, uv2);
    }

    int y0 = t0.y, y1 = t1.y, y2 = t2.y;

    const int h = y2 - y0; // max height
    const int dy01 = y1 - y0, dy12 = y2 - y1;
    const bool y01 = y0 == y1;
    const Vec3f t02 = Vec3f(t2 - t0), t01 = Vec3f(t1 - t0),
          t12 = Vec3f(t2 - t1);

    for (int y = 0; y < h; ++y) {
        const bool up = y > dy01 || y01; // which part of the triangle
        const float a = (static_cast<float>(y) / h);
        const float b = up ? static_cast<float>(y - dy01) / dy12 :
            (static_cast<float>(y) / dy01);
        Vec3i A = t0 + t02 * a;
        Vec3i B = up ? t1 + t12 * b : t0 + t01 * b;
        Vec2i uvA = uv0 + (uv2 - uv0) * a;
        Vec2i uvB = up ? uv1 + (uv2 - uv1) * b : uv0 + (uv1 - uv0) * b;

        if (A.x > B.x) {
            std::swap(A, B);
            std::swap(uvA, uvB);
        }

        const int xa = A.x, xb = B.x, dxab = xb - xa;
        const bool xab = (xa == xb);
        const Vec3f Av = Vec3f(A), dAB = Vec3f(B - A);

        for (int x = xa; x <= xb; ++x) {
            float phi = xab ? 1.0 : static_cast<float>(x - xa) / dxab;
            Vec3i P = Av + dAB * phi;
            Vec2i uvP = uvA + (uvB - uvA) * phi;
            int idx = P.x + P.y * width;
            if (zbuf[idx] < P.z) {
                zbuf[idx] = P.z;
                TGAColor color = model->diffuse(uvP);
                img.set(P.x, P.y, TGAColor(color.r * br, color.g * br,
                            color.b*br));
            }
        }
    }
}

void rasterize(Vec2i p0, Vec2i p1, TGAImage &img, const TGAColor color,
        int ybuf[]) {
    if (p0.x > p1.x) std::swap(p0, p1);
    const int x0 = p0.x, x1 = p1.x;
    const int y0 = p0.y, y1 = p1.y, dy = y1 - y0;
    const float dx = static_cast<float>(x1 - x0);

    for (int x = x0; x <= x1; ++x) {
        int y = (x - x0) / dx * dy + y0;
        if (ybuf[x] < y) {
            ybuf[x] = y;
            img.set(x, 0, color);
        }
    }
}
