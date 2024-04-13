#include "Image_Class.h"
#include <cmath>
#include <iostream>
#include <string>
using namespace std;
bool isvalidExtension(const string& filename) {
    const string validExtensions[] = {".jpg", ".jpeg", ".png", ".bmp"};
    unsigned long long size = filename.length() - 1;
    int i = (int)size;
    while (i >= 0 && filename[i] != '.') {
        i--;
    }
    if (i >= 0) {
        string extension = filename.substr(i);
        for (const string& validExtension : validExtensions) {
            if (extension == validExtension)
                return true;
        }
    }
    return false;
}
void Convert_to_BW() {
    cout << "Please enter your file name" << endl;
    string filename, new_file;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    const unsigned int threshold = 127;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg /= image.channels;
            for (int k = 0; k < image.channels; k++) {
                if (avg < threshold)
                    image(i, j, k) = 0;
                else
                    image(i, j, k) = 255;
            }
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> new_file;
    while (!isvalidExtension(new_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> new_file;
    }
    image.saveImage(new_file);
    cout << "Converted to black and white successfully." << endl;
}
void Flip() {
    cout << "Please enter your file name." << endl;
    string filename, new_file;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    int choice;
    while (true) {
        cout << "Choose one of the following:\n1) Horizontal\n2) Vertical" << endl;
        if (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            cin.clear();
            while (cin.get() != '\n');
        } else {
            break;
        }
    }
    if (choice == 1) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < image.channels; k++) {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    } else if (choice == 2) {
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width / 2; j++) {
                for (int k = 0; k < image.channels; k++) {
                    swap(image(j, i, k), image(image.width - 1 - j, i, k));
                }
            }
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> new_file;
    while (!isvalidExtension(new_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> new_file;
    }
    image.saveImage(new_file);
    cout << "Flipped successfully." << endl;
}
void Invert() {
    string filename, saved_file;
    cout << "Please enter your file name" << endl;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    image.saveImage(saved_file);
    cout << "Image inverted successfully." << endl;
}
void Framed_image() {
    string filename;
    cout << "Please enter your file name" << endl;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    int choice;
    while (true) {
        cout << "Choose one of the following:\n1) Simple frame\n2) Fancy frame" << endl;
        if (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            cin.clear();
            while (cin.get() != '\n');
        } else {
            break;
        }
    }
    if (choice == 1) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (i < 10 || i > image.width - 10 || j < 10 || j > image.height - 10)
                        image(i, j, k) = 255;
                    else if (i < 20 || i >= image.width - 20 && i <= image.width - 10 || j < 20 || j >= image.height - 20 && j <= image.height - 10) {
                        image(i, j, 0) = 0;
                        image(i, j, 1) = 0;
                        image(i, j, 2) = 255;
                    }
                }
            }
        }
        string saved_file;
        cout << "Please enter the file name and extension for the saved filtered image" << endl;
        cin >> saved_file;
        while (!isvalidExtension(saved_file)) {
            cout << "invalid file name! please enter a valid one." << endl;
            cin >> saved_file;
        }
        image.saveImage(saved_file);
        cout << "The simple frame added successfully." << endl;

    } else if (choice == 2) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if ((i < 5) || (i > image.width - 5) || (j < 5) || (j > image.height - 5) ||
                        (i >= 15 && i < 17)
                        || (i >= 20 && i < 22) || (i >= 25 && i < 27) ||
                        (i >= image.width - 27 && i < image.width - 25)
                        || (i >= image.width - 22 && i < image.width - 20) ||
                        (i >= image.width - 17 && i < image.width - 15)
                        || (j >= 15 && j < 17) || (j >= 20 && j < 22) || (j >= 25 && j < 27)
                        || (j >= image.height - 27 && j < image.height - 25) ||
                        (j >= image.height - 22 && j < image.height - 20)
                        || (j >= image.height - 17 && j < image.height - 15)

                            ) {
                        image(i, j, k) = 255;
                    } else if (i < 15 || i >= image.width - 15 && i <= image.width - 5 ||
                               j < 15
                               || j >= image.height - 15 && j <= image.height - 5) {
                        image(i, j, 0) = 0;
                        image(i, j, 1) = 0;
                        image(i, j, 2) = 255;
                    }
                }
            }
        }
        string saved_file;
        cout << "Please enter the file name and extension for the saved filtered image" << endl;
        cin >> saved_file;
        while (!isvalidExtension(saved_file)) {
            cout << "invalid file name! please enter a valid one." << endl;
            cin >> saved_file;
        }
        image.saveImage(saved_file);
        cout << "The fancy frame was added successfully." << endl;
    }
}
void Gray_scale() {
    cout << "Please enter your file name" << endl;
    string filename;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    //gray scaling
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    string saved_file;
    cout << "Please enter the file name and extension for the saved filtered image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    image.saveImage(saved_file);
    cout << "The image has turned gray successfully" << endl;
}
void CropImage() {
    cout << "Please enter your file name" << endl;
    string filename;
    cin >> filename;
    int X, Y, newWidth, newHeight;
    cout << "Enter the starting X-coordinate of the crop region\n";
    cin >> X;
    cout << "Enter the starting Y-coordinate of the crop region\n";
    cin >> Y;
    cout << "Enter the width of the cropped region\n";
    cin >> newWidth;
    cout << "Enter the height of the cropped region\n";
    cin >> newHeight;
    Image image(filename);
    if (X < 0 || Y < 0 || newWidth <= 0 || newHeight <= 0 || X + newWidth > image.width || Y + newHeight > image.height) {
        cout << "Invalid crop dimensions" << endl;
        return;
    }
    Image croppedImage(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                unsigned char pixelValue = image(X + x, Y + y, c);
                croppedImage.setPixel(x, y, c, pixelValue);
            }
        }
    }
    croppedImage.width = newWidth;
    croppedImage.height = newHeight;
    swap(image.imageData, croppedImage.imageData);
    swap(image.width, croppedImage.width);
    swap(image.height, croppedImage.height);
    if (croppedImage.imageData != nullptr) {
        stbi_image_free(croppedImage.imageData);
    } // if I want to avoid memory leak, I should use this
    string saved_file;
    cout << "Please enter the file name and extension for the saved cropped image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    image.saveImage(saved_file);
    cout << "The image has been cropped successfully" << endl;
}
void Resizing() {
    int newWidth, newHeight;
    cout << "Please enter your file name" << endl;
    string filename, new_file;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    cout << "Enter the new width" << endl;
    cin >> newWidth;
    cout << "Enter the new height" << endl;
    cin >> newHeight;
    float scaleX = (float)image.width / (float)newWidth;
    float scaleY = (float)image.height / (float)newHeight;
    Image resizedImage(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            float originalX = (float)x * scaleX;
            float originalY = (float)y * scaleY;
            int nearestX = lround(originalX);
            int nearestY = lround(originalY);
            nearestX = min(max(nearestX, 0), image.width - 1);
            nearestY = min(max(nearestY, 0), image.height - 1);
            for (int c = 0; c < image.channels; ++c) {
                int pixelValue = image.getPixel(nearestX, nearestY, c);
                resizedImage.setPixel(x, y, c, pixelValue);
            }
        }
    }
    string saved_file;
    cout << "Please enter the file name and extension for the saved resized image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    resizedImage.saveImage(saved_file); // Save the resized image
    cout << "The image has been resized successfully" << endl;
}
void Purple(){
    cout << "Please enter your file name" << endl;
    string filename, new_file;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                if (k == 1)
                     image(i, j, k) = static_cast <unsigned char> (image(i, j, k) * 0.7);
            }
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> new_file;
    while (!isvalidExtension(new_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> new_file;
    }
    image.saveImage(new_file);
    cout << "Converted to purple successfully." << endl;
}
void Rotate(){
    string filename, saved_file;
    cout << "Please enter your file name" << endl;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    int choice;
    while (true) {
        cout << "Choose one of the following:\n1) rotate 90 degree\n2) rotate 180 degree\n3) rotate 270 degree" << endl;
        if (!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3)) {
            cout << "Invalid choice. Please enter 1 or 2 or 3." << endl;
            cin.clear();
            while (cin.get() != '\n');
        } else {
            break;
        }
    }
    Image rotated_image (image.width , image.height);

    if (choice == 1) {
            for (int i = 0; i < image.height; ++i) {
                for (int j = 0; j < image.width; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated_image(i, j, k) = image(j, image.height - i - 1, k);
                    }
                }
            }
    } else if (choice == 2) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    rotated_image (i , j , k) = (image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    }else if (choice == 3){
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotated_image(i, j, k) = image(image.width - j - 1, i, k);
                }
            }
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    rotated_image.saveImage(saved_file);
    cout << "rotated successfully." << endl;
}
void Blur(){
    string filename, saved_file;
    cout << "Please enter your file name" << endl;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
    Image blur(image.width, image.height);
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int sum = 0;
            int Red = 0, Green = 0, Blue = 0;
            for (int ky = -20; ky <= 20; ++ky) {
                for (int kx = -20; kx <= 20; ++kx) {
                    int nx = x + kx;
                    int ny = y + ky;
                    if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                        Red += image(nx, ny, 0);
                        Green += image(nx, ny, 1);
                        Blue += image(nx, ny, 2);
                        sum++;
                    }
                }
            }
            unsigned char avg_Red = Red / sum;
            unsigned char avg_Green = Green / sum;
            unsigned char avg_Blue = Blue / sum;
            blur(x, y, 0) = avg_Red;
            blur(x, y, 1) = avg_Green;
            blur(x, y, 2) = avg_Blue;
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> saved_file;
    while (!isvalidExtension(saved_file)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> saved_file;
    }
    blur.saveImage(saved_file);
    cout << "rotated successfully." << endl;
}
int main() {
    while (true) {
        int choice;
        while (true) {
            cout << "Choose one of the following filters:\n1) Convert to black and white\n2) Flip image\n3) Invert Image\n4) Add Frames to the image\n5) Gray scale\n6) Crop image\n7) Resize\n8) Purple filter\n9) Rotate\n10) Blur\n11) Exit\n";
            if (!(cin >> choice) || choice < 1 || choice > 11) {
                cout << "Invalid choice ! Please enter a valid option." << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else
                break;
        }
        if (choice == 1)
            Convert_to_BW();
        else if (choice == 2)
            Flip();
        else if (choice == 3)
            Invert();
        else if (choice == 4)
            Framed_image();
        else if (choice == 5)
            Gray_scale();
        else if (choice == 6)
            CropImage();
        else if (choice == 7)
            Resizing();
        else if (choice == 8)
            Purple();
        else if (choice == 9)
            Rotate();
        else if (choice == 10)
            Blur();
        else if (choice == 11) {
            cout << "Program  is terminating..." << endl;
            break;
        }
    }
}