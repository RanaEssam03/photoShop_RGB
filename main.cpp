// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: photoShop.cpp
// Last Modification Date: 23/4/2022
// Author1 and ID and Group: Rana Essam Ibrahim 20210133 S1
// Author2 and ID and Group: Nourhan Abdullah  20210437 S1
// Author3 and ID and Group: Hazem Medhat  20210116
// Teaching Assistant: Eng: Nesma & Eng: Youssra
// Purpose:Full photo shop program

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <vector>
using namespace std;
unsigned char image[SIZE][SIZE] [RGB];

void loadImage ();
void saveImage ();
void bAndW ();
void flipImage(char option);
void detectImageEdges();
void mirrorImage();
void blur();
void invert();
void rotateImage();
void Enlarge ();
void darkenAndLighten();
void shrink();
void merge();
void shuffle();


int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    char filter;

    while (true){
        cout <<"Please enter file name of the image to process : " << endl << "->";
        loadImage();
        while (true) {
            cout << "Please select a filter to apply or 0 to exit:\n";
            cout << "1-Black & white Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Darken and Lighten Image";
            cout << "\n6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\na- Mirror 1/2 Image";
            cout << "\nb- Shuffle Image\nc- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
            cin.ignore();
            cin >> filter;

            if (filter == '0') {
                break;
            } else if (filter == '1') {
                bAndW();
            } else if (filter == '2') {
                invert();
            } else if (filter == '3') {
                merge();
            } else if (filter == '4') {
                char option;
                cout << "Flip (h)orizontally or (v)ertically ?\n-->";
                cin >> option;
                flipImage(option);
            } else if (filter == '5') {
                darkenAndLighten();
            } else if (filter == '6') {
                rotateImage();
            } else if (filter == '7') {
                detectImageEdges();
            } else if (filter == '8') {
                Enlarge();
            } else if (filter == '9') {
                shrink();
            } else if (filter == 'a') {
                mirrorImage();
            }
            else if (filter == 'b'){
                shuffle();
            }
            else if (filter == 'c') {
                blur();
            } else if (filter == 's') {
                saveImage();
                break;
            }

        }
        int x;
        cout << "Do you want to upload new image (1) or exit (0)?";
        cin >> x;
        if (x==0){
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

                if ((image [i] [j] [0] +image [i] [j] [1]+image [i] [j] [2] )/2 > 200){
                    image [i] [j] [0] = image [i] [j] [1]= image [i] [j] [2] = 255 ;
                }
                else
                    image [i] [j] [0] = image [i] [j] [1]= image [i] [j] [2] = 0 ;

        }
    }
}
//___________________________________________________________

