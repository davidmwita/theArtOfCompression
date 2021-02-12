
#include "stats.h"

stats::stats(PNG & im) {

// YOUR CODE HERE!!

	unsigned int width  = im.width();
	unsigned int height = im.height();

	for (unsigned int y = 0; y < height; y++) {
		vector< long > reds;
		vector< long > greens;
		vector< long > blues;

		vector< long > redsq;
		vector< long > greensq;
		vector< long > bluesq;

		for (unsigned int x = 0; x < width; x++) {

			RGBAPixel * pixel = im.getPixel(x, y);

			if (x) {
				if (y) {
					reds.push_back(sumRed[y-1][x] + reds[x-1] - sumRed[y-1][x-1] + pixel->r);
					greens.push_back(sumGreen[y-1][x] + greens[x-1] - sumGreen[y-1][x-1] + pixel->g);
					blues.push_back(sumBlue[y-1][x] + blues[x-1] - sumBlue[y-1][x-1] + pixel->b);

					redsq.push_back(sumsqRed[y-1][x] + redsq[x-1] - sumsqRed[y-1][x-1] + (pixel->r * pixel->r));
					greensq.push_back(sumsqGreen[y-1][x] + greensq[x-1] - sumsqGreen[y-1][x-1] + (pixel->g * pixel->g));
				  bluesq.push_back(sumsqBlue[y-1][x] + bluesq[x-1] - sumsqBlue[y-1][x-1] + (pixel->b * pixel->b));
				} else {
					reds.push_back(reds[x-1] + pixel->r);
					greens.push_back(greens[x-1] + pixel->g);
					blues.push_back(blues[x-1] + pixel->b);

					redsq.push_back(redsq[x-1] +(pixel->r * pixel->r));
					greensq.push_back(greensq[x-1] + (pixel->g * pixel->g));
					bluesq.push_back(bluesq[x-1] + (pixel->b * pixel->b));
				}
			} else {
				if (y) {
					reds.push_back(sumRed[y-1][x] + pixel->r);
					greens.push_back(sumGreen[y-1][x] + pixel->g);
					blues.push_back(sumBlue[y-1][x] + pixel->b);

					redsq.push_back(sumsqRed[y-1][x] + (pixel->r * pixel->r));
					greensq.push_back(sumsqGreen[y-1][x] + (pixel->g * pixel->g));
					bluesq.push_back(sumsqBlue[y-1][x] + (pixel->b * pixel->b));
				} else {
					reds.push_back(pixel->r);
					greens.push_back(pixel->g);
					blues.push_back(pixel->b);

					redsq.push_back((pixel->r * pixel->r));
					greensq.push_back((pixel->g * pixel->g));
					bluesq.push_back((pixel->b * pixel->b));
				}
			}

		}

		sumRed.push_back(reds);
		sumGreen.push_back(greens);
		sumBlue.push_back(blues);

		sumsqRed.push_back(redsq);
		sumsqGreen.push_back(greensq);
		sumsqBlue.push_back(bluesq);
	}

	// for (unsigned int y = 0; y < height; y++) {
	// 	for (unsigned int x = 0; x < width; x++) {
	// 		std::cout << "sumRed[" << y << "][" << x << "] == " << sumRed[y][x] << std::endl;
	// 		std::cout << "sumGreen[" << y << "][" << x << "] == " << sumGreen[y][x] << std::endl;
	// 		std::cout << "sumBlue[" << y << "][" << x << "] == " << sumBlue[y][x] << std::endl << std::endl;
	// 	}
	// }

}

