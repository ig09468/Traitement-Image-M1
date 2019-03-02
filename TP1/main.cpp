#include <iostream>

using namespace std;

#include "opencv.hpp"

using namespace cv;


void creationImage(int rows, int cols){

    Mat img = Mat(rows,cols, CV_8U);
    for(int row = 0 ; row < img.rows ; row++){
        for(int col = 0 ; col < img.cols ; col++){
            img.at<uchar>(row,col)=row;
        }
    }

    Mat img2 = Mat(rows,cols, CV_8U);
    for(int row = 0 ; row < img2.rows ; row++){
        for(int col = 0 ; col < img2.cols ; col++){
            img2.at<uchar>(row,col)=col;
        }
    }

    Mat img3 = Mat(rows,cols, CV_8U);
    int color=0;
    for(int row = 0 ; row < img3.rows ; row++){
        for(int col = 0 ; col < img3.cols ; col++){
            img3.at<uchar>(row,col)=(row+col)/2;
        }
    }

    Mat img4 = Mat(rows,cols, CV_8U);
    for(int row = 0 ; row < img4.rows ; row++){
        for(int col = 0 ; col < img4.cols ; col++){
            img4.at<uchar>(row,col)=rand()%256;
        }
    }

    imshow("Img1",img);
    imshow("Img2",img2);
    imshow("Img3",img3);
    imshow("Img4",img4);
    waitKey(0);
}


void creationMorpion(int rows, int cols){
    Mat img = Mat(rows,cols, CV_8U,255);

    line(img,Point(0,100),Point(300,100), 0, 1, 8, 0);
    line(img,Point(0,200),Point(300,200),0,1,8,0);
    line(img,Point(100,0),Point(100,300),0,1,8,0);
    line(img,Point(200,0),Point(200,300),0,1,8,0);
    circle(img,Point(50,50),45,0,1,8,0);
    circle(img,Point(250,50),45,0,1,8,0);
    line(img,Point(110,10),Point(190,90),0,1,8,0);
    line(img,Point(190,10),Point(110,90),0,1,8,0);

    imshow("Morpion",img);
    waitKey(0);

}


void leneaThres(string src){

    Mat img = imread(src, CV_8U);
    imshow("Lena", img);
    Mat img2;
    threshold(img,img2,128,255,THRESH_BINARY);

    imshow("Lena2",img2);
    waitKey(0);

}

void histoLena(string src){
    Mat img = imread(src, CV_8U);
    imshow("Lena", img);
    Mat histogram;
    int channels[] = { 0 };
    int histSize[] = { 256 };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };

    calcHist(&img, 1, channels, Mat(), histogram, 1, histSize, ranges, true, false);
    imshow("Histogramme", histogram);
    waitKey(0);
}

int main() {

    //creationImage(256,256);
    //creationMorpion(300,300);
    //leneaThres("/home/meynadier/CLionProjects/TP1/len.jpg");
    histoLena("/home/meynadier/CLionProjects/TP1/len.jpg");
    return 0;
}