void flipImage(char option){


    if (option == 'v'){
        for (int i = 0 ; i < SIZE/2 ; i++){
            for (int j = 0 ; j < SIZE ; j++){
                for (int k = 0 ; k < 3 ; k++) {
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
                for (int k = 0 ; k < 3 ; k++){
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
            for (int k = 0 ; k < 3 ; k++) {
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
                for (int k = 0 ; k < 3 ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
    else if (side == 'r'){
        for (int i = 0; i <255; i++){
            for (int j = 0; j < 127 ; j++){
                for (int k = 0 ; k < 3 ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }

    if (side == 'u'){
        for (int i = 127; i <255; i++){
            for (int j = 0; j < 255 ; j++){
                for (int k = 0 ; k < 3 ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
    if (side == 'd'){
        for (int i = 0; i <127; i++){
            for (int j = 0; j < 255 ; j++){
                for (int k = 0 ; k < 3 ; k++){
                    image[i][j][k] = image[i][255-j-1][k];
                }

            }
        }
    }
}

////________________________________________________________________________________
void blur () {
    int value;
    for (int i=0 ; i < SIZE ; i+=2){
        for (int j=0 ; j < SIZE ; j+=2){
            for (int k = 0 ; k < 3 ; k++) {
                value = ((image[i][j][k] + image[i + 1][j][k] + image[i][j + 1][k] + image[i + 1][j + 1][k] + image[i][j + 2] [k]+
                          image[i + 2][j] [k] + image[i + 2][i + 2][k] + image[i + 1][j + 2][k] + image[i + 2][j + 1][k]) / 9);
                image[i][j][k] = value;
                image[i + 1][j][k] = value;
                image[i][j + 1] [k] = value;
                image[i + 1][j + 1] [k] = value;
                image[i][j + 2] [k]= value;
                image[i + 2][j] [k]= value;
                image[i + 2][i + 2][k] = value;
                image[i + 1][j + 2][k] = value;
                image[i + 2][j + 1][k] = value;
            }

        }}
}
////_______________________________________________________________________
void invert(){
    for (int i=0; i < 255; i++){
        for (int j = 0 ; j < 255 ; j++){
            for (int k = 0 ; k < 3 ; k++){
                image[i][j][k] = abs( 255 - image[i] [j] [k]);
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
            for (int k = 0 ; k < 3; k++)
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
//--------------------------------------------------------------------------------------------
 void Enlarge (){
    unsigned char temp[SIZE / 2][SIZE / 2][3];
    int  startRow, startCol, endRow, endCol;
    int quarter = 0;
    while (quarter > 4 || quarter < 1) {
        cout << "Which quarter to enlarge 1, 2, 3 or 4?" << endl;
        cin >> quarter;
    }
    startRow = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
    endRow = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
    startCol = quarter == 1 || quarter == 3 ? 0 : SIZE / 2;
    endCol = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE;
    for (int i = startRow, row = 0; i < endRow; i++) {
        for (int j = startCol, col = 0; j < endCol; j++) {
            for (int k=0 ; k < 3 ; k++)
            temp[row][col][k] = image[i][j][k];
            col++;
        }
        row++;
    }
    int row = 0;
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0, col = 0; j < SIZE / 2; j++) {
            for (int k = 0 ; k < RGB; k++) {
                image[row][col][k] = temp[i][j][k];
                image[row + 1][col][k] = temp[i][j][k];
                image[row][col + 1][k] = temp[i][j][k];
                image[row + 1][col + 1][k] = temp[i][j][k];

            }
            col += 2;
        }
        row += 2;
    }
 }
//______________________________________________________________

void darkenAndLighten(){
    char x ;
    cout << "(d)arken or (l)ighten ? ";
    cin >> x;
    if (x== 'd')
    {
        for (int i = 0 ; i < SIZE; i++){
            for(int j = 0 ; j < SIZE ; j++){
                for (int k = 0 ; k < 3 ; k++)
                    image[i][j][k] /= 2;
            }
        }
    }
    else
    {
        for (int i = 0 ; i < SIZE; i++){
            for(int j = 0 ; j < SIZE ; j++){
                for (int k = 0 ; k < 3 ; k++)
                    image[i][j][k] = (image[i][j][k] + 255)/2 ;
            }
        }
    }

}
//____________________________________________________
void merge(){
    cout << "enter the file's name: ";
    unsigned char image2 [SIZE][SIZE][RGB];
    unsigned char temp [SIZE][SIZE][RGB];
    char imageFileName[100];
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);
    for (int i = 0; i <= SIZE; i++){
        for(int j = 0; j <= SIZE; j++){
            for (int k = 0 ; k < RGB; k++) {
                temp[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
                image[i][j][k] = temp[i][j][k];
            }

        }
    }
}
//_________________________________________________________________________
void shrink () {
    cout << "please enter the value you want to shrink with from the list[1/2,1/3,1/4]\n";
    string shrink_value;
    cin >> shrink_value;
    if (shrink_value == "1/2") {
        int x = 0;
        for (int i = 0; i < SIZE; i += 2) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0 ; k < RGB ;k++) {
                    image[x][y][k] = ((image[i][j][k] + image[i + 1][j] [k] + image[i][j + 1] [k] + image[i + 1][j + 1] [k]) / 4);

                }
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0 ; k < RGB; k++){
                    if (i >= (SIZE / 2) || j >= (SIZE / 2)) {
                        image[i][j][k] = SIZE - 1;
                    }
                }
            }
        }
    }
    else if (shrink_value == "1/3"){
        int x = 0;
        for (int i = 0; i < SIZE; i += 3) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 3) {
                for (int k = 0 ;k < RGB ; k++ ) {
                    image[x][y][k] = (
                            (image[i][j][k] + image[i + 1][j][k] + image[i][j + 1][k] + image[i + 1][j + 1][k] + image[i][j + 2] [k]+
                             image[i + 2][j][k] + image[i + 2][i + 2] [k] + image[i + 1][j + 2][k] + image[i + 2][j + 1][k]) / 9);

                }
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for (int k = 0 ; k < RGB ; k++) {
                    if (i >= (SIZE / 3) || j >= (SIZE / 3)) {
                        image[i][j][k] = SIZE - 1;
                    }
                }
            }
        }
    }else if (shrink_value == "1/4"){
        int x = 0;
        for (int i = 0; i < SIZE; i += 4) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 4) {
                for (int k = 0 ; k < RGB ; k++) {
                    image[x][y][k] = (
                            (image[i][j][k] + image[i + 1][j][k] + image[i][j + 1][k] + image[i + 1][j + 1][k] + image[i][j + 2][k] +
                             image[i + 2][j][k] + image[i + 2][i + 2][k] + image[i + 1][j + 2][k] + image[i + 2][j + 1][k] +
                             image[i + 3][j][k] + image[i][j + 3][k] + image[i + 1][j + 3][k] + image[i + 3][j + 1][k] +
                             image[i + 3][j + 2][k] + image[i + 2][j + 3][k]) / 16);

                }
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0 ; k<RGB; k++){
                    if (i >= (SIZE / 4) || j >= (SIZE / 4)) {
                        image[i][j][k] = SIZE - 1;
                    }
                }
            }
        }
    }
}
//-------------------------------------------
// divide image to corrspond quarter and fill the image given
void divideImage(int quarter, unsigned char newImage[][SIZE / 2][RGB]) {
    int startRow, endRow, startCol, endCol;

    // define every quarter by start and end of row and col
    startRow = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
    endRow = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
    startCol = quarter == 1 || quarter == 3 ? 0 : SIZE / 2;
    endCol = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE;


    // fill given image
    for (int i = startRow, row = 0; i < endRow; i++) {
        for (int j = startCol, col = 0; j < endCol; j++) {
            for (int k = 0 ; k < RGB ; k++) {
                newImage[row][col][k] = image[i][j][k];
            }
            col++;
        }
        row++;
    }
}
//------------------------------------------------------------------------------
void shuffle() {

    // order of suffle
    int seq[4];

    // get seqaunce from user
    cout << "New sequence of quarters ? ";
    for (int i = 0; i < 4; i++) {
        cin >> seq[i];
        if (seq[i] > 4 || seq[i] < 1) {
            cout << "reject\n";
            return;
        }
    }

    // all quarters of image
    vector<unsigned char[SIZE / 2][SIZE / 2][RGB]>quarterImages(4);

    // get quarters of image
    for (int i = 0; i < quarterImages.size(); i++) {
        divideImage(seq[i], quarterImages[i]);
    }

    int row, col;
    for (int i = 0; i < 4; i++) {

        // avoid overflow
        row = i == 0 || i == 1 ? 0 : SIZE / 2;

        //fiil image with quarter in order
        for (int j = 0; j < SIZE / 2; j++) {

            // avoid overflow
            col = i == 0 || i == 2 ? 0 : SIZE / 2;

            for (int k = 0; k < SIZE / 2; k++) {
                for (int n = 0 ; n <RGB; n++)
                image[row][col][n] = quarterImages[i][j][k][n];
                col++;
            }
            row++;
        }
    }
}