// in all, specify y then x -> sumRed[lr.second][lr.first]

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

	if (channel == 'r') {
		if (ul.first == 0) {
			if (ul.second == 0) return sumRed[lr.second][lr.first];
			return sumRed[lr.second][lr.first] - sumRed[ul.second - 1][lr.first];
		} else if (ul.second == 0) {
			return sumRed[lr.second][lr.first] - sumRed[lr.second][ul.first - 1];
		} else {
			return sumRed[lr.second][lr.first] - sumRed[ul.second - 1][lr.first] -
			sumRed[lr.second][ul.first - 1] + sumRed[ul.second - 1][ul.first - 1];
		}
	}

	if (channel == 'g') {
		if (ul.first == 0) {
			if (ul.second == 0) return sumGreen[lr.second][lr.first];
			return sumGreen[lr.second][lr.first] - sumGreen[ul.second - 1][lr.first];
		} else if (ul.second == 0) {
			return sumGreen[lr.second][lr.first] - sumGreen[lr.second][ul.first - 1];
		} else {
			return sumGreen[lr.second][lr.first] - sumGreen[ul.second - 1][lr.first] -
			sumGreen[lr.second][ul.first - 1] + sumGreen[ul.second - 1][ul.first - 1];
		}
	}

	if (channel == 'b') {
		if (ul.first == 0) {
			if (ul.second == 0) return sumBlue[lr.second][lr.first];
			return sumBlue[lr.second][lr.first] - sumBlue[ul.second - 1][lr.first];
		} else if (ul.second == 0) {
			return sumBlue[lr.second][lr.first] - sumBlue[lr.second][ul.first - 1];
		} else {
			return sumBlue[lr.second][lr.first] - sumBlue[ul.second - 1][lr.first] -
			sumBlue[lr.second][ul.first - 1] + sumBlue[ul.second - 1][ul.first - 1];
		}
	}


	return -1l;

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
		if (channel == 'r') {
			if (ul.first == 0) {
				if (ul.second == 0) return sumsqRed[lr.second][lr.first];
				return sumsqRed[lr.second][lr.first] - sumsqRed[ul.second - 1][lr.first];
			} else if (ul.second == 0) {
				return sumsqRed[lr.second][lr.first] - sumsqRed[lr.second][ul.first - 1];
			} else {
				return sumsqRed[lr.second][lr.first] - sumsqRed[ul.second - 1][lr.first] -
				sumsqRed[lr.second][ul.first - 1] + sumsqRed[ul.second - 1][ul.first - 1];
			}
		}

		if (channel == 'g') {
			if (ul.first == 0) {
				if (ul.second == 0) return sumsqGreen[lr.second][lr.first];
				return sumsqGreen[lr.second][lr.first] - sumsqGreen[ul.second - 1][lr.first];
			} else if (ul.second == 0) {
				return sumsqGreen[lr.second][lr.first] - sumsqGreen[lr.second][ul.first - 1];
			} else {
				return sumsqGreen[lr.second][lr.first] - sumsqGreen[ul.second - 1][lr.first] -
				sumsqGreen[lr.second][ul.first - 1] + sumsqGreen[ul.second - 1][ul.first - 1];
			}
		}

		if (channel == 'b') {
			if (ul.first == 0) {
				if (ul.second == 0) return sumsqBlue[lr.second][lr.first];
				return sumsqBlue[lr.second][lr.first] - sumsqBlue[ul.second - 1][lr.first];
			} else if (ul.second == 0) {
				return sumsqBlue[lr.second][lr.first] - sumsqBlue[lr.second][ul.first - 1];
			} else {
				return sumsqBlue[lr.second][lr.first] - sumsqBlue[ul.second - 1][lr.first] -
				sumsqBlue[lr.second][ul.first - 1] + sumsqBlue[ul.second - 1][ul.first - 1];
			}
		}


		return -1l;
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
	int width  = lr.first + 1  - ul.first;
	int height = lr.second + 1 - ul.second;

	return height * width;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!! - compute separately for rgb then sum to get score
	long area = rectArea(ul, lr);

	long sumR = getSum('r', ul, lr);
	long sumsqR = getSumSq('r', ul, lr);
	long ssdR = sumsqR - (pow(sumR, 2)/area);

	long sumG = getSum('g', ul, lr);
	long sumsqG = getSumSq('g', ul, lr);
	long ssdG = sumsqG - (pow(sumG, 2)/area);

	long sumB = getSum('b', ul, lr);
	long sumsqB = getSumSq('b', ul, lr);
	long ssdB = sumsqB - (pow(sumB, 2)/area);

	return ssdR + ssdG + ssdB;

}

RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
	long area = rectArea(ul, lr);

	long sumR = getSum('r', ul, lr);
	long sumG = getSum('g', ul, lr);
	long sumB = getSum('b', ul, lr);

	return RGBAPixel(sumR/area, sumG/area, sumB/area);

}

//
// #include <cmath>
// #include "stats.h"
// 
// stats::stats(PNG & im){
//
// 	sumRed.resize(im.height());
// 	sumGreen.resize(im.height());
// 	sumBlue.resize(im.height());
// 	sumsqRed.resize(im.height());
// 	sumsqGreen.resize(im.height());
// 	sumsqBlue.resize(im.height());
//
//
// 	sumRed[0].push_back((long) im.getPixel(0,0)->r);
// 	sumGreen[0].push_back((long) im.getPixel(0,0)->g);
// 	sumBlue[0].push_back((long) im.getPixel(0,0)->b);
// 	sumsqRed[0].push_back((long) pow(im.getPixel(0,0)->r, 2));
// 	sumsqGreen[0].push_back((long) pow(im.getPixel(0,0)->g, 2));
// 	sumsqBlue[0].push_back((long) pow(im.getPixel(0,0)->b, 2));
//
// 	for (unsigned int y = 0; y < im.height(); y++){
// 		unsigned long rowRedSum = 0;
// 		unsigned long rowRedSumSq = 0;
// 		unsigned long rowGreenSum = 0;
// 		unsigned long rowGreenSumSq = 0;
// 		unsigned long rowBlueSum = 0;
// 		unsigned long rowBlueSumSq = 0;
//
// 		sumRed[y].resize(im.width());
// 		sumGreen[y].resize(im.width());
// 		sumBlue[y].resize(im.width());
// 		sumsqRed[y].resize(im.width());
// 		sumsqGreen[y].resize(im.width());
// 		sumsqBlue[y].resize(im.width());
//
// 		for (unsigned int x = 0; x < im.width(); x++){
// 			// if(!(x == 0 && y == 0)){
// 				rowRedSum += im.getPixel(x,y)->r;
// 				rowRedSumSq += pow(im.getPixel(x,y)->r,2);
// 				rowGreenSum += im.getPixel(x,y)->g;
// 				rowGreenSumSq += pow(im.getPixel(x,y)->g,2);
// 				rowBlueSum += im.getPixel(x,y)->b;
// 				rowBlueSumSq += pow(im.getPixel(x,y)->b,2);
//
// 				if(y == 0){
// 					sumRed[y][x] = rowRedSum;
// 					sumGreen[y][x] = rowGreenSum;
// 					sumBlue[y][x] = rowBlueSum;
// 					sumsqRed[y][x] = rowRedSumSq;
// 					sumsqGreen[y][x] = rowGreenSumSq;
// 					sumsqBlue[y][x] = rowBlueSumSq;
// 				}else{
// 					sumRed[y][x] = rowRedSum + sumRed[y-1][x];
// 					sumGreen[y][x] = rowGreenSum + sumGreen[y-1][x];
// 					sumBlue[y][x] = rowBlueSum + sumBlue[y-1][x];
// 					sumsqRed[y][x] = rowRedSumSq + sumsqRed[y-1][x];
// 					sumsqGreen[y][x] = rowGreenSumSq + sumsqGreen[y-1][x];
// 					sumsqBlue[y][x] = rowBlueSumSq + sumsqBlue[y-1][x];
// 				}
// 			// }
// 		}
// 	}
// 	// std::printf("Height: %d, Width: %d\n", im.height(), im.width());
// 	// std::printf("TEST: pixels: (0,0): %d\n              (1,0): %d\n              (0,1): %d\n              (1,1): %d\n      values: %ld\n              %ld\n              %ld\n              %ld\n", im.getPixel(0,0)->r,im.getPixel(1,0)->r,im.getPixel(0,1)->r,im.getPixel(1,1)->r, sumRed[0][0], sumRed[0][1], sumRed[1][0], sumRed[1][1]);
// 	// std::printf("Coulour at:    (0,0): %d\n              (1,0): %d\n              (0,1): %d\n              (1,1): %d\n", getAvg(pair<int,int>(0,0), pair<int,int>(0,0)).r, getAvg(pair<int,int>(1,0), pair<int,int>(1,0)).r, getAvg(pair<int,int>(0,1), pair<int,int>(0,1)).r, getAvg(pair<int,int>(1,1), pair<int,int>(1,1)).r);
//
// }
//
// long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
//
// // YOUR CODE HERE!!
// //THIS IS AN ISSUE, FIX LATER
// 	// if(ul.first > lr.first||ul.second > lr.second)
// 		// return 0;
// 	// else if(ul.first < 0|| ul.second < 0)
// 		// return 0;
//
//
// 	// long left;// = getSum(channel, pair<int,int>(0,0), pair<int,int>(ul.first, lr.second));
// 	// long up;// = getSum(channel, pair<int,int>(ul.first,0), pair<int,int>(lr.first, ul.second));
//
// 	// if(ul.first == ul.second == 0){
// 		// left = 0;
// 		// up = 0;
// 	// }else if(ul.first == 0){
// 		// left = 0;
// 		// up = getSum(channel, pair<int,int>(0,0), pair<int,int>(lr.first, ul.second - 1));
// 	// }else if(ul.second == 0){
// 		// up = 0;
// 		// left = getSum(channel, pair<int,int>(0,0), pair<int,int>(ul.first - 1, lr.second));
// 	// }
//
//
//
// 	// if( channel == 'r')
// 		// return sumRed[lr.second][lr.first] - (up + left);
// 	// else if (channel == 'g')
// 		// return sumGreen[lr.second][lr.first] - (up + left);
// 	// else if (channel == 'b')
// 		// return sumBlue[lr.second][lr.first] - (up + left);
// 	// else
// 		// return 0;
//
// 	if( channel == 'r')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumRed[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumRed[lr.second][lr.first] - sumRed[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumRed[lr.second][lr.first] - sumRed[ul.second-1][lr.first];
// 		else
// 			return sumRed[lr.second][lr.first] - sumRed[lr.second][ul.first-1] - sumRed[ul.second-1][lr.first] + sumRed[ul.second-1][ul.first-1];
// 	else if (channel == 'g')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumGreen[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumGreen[lr.second][lr.first] - sumGreen[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumGreen[lr.second][lr.first] - sumGreen[ul.second-1][lr.first];
// 		else
// 			return sumGreen[lr.second][lr.first] - sumGreen[lr.second][ul.first-1] - sumGreen[ul.second-1][lr.first] + sumGreen[ul.second-1][ul.first-1];
// 	else if (channel == 'b')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumBlue[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumBlue[lr.second][lr.first] - sumBlue[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumBlue[lr.second][lr.first] - sumBlue[ul.second-1][lr.first];
// 		else
// 			return sumBlue[lr.second][lr.first] - sumBlue[lr.second][ul.first-1] - sumBlue[ul.second-1][lr.first] + sumBlue[ul.second-1][ul.first-1];
// 	else
// 		return 0;
//
// }
//
// long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
//
// // YOUR CODE HERE!!
// 	// if(ul.first > lr.first||ul.second > lr.second)
// 		// return 0;
// 	// else if(ul.first < 0|| ul.second < 0)
// 		// return 0;
//
//
// 	// long left;// = getSum(channel, pair<int,int>(0,0), pair<int,int>(ul.first, lr.second));
// 	// long up;// = getSum(channel, pair<int,int>(ul.first,0), pair<int,int>(lr.first, ul.second));
//
// 	// if(ul.first == ul.second == 0){
// 		// left = 0;
// 		// up = 0;
// 	// }else if(ul.first == 0){
// 		// left = 0;
// 		// up = getSumSq(channel, pair<int,int>(0,0), pair<int,int>(lr.first, ul.second - 1));
// 	// }else if(ul.second == 0){
// 		// up = 0;
// 		// left = getSumSq(channel, pair<int,int>(0,0), pair<int,int>(ul.first - 1, lr.second));
// 	// }
//
//
//
// 	// if( channel == 'r')
// 		// return sumsqRed[lr.second][lr.first] - (up + left);
// 	// else if (channel == 'g')
// 		// return sumsqGreen[lr.second][lr.first] - (up + left);
// 	// else if (channel == 'b')
// 		// return sumsqBlue[lr.second][lr.first] - (up + left);
// 	// else
// 		// return 0;
//
// 	if( channel == 'r')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumsqRed[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumsqRed[lr.second][lr.first] - sumsqRed[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumsqRed[lr.second][lr.first] - sumsqRed[ul.second-1][lr.first];
// 		else
// 			return sumsqRed[lr.second][lr.first] - sumsqRed[lr.second][ul.first-1] - sumsqRed[ul.second-1][lr.first] + sumsqRed[ul.second-1][ul.first-1];
// 	else if (channel == 'g')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumsqGreen[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumsqGreen[lr.second][lr.first] - sumsqGreen[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumsqGreen[lr.second][lr.first] - sumsqGreen[ul.second-1][lr.first];
// 		else
// 			return sumsqGreen[lr.second][lr.first] - sumsqGreen[lr.second][ul.first-1] - sumsqGreen[ul.second-1][lr.first] + sumsqGreen[ul.second-1][ul.first-1];
// 	else if (channel == 'b')
// 		if(ul.second == 0 && ul.first == 0)
// 			return sumsqBlue[lr.second][lr.first];
// 		else if(ul.second == 0)
// 			return sumsqBlue[lr.second][lr.first] - sumsqBlue[lr.second][ul.first-1];
// 		else if(ul.first == 0)
// 			return sumsqBlue[lr.second][lr.first] - sumsqBlue[ul.second-1][lr.first];
// 		else
// 			return sumsqBlue[lr.second][lr.first] - sumsqBlue[lr.second][ul.first-1] - sumsqBlue[ul.second-1][lr.first] + sumsqBlue[ul.second-1][ul.first-1];
// 	else
// 		return 0;
//
// }
//
// long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
//
// // YOUR CODE HERE!!
// 	return (lr.first - ul.first+1)*(lr.second - ul.second+1);
//
// }
//
// // given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// long stats::getScore(pair<int,int> ul, pair<int,int> lr){
//
// // YOUR CODE HERE!!
//
// 	unsigned long red = (unsigned long) getSumSq('r', ul, lr) - (unsigned long) (pow(getSum('r', ul, lr), 2)/rectArea(ul,lr));
// 	unsigned long green = (unsigned long) getSumSq('g', ul, lr) - (unsigned long) (pow(getSum('g', ul, lr), 2)/rectArea(ul,lr));
// 	unsigned long blue = (unsigned long) getSumSq('b', ul, lr) - (unsigned long) (pow(getSum('b', ul, lr), 2)/rectArea(ul,lr));
// 	return red + green + blue;
//
// }
//
// RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
//
// // YOUR CODE HERE!!
// 	// if (ul == lr)
// 	// printf("red: %ld, area: %ld\n", getSum('r', ul, lr), rectArea(ul,lr));
// 	int red = getSum('r', ul,lr)/rectArea(ul,lr);
// 	int green = getSum('g', ul,lr)/rectArea(ul,lr);
// 	int blue = getSum('b', ul,lr)/rectArea(ul,lr);
//
// 	return RGBAPixel(red, green, blue);
//
// }
