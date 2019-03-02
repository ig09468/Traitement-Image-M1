//
// Created by meynadier on 20/02/19.
//

#include <opencv.hpp>
#include "Filter.h"

Filter::Filter(const std::string url) {
	sourceImg=openImg(url);
}

Filter::~Filter() {

}

Filter Filter::operator =(const Filter &rhs) const{
	if(&rhs != this)
		rhs.sourceImg.copyTo(sourceImg);
}


cv::Mat Filter::openImg(std::string url){
	cv::Mat img = cv::imread(url,cv::IMREAD_COLOR);
	return img;
}

cv::Mat Filter::greyscale8U() {
	const int rowImg = sourceImg.rows;
	const int colsImg = sourceImg.cols;

	cv::Mat greyImg = cv::Mat(rowImg,colsImg,CV_8U);

	for(int rows = 0 ; rows < rowImg ; rows++){
		for(int cols = 0 ; cols < colsImg ; cols++){
			greyImg.at<uchar>(rows,cols)=(sourceImg.at<cv::Vec3b>(rows,cols)[0]+sourceImg.at<cv::Vec3b>(rows,cols)[1]+sourceImg.at<cv::Vec3b>(rows,cols)[3])/3;
		}
	}
	return greyImg;
}


cv::Mat Filter::greyscale8UC3() {
	const int rowImg = sourceImg.rows;
	const int colsImg = sourceImg.cols;

	cv::Mat greyImg = cv::Mat(rowImg,colsImg,CV_8UC3);

	for(int rows = 0 ; rows < rowImg ; rows++){
		for(int cols = 0 ; cols < colsImg ; cols++){
			greyImg.at<cv::Vec3b>(rows,cols)[0]=(sourceImg.at<cv::Vec3b>(rows,cols)[0]+sourceImg.at<cv::Vec3b>(rows,cols)[1]+sourceImg.at<cv::Vec3b>(rows,cols)[3])/3;
			greyImg.at<cv::Vec3b>(rows,cols)[1]=(sourceImg.at<cv::Vec3b>(rows,cols)[0]+sourceImg.at<cv::Vec3b>(rows,cols)[1]+sourceImg.at<cv::Vec3b>(rows,cols)[3])/3;
			greyImg.at<cv::Vec3b>(rows,cols)[2]=(sourceImg.at<cv::Vec3b>(rows,cols)[0]+sourceImg.at<cv::Vec3b>(rows,cols)[1]+sourceImg.at<cv::Vec3b>(rows,cols)[3])/3;
		}
	}
	return greyImg;
}


int Filter::blur(const int &rows, const int &cols){
	if(cols == 0 || cols == sourceImg.cols-1 || rows == 0 || rows == sourceImg.rows-1){
		return sourceImg.at<uchar>(rows,cols);
	}
	else{
		return (sourceImg.at<uchar>(rows,cols) + sourceImg.at<uchar>(rows+1,cols+1) + sourceImg.at<uchar>(rows,cols+1) + sourceImg.at<uchar>(rows+1,cols) + sourceImg.at<uchar>(rows-1,cols) + sourceImg.at<uchar>(rows,cols-1) + sourceImg.at<uchar>(rows-1,cols-1)+sourceImg.at<uchar>(rows+1,cols-1) + sourceImg.at<uchar>(rows-1,cols+1))/9;
	}
}




cv::Mat Filter::blurFilter() {
	const int rowImg = sourceImg.rows;
	const int colsImg = sourceImg.cols;
	const int type = sourceImg.type();
	cv::Mat imgBlur = cv::Mat(rowImg,colsImg,CV_8U);


	for(int rows = 0 ; rows < rowImg; rows++){
		for(int cols = 0 ; cols < colsImg ; cols++){
			imgBlur.at<uchar>(rows,cols)=blur(rows,cols);
		}
	}
	return imgBlur;
	//cv::Mat blur;
	//cv::blur(sourceImg,blur,cv::Size(50,50),cv::Point(-1,-1),cv::BORDER_DEFAULT);
	//return blur;
}

