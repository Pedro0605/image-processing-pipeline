#include "Image.hpp"

namespace prog {
    Image::Image(int w, int h, const Color &fill) {
        image.resize(h, std::vector<Color>(w, fill));
    }

    Image::~Image() {
    }

    int Image::width() const {
        return static_cast<int>(image[0].size());
    }

    int Image::height() const {
        return static_cast<int>(image.size());
    }

    Color &Image::at(int x, int y) {
		return image[y][x];
    }

    const Color &Image::at(int x, int y) const {
        return image[y][x];
    }
}
