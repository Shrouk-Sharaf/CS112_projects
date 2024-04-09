#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

// Define necessary constants for image types and unsupported type
#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

// Define implementation macros for STB image libraries
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// Include necessary libraries
#include <iostream>
#include <exception>
#include "stb_image.h"
#include "stb_image_write.h"
using namespace std;

// Declare the Image class
class Image {
private:
    // Private member functions for internal usage

    // Check if the filename has a valid extension
    bool isValidFilename(const string& filename) {
        const char* extension = strrchr(filename.c_str(), '.');
        if (extension == nullptr) {
            cout << "Invalid filename: " << filename << endl;
            return false;
        }
        return true;
    }

    // Determine the type of image based on the file extension
    short getExtensionType(const char* extension) {
        if (strcmp(extension, ".png") == 0) {
            return PNG_TYPE;
        }
        if (strcmp(extension, ".bmp") == 0) {
            return BMP_TYPE;
        }
        if (strcmp(extension, ".tga") == 0) {
            return TGA_TYPE;
        }
        if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) {
            return JPG_TYPE;
        }
        cout << "Unsupported image format: " << extension << endl;
        return UNSUPPORTED_TYPE;
    }

private:
    // Private member variables

    string filename; ///< Stores the filename of the image.

public:
    // Public member variables

    int width = 0; ///< Width of the image.
    int height = 0; ///< Height of the image.
    int channels = 3; ///< Number of color channels in the image.
    unsigned char* imageData = nullptr; ///< Pointer to the image data.

    // Constructors and Destructor

    // Default constructor
    Image() = default;

    // Constructor to load an image from a file
    Image(string filename) : filename((filename)) {
        loadNewImage(this->filename);
    }

    // Constructor to create an empty image with specified dimensions
    Image(int mWidth, int mHeight) {
        this->width = mWidth;
        this->height = mHeight;
        this->imageData = (unsigned char*)malloc(mWidth * mHeight * this->channels);
    }

    // Destructor to free memory
    ~Image() {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }
    }

    // Public member functions

    // Load a new image from the specified filename
    bool loadNewImage(const string& filename) {
        if (!isValidFilename(filename)) {
            cout << "Couldn't Load Image" << '\n';
            throw invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(filename.c_str(), '.');
        short extensionType = getExtensionType(extension);

        if (extensionType == UNSUPPORTED_TYPE) {
            cout << "Unsupported File Format" << '\n';
            throw invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }

        imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

        if (imageData == nullptr) {
            cout << "File Doesn't Exist" << '\n';
            throw invalid_argument("Invalid filename, File Does not Exist");
        }

        return true;
    }

    // Save the image to the specified output filename
    bool saveImage(const string& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            cout << "Not Supported Format" << '\n';
            throw invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(outputFilename.c_str(), '.');
        short extensionType = getExtensionType(extension);

        if (extensionType == UNSUPPORTED_TYPE) {
            cout << "File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported" << '\n';
            throw invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
        } else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        } else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        } else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);
        }

        return true;
    }

    // Get the pixel value at the specified position and channel
    unsigned char& getPixel(int x, int y, int c) {
        if (x > width || x < 0) {
            cout << "Out of width bounds" << '\n';
            throw out_of_range("Out of bounds, Cannot exceed width value");
        }

        if (y > height || y < 0) {
            cout << "Out of height bounds" << '\n';
            throw out_of_range("Out of bounds, Cannot exceed height value");
        }

        if (c < 0 || c > 2) {
            cout << "Out of channels bounds" << '\n';
            throw out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }

    // Set the pixel value at the specified position and channel
    void setPixel(int x, int y, int c, unsigned char value) {
        if (x > width || x < 0) {
            cout << "Out of width bounds" << '\n';
            throw out_of_range("Out of bounds, Cannot exceed width value");
        }

        if (y > height || y < 0) {
            cout << "Out of height bounds" << '\n';
            throw out_of_range("Out of bounds, Cannot exceed height value");
        }

        if (c < 0 || c > 2) {
            cout << "Out of channels bounds" << '\n';
            throw out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        imageData[(y * width + x) * channels + c] = value;
    }

    // Overloaded operator to access pixel values using parentheses
    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
};
#endif