int Filter::median(int rows, int cols){
	std::vector<int> table;
	if(rows > 0 && cols > 0 ){
		table.push_back(sourceImg.at<uchar>(rows,cols));
		table.push_back(sourceImg.at<uchar>(rows,cols+1));
		table.push_back(sourceImg.at<uchar>(rows,cols-1));
		table.push_back(sourceImg.at<uchar>(rows+1,cols));
		table.push_back(sourceImg.at<uchar>(rows+1,cols-1));
		table.push_back(sourceImg.at<uchar>(rows+1,cols+1));
		table.push_back(sourceImg.at<uchar>(rows-1,cols));
		table.push_back(sourceImg.at<uchar>(rows-1,cols+1));
		table.push_back(sourceImg.at<uchar>(rows-1,cols-1));
		std::sort(table.begin(),table.end());
		return table[5];
	}
	if(rows > 0 && cols == 0){
		table.push_back(sourceImg.at<uchar>(rows,cols));
		table.push_back(sourceImg.at<uchar>(rows,cols));
		table.push_back(sourceImg.at<uchar>(rows+1,cols));
		table.push_back(sourceImg.at<uchar>(rows+1,cols));
		table.push_back(sourceImg.at<uchar>(rows-1,cols));
		table.push_back(sourceImg.at<uchar>(rows-1,cols));
		table.push_back(sourceImg.at<uchar>(rows,cols+1));
		table.push_back(sourceImg.at<uchar>(rows+1,cols+1));
		table.push_back(sourceImg.at<uchar>(rows-1,cols+1));
		std::sort(table.begin(),table.end());
		return table[5];

	} else if (cols > 0 && rows == 0) {
		table.push_back(sourceImg.at<uchar>(rows,cols));
		table.push_back(sourceImg.at<uchar>(rows,cols));
		table.push_back(sourceImg.at<uchar>(rows,cols+1));
		table.push_back(sourceImg.at<uchar>(rows,cols+1));
		table.push_back(sourceImg.at<uchar>(rows,cols-1));
		table.push_back(sourceImg.at<uchar>(rows,cols-1));
		table.push_back(sourceImg.at<uchar>(rows+1,cols));
		table.push_back(sourceImg.at<uchar>(rows+1,cols+1));
		table.push_back(sourceImg.at<uchar>(rows+1,cols-1));
		std::sort(table.begin(),table.end());
		return table[5];
	} else if(rows == 0 && cols == 0){
			table.push_back(sourceImg.at<uchar>(rows,cols));
			table.push_back(sourceImg.at<uchar>(rows,cols));
			table.push_back(sourceImg.at<uchar>(rows,cols));
			table.push_back(sourceImg.at<uchar>(rows,cols));
			table.push_back(sourceImg.at<uchar>(rows+1,cols+1));
			table.push_back(sourceImg.at<uchar>(rows+1,cols));
			table.push_back(sourceImg.at<uchar>(rows+1,cols));
			table.push_back(sourceImg.at<uchar>(rows,cols+1));
			table.push_back(sourceImg.at<uchar>(rows,cols+1));
			std::sort(table.begin(),table.end());
			return table[5];
	}
}

cv::Mat Filter::filtreMedian() {
	const int rowImg = sourceImg.rows;
	const int colsImg = sourceImg.cols;
	cv::Mat imgMedian = cv::Mat(rowImg,colsImg,CV_8U);


	for(int rows = 0 ; rows < rowImg; rows++){
		for(int cols = 0 ; cols < colsImg ; cols++){
			imgMedian.at<uchar>(rows,cols)=median(rows,cols);
		}
	}
	//cv::Mat median;
	//cv::medianBlur(sourceImg,median,27);
	return imgMedian;
}

cv::Mat Filter::filtreSobel(){
	int ddepth = CV_16S;
	cv::Mat sobel;
	cv::Sobel(sourceImg,sobel,ddepth,0,1,3,1,0,cv::BORDER_DEFAULT);
	return sobel;
}


void Filter::test (){
	cv::imshow("Origine",sourceImg);
	cv:: Mat greyscale = greyscale8U();
	cv::imshow("Greyscale8U",greyscale);
	//cv::Mat blur = blurFilter();
	//cv::imshow("Filtre Moyenneur",blur);
	cv::Mat median = filtreMedian();
	cv::imshow("Median", median);
	//cv::Mat sobel = filtreSobel(grey);

	//cv::imshow("Moyenneur",moyenneur);
	//cv::imshow("Median", median);
	//cv::imshow("Sobel",sobel);
	cv::waitKey(0);


}




