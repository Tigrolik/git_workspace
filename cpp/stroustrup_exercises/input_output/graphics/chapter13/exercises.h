struct Arc: Shape {
    Arc(Point p, const int ww, const int hh,const int ang_beg,
            const int ang_end): w_{ww}, h_{hh}, ang_beg_{ang_beg},
        ang_end_{ang_end} { add(Point{p.x - ww, p.y - hh}); }
    void draw_lines() const {
        if (color().visibility()) {
            fl_color(color().as_int());
            fl_arc(point(0).x, point(0).y, w_<<1, h_<<1, ang_beg_, ang_end_);
        }
    }
    private:
    int w_;
    int h_;
    int ang_beg_;
    int ang_end_;
};

struct Box: Shape {
    Box(Point p, const int ww, const int hh,
            const int x_off = 10, const int y_off = 10):
        w_{ww}, h_{hh}, x_offset_{x_off}, y_offset_{y_off} {
            if (x_off < 0 || y_off < 0) {
                cout << "Warning: negative offset, making a basic rectangle\n";
                x_offset_ = 0;
                y_offset_ = 0;
            } else if (x_off << 1 > ww || y_off << 1 > hh) {
                cout << "Warning: too big offset, making a basic rectangle\n";
                x_offset_ = 0;
                y_offset_ = 0;
            }
        add(p);
    }
    void draw_lines() const {
        if (color().visibility()) {
            fl_color(color().as_int());
            const int w_t1 {w_ - x_offset_};
            const int h_t1 {h_ - y_offset_};
            fl_line(point(0).x + x_offset_, point(0).y,
                    point(0).x + w_t1, point(0).y);
            fl_line(point(0).x + x_offset_, point(0).y + h_,
                    point(0).x + w_t1, point(0).y + h_);
            fl_line(point(0).x, point(0).y + y_offset_,
                    point(0).x, point(0).y + h_t1);
            fl_line(point(0).x + w_, point(0).y + y_offset_,
                    point(0).x + w_, point(0).y + h_t1);
            const int step_x = x_offset_ << 1, step_y = y_offset_ << 1;
            fl_arc(point(0).x, point(0).y, step_x, step_y, 90, 180);
            fl_arc(point(0).x, point(0).y + h_ - step_y, step_x, step_y,
                    180, 270);
            fl_arc(point(0).x + w_ - step_x, point(0).y + h_ - step_y,
                    step_x, step_y, 270, 360);
            fl_arc(point(0).x + w_ - step_x, point(0).y, step_x, step_y, 0, 90);
        }
    }
    private:
    int w_, h_, x_offset_, y_offset_;
};

struct Arrow: Shape {
    Arrow(Point p1, Point p2, const double ss=15, const double arr_angle=30):
        streak_size_{ss}, arr_ang_{arr_angle} { add(p1); add(p2); }
    void draw_lines() const {
        if (color().visibility()) {
            fl_color(color().as_int());
            const int dx{point(1).x - point(0).x}, dy{point(1).y - point(0).y};
            constexpr double pi {acos(-1)}, r {pi / 180};
            const double arr_ang {pi * (dx >= 0) + arr_ang_ * r};
            const double ang_t{atan(static_cast<double>(dy)/dx) - arr_ang};
            const double ang_s{atan(static_cast<double>(dy)/dx) + arr_ang};
            fl_line(point(1).x, point(1).y, point(0).x, point(0).y);
            fl_line(point(1).x, point(1).y, static_cast<int>(point(1).x +
                        streak_size_ * cos(ang_t)), static_cast<int>(point(1).y +
                        streak_size_ * sin(ang_t)));
            fl_line(point(1).x, point(1).y, static_cast<int>(point(1).x +
                        streak_size_ * cos(ang_s)), static_cast<int>(point(1).y +
                        streak_size_ * sin(ang_s)));
        }
    }
    private:
    double streak_size_;
    double arr_ang_;
};

struct Regular_polygon: Polygon {
    Regular_polygon(Point p, const int n_sides, const double r):
        no_of_sides_{n_sides}, r_{r}
    {
        const double ang {acos(-1) * 2.0 / no_of_sides_};
        for (int i {0}; i < no_of_sides_; ++i)
            add(Point{static_cast<int>(p.x + r_ * cos(i * ang)),
                    static_cast<int>(p.y - r_ * sin(i * ang))});
    }
    private:
    int no_of_sides_;
    double r_;
};

Graph_lib::Point n(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + (r.width() >> 1), r.point(0).y};
}

Graph_lib::Point s(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + (r.width() >> 1), r.point(0).y + r.height()};
}

Graph_lib::Point w(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x, r.point(0).y + (r.height() >> 1)};
}

Graph_lib::Point e(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + r.width(), r.point(0).y + (r.height() >> 1)};
}

Graph_lib::Point nw(const Graph_lib::Rectangle &r) {
    return r.point(0);
}

Graph_lib::Point ne(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + r.width(), r.point(0).y};
}

Graph_lib::Point sw(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x, r.point(0).y + r.height()};
}

Graph_lib::Point se(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + r.width(), r.point(0).y + r.height()};
}

Graph_lib::Point center(const Graph_lib::Rectangle &r) {
    return Point{r.point(0).x + (r.width() >> 1),
        r.point(0).y + (r.height() >> 1)};
}


