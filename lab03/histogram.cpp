#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "histogram.h"

using namespace std;

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='"<< left <<"' y='"<< baseline <<"'>"<< text << "</text>"<<endl;
}

void svg_rect(double x, double y, double width, double height, double fill_opacity, string stroke, string fill)
{
    cout << "<rect x = '" << x << "' y = '" << y << "' width = '" << width << "' height = '" 
         <<  height <<"' stroke = '"<< stroke <<"' fill = '"<< fill<<"' fill-opacity='" << fill_opacity << "' />" << endl;
}

void
svg_end() {
    cout << "</svg>\n";
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double max_bin = bins[0];
    for (double bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }

    
    for (size_t bin : bins)
    {
        size_t height = bin * BLOCK_WIDTH;
        if (max_bin * BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH)
        {
            height = (IMAGE_WIDTH - TEXT_WIDTH) * (static_cast<double>(bin) / max_bin);
        }
        const double bin_width = height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,bin/max_bin,"black","red");
        top += BIN_HEIGHT;
    }
    svg_end();
}