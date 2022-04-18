#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE] [RGB];

void loadImage ();
void saveImage ();
void bAndW ();
void flipImage(char option);
void detectImageEdges();
void mirrorImage();
//void blur();
void invert();
void rotateImage();

int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    char filter;
    cout <<"Please enter file name of the image to process : " << endl << "->";
    loadImage();

    while (true){
        cout << "Please select a filter to apply or 0 to exit:\n";
        cout << "1-Black & white Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Darken and Lighten Image";
        cout << "\n6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\na- Mirror 1/2 Image";
        cout << "\nb- Shuffle Image\nc- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
        cin.ignore();
        cin >> filter;

        if (filter =='0'){
            break;
        }
        else if (filter == '1'){
            bAndW();
        }
        else if (filter == '2'){
            invert();
        }
        else if (filter == '4'){
            char option ;
            cout <<"Flip (h)orizontally or (v)ertically ?\n-->";
            cin >> option;
            flipImage(option);
        }
        else if (filter == '6'){
            rotateImage();
        }
        else if (filter == '7'){
            detectImageEdges();
        }
        else if (filter == 'a'){
            mirrorImage();
        }
//        else if (filter == 'c'){
//            blur();
//        }
        else if (filter == 's'){
            saveImage();
            break;
        }
    }

    return 0;
}
//_________________________________________________

void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name

    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
//_____________________________________________

void bAndW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0 ; k < RGB ; k++) {
                image[i] [j] [k] /= 3;
//                if (image[i][j] [k] > 127)
//                    image[i][j] [k] = 255;
//                else
//                    image[i][j] [k]= 0;
            }
        }
    }
}
//___________________________________________________________

void flipImage(char option){


    if (option == 'v'){
        for (int i = 0 ; i < SIZE/2 ; i++){
            for (int j = 0 ; j < SIZE ; j++){
                for (int k = 0 ; k < RGB ; k++) {
                    int temp = image[i][j] [k];
                    image[i][j][k] = image[SIZE - i - 1][j] [k];
                    image[SIZE - i - 1][j][k] = temp;
                }
            }
        }
    }
    else if (option == 'h'){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE/2 ; j++){
                for (int k = 0 ; k < RGB ; k++){
                    int temp = image[i][j][k];
                    image[i][j] [k] = image[i][SIZE-j-1] [k];
                    image[i][SIZE-j-1] [k] = temp;
                }
            }
        }
    }
}
////____________________________________________________________
//
void detectImageEdges(){
    bAndW();
    for (int i = 0 ; i <255; i++){
        for (int j = 0 ; j < 255; j++){
            for (int k = 0 ; k < RGB ; k++) {
                if (image[i][j][k] != image[i][j + 1][k] || image[i][j] [k]!= image[i + 1][j][k]) {
                    image[i][j][k] = 0;
                } else if (image[i][j][k] == image[i][j + 1][k] || image[i][j][k] == image[i + 1][j][k]) {
                    image[i][j][k] = 255;
                }
            }
        }
    }
}

////______________________________________________________
void mirrorImage(){
    char side;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n -->";
    cin >> side;
    if (side == 'l'){
        for (int i = 0; i <255; i++){
            for (int j = 127; j < 255 ; j++){
                for (int k = 0 ; k < RGB ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
    else if (side == 'r'){
        for (int i = 0; i <255; i++){
            for (int j = 0; j < 127 ; j++){
                for (int k = 0 ; k < RGB ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }

    if (side == 'u'){
        for (int i = 127; i <255; i++){
            for (int j = 0; j < 255 ; j++){
                for (int k = 0 ; k < RGB ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
    if (side == 'd'){
        for (int i = 0; i <127; i++){
            for (int j = 0; j < 255 ; j++){
                for (int k = 0 ; k < RGB ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
}

////________________________________________________________________________________
//void blur () {
//    int value;
//    for (int i=0 ; i < SIZE ; i+=2){
//        for (int j=0 ; j < SIZE ; j+=2){
//            value =((image[i][j]+image[i+1][j]+image[i][j+1]+image[i+1][j+1]+image[i][j+2]+image[i+2][j]+image[i+2][i+2]+image[i+1][j+2]+image[i+2][j+1])/9);
//            image[i][j]=value;
//            image[i+1][j]=value;
//            image[i][j+1]=value;
//            image[i+1][j+1]=value;
//            image[i][j+2]=value;
//            image[i+2][j]=value;
//            image[i+2][i+2]=value;
//            image[i+1][j+2]=value;
//            image[i+2][j+1]=value;
//
//        }}
//}
////_______________________________________________________________________
void invert(){
    for (int i=0; i < 255; i++){
        for (int j = 0 ; j < 255 ; j++){
            for (int k = 0 ; k < RGB ; k++){
                int x = image[i][j] [k];
                image[i][j][k] = abs( RGB - image[i] [j] [k]);
            }

        }
    };
}

////_______________________________________________________________________________
void rotateImage() {
    int d;
    cout << "Rotate (90), (180) or (270) degrees?";
    cin >> d;
    int c = d / 90;
   for (int k = 0; k < c; k++)
   {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i; j < SIZE; j++)
        {
            for (int k = 0 ; k < RGB; k++)
            {
                int temp = image[i][j][k];
                image[i][j][k] = image[j][i][k];
                image[j][i][k] = temp;
            }
        }
    }
    flipImage('h');
}

}