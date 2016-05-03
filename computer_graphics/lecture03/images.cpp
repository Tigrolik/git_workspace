#include <iostream>
#include <ctime>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void gray2bw(Mat &I, const int threshold_val) {

    CV_Assert(I.depth() == CV_8U);

    int nRows = I.rows, nCols = I.cols * I.channels();

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    uchar *p;
    for (int i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; ++j)
            if (p[j] > threshold_val)
                p[j] = 255;
            else
                p[j] = 0;
    }
}

void gray2bw2(Mat &I, const int threshold_val) {

    CV_Assert(I.depth() == CV_8U);

    switch (I.channels()) {
        case 1:
            {
                MatIterator_<uchar> it, end;
                for (it = I.begin<uchar>(), end = I.end<uchar>();
                        it != end; ++it)
                    if (*it > threshold_val)
                        *it = 255;
                    else
                        *it = 0;
                break;
            }
        case 3:
            {
                MatIterator_<Vec3b> it, end;
                for (it = I.begin<Vec3b>(), end = I.end<Vec3b>();
                        it != end; ++it) {
                    if ((*it)[0] > threshold_val)
                        (*it)[0] = 255;
                    else
                        (*it)[0] = 0;
                    if ((*it)[1] > threshold_val)
                        (*it)[1] = 255;
                    else
                        (*it)[1] = 0;
                    if ((*it)[2] > threshold_val)
                        (*it)[2] = 255;
                    else
                        (*it)[2] = 0;
                }
                break;
            }
    }
}

void orderedDither(Mat &I, const int map_size) {

    CV_Assert(I.depth() == CV_8U);

    (void) map_size;
    int M2[2][2] = {
        {0, 2},
        {3, 1}
    };

    int nRows = I.rows;

    uchar *p = I.ptr<uchar>(0);
    for (int i = 0; i < nRows * I.cols; ++i) {
        if (p[i] * 5 / 256 > M2[(i / nRows) % 2][(i % nRows) % 2])
            p[i] = 255;
        else
            p[i] = 0;
    }
}

void errorDiffusion(Mat &I) {
    CV_Assert(I.depth() == CV_8U);

    int nRows = I.rows;

    uchar *p = I.ptr<uchar>(0);
    int qErr, temp;
    for (int i = 2; i < nRows * I.cols - 2; ++i) {
        temp = (p[i] > 128) ? 255 : 0;
        qErr = p[i] - temp;
        p[i + 1] += qErr / 4;
        p[i + 2] += qErr * 3 / 16;
        p[i + nRows - 2] += qErr / 16;
        p[i + nRows - 1] += qErr / 8;
        p[i + nRows] += qErr * 3 / 16;
        p[i + nRows + 1] += qErr / 8;
        p[i + nRows + 2] += qErr / 16;
    }
}

void dispalyRGBchannels(const Mat I) {
    int nRows = I.rows, nCols = I.cols;
    Mat bI(nRows, nCols, CV_8U);
    Mat gI(nRows, nCols, CV_8U);
    Mat rI(nRows, nCols, CV_8U);

    Vec3b intensity;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            intensity = I.at<Vec3b>(i, j);
            bI.at<uchar>(i, j) = intensity.val[0];
            gI.at<uchar>(i, j) = intensity.val[1];
            rI.at<uchar>(i, j) = intensity.val[2];
        }
    }

    imshow("red", rI);
    imshow("green", gI);
    imshow("blue", bI);
}

