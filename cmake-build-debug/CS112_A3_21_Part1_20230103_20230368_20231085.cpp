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
void Flip(){
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
void Resizing(){
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
void CropImage(){
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
void Framed_image(){
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
void Invert(){
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
void Gray_scale(){
    cout << "Please enter your file name" << endl;
    string filename;
    cin >> filename;
    while (!isvalidExtension(filename)) {
        cout << "invalid file name! please enter a valid one." << endl;
        cin >> filename;
    }
    Image image(filename);
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
void Infrared(){
    string filename, savedfile;
    int y;
    cout << "Please enter your file name" << endl;
    cin >> filename;
    while(!isvalidExtension(filename)){
        cout<<"invalid file name! please enter a valid one."<<endl;
        cin>>filename;
    }
    Image image(filename);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = 255;
            y = image(i, j, 1);
            image(i, j, 1) = 255 - image(i, j, 2);
            image(i, j, 2) = 255 - y;
        }
    }
    cout << "Enter the filename and extension for the saved filtered image" << endl;
    cin >> savedfile;
    while(!isvalidExtension(savedfile))
    {
        cout<<"invalid file name! please enter a valid one."<<endl;
        cin>>savedfile;
    }
    image.saveImage(savedfile);
    cout << "The image filter has been applied successfully"<<endl;
}
void EdgeDetection() {
    string filename, savedfile;
    cout << "Enter the filename of the image" << endl;
    cin >> filename;
    while(!isvalidExtension(filename)){
        cout<<"invalid input! please enter a valid one. "<<endl;
        cin>>filename;
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
                if (avg < threshold) {
                    image(i, j, k) = 0;
                } else {
                    image(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < image.width - 1; i++) {
        for (int j = 0; j < image.height - 1; j++) {
            int intensity_diff_x = abs(image(i, j, 0) - image(i + 1, j, 0));
            int intensity_diff_y = abs(image(i, j, 0) - image(i, j + 1, 0));
            if (intensity_diff_x > threshold || intensity_diff_y > threshold) {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
            else {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    cout<<"Enter the name of the saved file:"<<endl;
    cin>>savedfile;
    while(!isvalidExtension(savedfile)){
        cout<<"invalid input! please enter a valid input"<<endl;
        cin>>savedfile;
    }
    image.saveImage(savedfile);
    cout << "Edge detection filter applied successfully."<<endl;
}
void DarkeningOrLightening() {
    int choice;
    while (true) {
        cout << "Please choose:\n1) Darkening image\n2) Lightening image\n";
        if(!(cin>>choice)||(choice!=1 && choice!=2)){
            cout<<"invalid choice! please enter 1 or 2"<<endl;
            cin.clear();
            while(cin.get()!='\n');
        }
        else
            break;
    }
    if (choice == 1) {
        cout << "Welcome to Darkening image filter" << endl;
        string filename, savedFile;
        cout << "Enter the file name of the image: "<<endl;
        cin >> filename;
        while(!isvalidExtension(filename)){
            cout<<"invalid input, please enter a valid one "<<endl;
            cin>>filename;
        }
        Image image(filename);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    // Corrected by explicitly casting the result to unsigned char
                    image(i, j, k) = static_cast<unsigned char>(image(i, j, k) * 0.5);
                }
            }
        }
        cout << "Enter the name of the saved file: "<<endl;
        cin >> savedFile;
        while(!isvalidExtension(savedFile)){
            cout<<"invalid input,please enter a valid one: "<<endl;
            cin>>savedFile;
        }
        image.saveImage(savedFile);
        cout << "The image has become darker successfully" << endl;
    }
    else if (choice == 2) {
        cout << "Welcome to Lightening image filter" << endl;
        string filename, savedFile;
        cout << "Enter the file name of the image: "<<endl;
        cin >> filename;
        while(!isvalidExtension(filename)){
            cout<<"invalid input,please enter a valid one: "<<endl;
            cin>>filename;
        }
        Image image(filename);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    // Corrected by handling the conversion explicitly and safely
                    int value = static_cast<int>(1.5 * image(i, j, k));
                    if (value > 255) {
                        image(i, j, k) = 255;
                    } else {
                        image(i, j, k) = static_cast<unsigned char>(value);
                    }
                }
            }
        }
        cout << "Enter the name of the saved file: "<<endl;
        cin >> savedFile;
        while(!isvalidExtension(savedFile)){
            cout<<"invalid input,please enter a valid input: "<<endl;
            cin>>savedFile;
        }
        image.saveImage(savedFile);
        cout << "The image has been lightened successfully" <<endl;
    }
}
Image Resizing(Image image, int newWidth, int newHeight) {
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
    // Copy resized image to the original image
    return resizedImage;
}
void merging_image(string file_name1, string file_name2, const string& saved_file, int choice) {
    Image image1(std::move(file_name1));
    Image image2(std::move(file_name2));
    if (choice == 1) {
        int max_width = max(image1.width, image2.width);
        int max_height = max(image1.height, image2.height);

        // Resize images
        Image re1 = Resizing(image1, max_width, max_height);
        Image re2 = Resizing(image2, max_width, max_height);

        // Merge resized images
        float variable = 0.5;
        Image new_image(max_width, max_height);
        for (int i = 0; i < max_width; i++) {
            for (int j = 0; j < max_height; j++) {
                for (int k = 0; k < 3; k++) {
                    unsigned char image1_pixel = (i < re1.width && j < re1.height) ? re1.getPixel(i, j, k) : 0;
                    unsigned char image2_pixel = (i < re2.width && j < re2.height) ? re2.getPixel(i, j, k) : 0;
                    unsigned new_pixel = static_cast<unsigned char>((1 - variable) * image1_pixel + variable * image2_pixel);
                    new_image.setPixel(i, j, k, new_pixel);
                }
            }
        }
        new_image.saveImage(saved_file);
    } else if (choice == 2) {
        int min_width=min(image1.width,image2.width);
        int min_height=min(image1.height,image2.height);
        Image new_image(min_width,min_height);
        // loop on the smallest width and smallest height
        for(int i=0;i<min_width;i++){
            for(int j=0;j<min_height;j++){
                for(int k=0;k<3;k++){
                    new_image(i,j,k)=(image1(i,j,k)+image2(i,j,k))/2;
                    if(new_image(i,j,k)>255)
                        new_image(i,j,k)=255;
                }
            }
        }
        new_image.saveImage(saved_file);
    }
    else
        cout<<"Invalid Input "<<endl;
}
void MergeImagesAndSave() {
    string file_name1, file_name2, saved_file;
    int choice;
    cout << "Welcome to merge effect" << endl;
    cout << "Enter the file name of the first image: " << endl;
    cin >> file_name1;
    cout << "Enter the file name of the second image: " << endl;
    cin >> file_name2;
    cout << "Enter the saved file name" << endl;
    cin >> saved_file;
    cout << "If two images have different dimensions what do you want to do this filter by:\n1)resizing\n2)cropping" << endl;
    cin >> choice;
    cout << "The two images have been merged successfully" << endl;
    merging_image(file_name1, file_name2, saved_file,choice);
}
int main() {
    while (true) {
        int choice;
        while (true) {
            cout << "Choose one of the following filters:\n1) Convert to black and white\n2) Flip image\n3) Invert Image"
                    "\n4) Add Frames to the image\n5) Gray scale\n6) Crop image\n7) Resize\n8) Purple filter\n9) Rotate"
                    "\n10) Blur\n11) Darken or lighten\n12) Edge detection\n 13) Infrared\n14) Merge\n15) Exit";
            if (!(cin >> choice) || choice < 1 || choice > 16) {
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
        else if (choice == 11)
            DarkeningOrLightening();
        else if (choice == 12)
            EdgeDetection();
        else if (choice == 13)
            Infrared();
        else if (choice == 14)
            MergeImagesAndSave();
        else if (choice == 15) {
            cout << "Program  is terminating..." << endl;
            break;
        }
    }
}
