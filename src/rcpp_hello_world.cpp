
#include <iostream>
#include <Rcpp.h>
#include "libattopng.h"
using namespace Rcpp;

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

// [[Rcpp::export]]
void createPNG(const Rcpp::IntegerMatrix & mat, const CharacterVector & toFilename) {

	int qntLine = mat.nrow(); //R,G,B,A para cada pixel.
	int qntCol = mat.ncol();
	libattopng_t* png = libattopng_new(qntCol, qntLine, PNG_RGBA);

    int x, y;
	
	for (x = 0; x < qntCol; x++) {
		for (y = 0; y < qntLine; y++) {
			libattopng_set_pixel(png, x, y, mat(x, y));
		}
	}
    libattopng_save(png, (Rcpp::as<std::string>(toFilename)).c_str());
    libattopng_destroy(png);


    /*CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;*/

    return;
}

// [[Rcpp::export]]
Rcpp::List intToRGBA(const int a1) {
int mask = 0x000000FF;
int rgba[4];
for (int i = 3; i >= 0; i--) {
rgba[3 - i] = ((a1 >> i * 8) & mask);
}
return Rcpp::List::create(rgba[0], rgba[1], rgba[2], rgba[3]);
}

// [[Rcpp::export]]
int convertFloat(const float a1) {
union sameNum {
 float f;
 unsigned int i;
};
sameNum num;
num.f = a1;
return num.i;
}