void dispalyCMYKchannels(const Mat I) {
    int nRows = I.rows, nCols = I.cols;
    Mat cI(nRows, nCols, CV_8UC1);
    Mat mI(nRows, nCols, CV_8UC1);
    Mat yI(nRows, nCols, CV_8UC1);
    Mat kI(nRows, nCols, CV_8UC1);

    Vec3b intensity;
    float r, g, b, c, m, y, k;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            intensity = I.at<Vec3b>(i, j);
            b = static_cast<int>(intensity.val[0]) / 255.0;
            g = static_cast<int>(intensity.val[1]) / 255.0;
            r = static_cast<int>(intensity.val[2]) / 255.0;
            c = 1 - r;
            m = 1 - g;
            y = 1 - b;
            k = min(min(c, m), y);
            y -= k;
            m -= k;
            c -= k;
            cI.at<uchar>(i, j) = 255 * c;
            mI.at<uchar>(i, j) = 255 * (1 - m);
            yI.at<uchar>(i, j) = static_cast<int>(128 * (y));
            kI.at<uchar>(i, j) = 255 * (1 - k);
        }
    }

    imshow("cyan", cI);
    imshow("magenta", mI);
    imshow("yellow", yI);
    imshow("black", kI);
}

void dispalyHSVchannels(const Mat I) {
    int nRows = I.rows, nCols = I.cols;
    Mat hI(nRows, nCols, CV_8UC1);
    Mat sI(nRows, nCols, CV_8UC1);
    Mat vI(nRows, nCols, CV_8UC1);

    Vec3b intensity;
    int maxc, minc, delta;
    int r, g, b;
    float rc, gc, bc;
    float s, h, v;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            intensity = I.at<Vec3b>(i, j);
            b = static_cast<int>(intensity.val[0]);
            g = static_cast<int>(intensity.val[1]);
            r = static_cast<int>(intensity.val[2]);
            maxc = max(max(r, g), b);
            minc = min(min(r, g), b);
            delta = maxc - minc;
            s = 0;
            if (maxc > 0)
                s = static_cast<float>(delta) / static_cast<float>(maxc);
            v = maxc;
            if (s == 0.0)
                h = 0.0;
            else {
                rc = static_cast<float>(maxc - r) / delta;
                gc = static_cast<float>(maxc - g) / delta;
                bc = static_cast<float>(maxc - b) / delta;
                if (r == maxc)
                    h = bc - gc;
                else if (g == maxc)
                    h = 2 + rc - bc;
                else
                    h = 4 + gc - rc;
                h *= 60.0;
            }

            hI.at<uchar>(i, j) = h;
            sI.at<uchar>(i, j) = 255 * s;
            vI.at<uchar>(i, j) = v;
        }
    }

    imshow("hue", hI);
    imshow("saturation", sI);
    imshow("value", vI);
}

void dispalyYCrCbchannels(const Mat I) {
    int nRows = I.rows, nCols = I.cols;
    Mat yI(nRows, nCols, CV_8UC1);
    Mat crI(nRows, nCols, CV_8UC1);
    Mat cbI(nRows, nCols, CV_8UC1);

    Vec3b intensity;
    int r, g, b;
    for (int i = 0; i < nRows; ++i)
        for (int j = 0; j < nCols; ++j) {
            intensity = I.at<Vec3b>(i, j);
            b = static_cast<int>(intensity.val[0]);
            g = static_cast<int>(intensity.val[1]);
            r = static_cast<int>(intensity.val[2]);

            yI.at<uchar>(i, j) = 0.299 * r + 0.587 * g + 0.114 * b;
            crI.at<uchar>(i, j) = 0.5 * r - 0.4187 * g - 0.0813 * b + 128;
            cbI.at<uchar>(i, j) = 0.1687 * r - 0.3313 * g + 0.5 * b + 128;
        }
    imshow("Y", yI);
    imshow("Cr", crI);
    imshow("Cb", cbI);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " imageFileName\n";
        return EXIT_FAILURE;
    }

    Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    //imshow("1", img);

    //dispalyRGBchannels(img);
    dispalyCMYKchannels(img);
    //dispalyHSVchannels(img);
    //dispalyYCrCbchannels(img);

    //cvtColor(img, img, CV_RGB2HSV);
    //dispalyRGBchannels(img);
#if 0
    Mat I;

    img.copyTo(I);
    gray2bw2(I, 128);
    imshow("2", I);

    img.copyTo(I);
    errorDiffusion(I);
    imshow("3", I);

    img.copyTo(I);
    orderedDither(I, 2);
    imshow("4", I);
#endif

    waitKey(0);

    return EXIT_SUCCESS;
}
