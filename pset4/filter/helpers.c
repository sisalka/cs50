#include "helpers.h"
c
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0; i < height; i++ ) {
        for (int j = 0; j < width; j++ ) {
            int shade_of_grey = (int)(0.11*image[i][j].rgbtBlue + 0.59*image[i][j].rgbtGreen + 0.3*image[i][j].rgbtRed);
            image[i][j].rgbtBlue = shade_of_grey;
            image[i][j].rgbtGreen = shade_of_grey;
            image[i][j].rgbtRed = shade_of_grey;
        }
    }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0; i < height; i++ ) {
        for (int j = 0; j < width; j++ ) {
            int tr = (int)(0.189*image[i][j].rgbtBlue + 0.769*image[i][j].rgbtGreen + 0.393*image[i][j].rgbtRed);
            int tg = (int)(0.168*image[i][j].rgbtBlue + 0.686*image[i][j].rgbtGreen + 0.349*image[i][j].rgbtRed);
            int tb = (int)(0.131*image[i][j].rgbtBlue + 0.534*image[i][j].rgbtGreen + 0.272*image[i][j].rgbtRed);

            if (tr>255){
                image[i][j].rgbtRed = 255;
            }
            else {
                image[i][j].rgbtRed = tr;
            }

            if (tg>255){
                image[i][j].rgbtGreen = 255;
            }
            else {
                image[i][j].rgbtGreen = tg;
            }

            if (tb>255){
                image[i][j].rgbtBlue = 255;
            }
            else {
                image[i][j].rgbtBlue = tb;
            }

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   for (int i = 0; i < height/2; i++) {
            for (int j = 0; j < width; j++) {
                int tempBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue=image[i][width-1-j].rgbtBlue;
                image[i][width-1-j].rgbtBlue=tempBlue;

                int tempRed = image[i][j].rgbtRed;
                image[i][j].rgbtRed=image[i][width-1-j].rgbtRed;
                image[i][width-1-j].rgbtRed=tempRed;

                int tempGreen = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen=image[i][width-1-j].rgbtGreen;
                image[i][width-1-j].rgbtGreen=tempGreen;
            }
    }
}

// Blur imageclear

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {   //.rgbtBlue
            //Top row of image
            if(i == 0)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4;
                else
                    sum = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
            }
            //Bottom row of image
            else if(i == height - 1)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4;
                else
                    sum = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6;
            }
            //Left side of image (excluding top or bottom row)
            else if(j == 0)
                sum = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
            //Right side of image (excluding top or bottom row)
            else if(j == width - 1)
                sum = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;
            else {
                sum = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
            }
            image[i][j].rgbtBlue = (unsigned char)sum;

            //.rgbtGreen
            //Top row of image
            if(i == 0)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4;
                else
                    sum = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
            }
            //Bottom row of image
            else if(i == height - 1)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4;
                else
                    sum = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6;
            }
            //Left side of image (excluding top or bottom row)
            else if(j == 0)
                sum = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
            //Right side of image (excluding top or bottom row)
            else if(j == width - 1)
                sum = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;

            else {
                sum = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
            }
            image[i][j].rgbtGreen = (unsigned char)sum;

            //.rgbtRed
            //Top row of image
            if(i == 0)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4;
                else
                    sum = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
            }
            //Bottom row of image
            else if(i == height - 1)
            {
                if(j == 0)
                    sum = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4;
                else if(j == width - 1)
                    sum = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                            image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4;
                else
                    sum = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6;
            }
            //Left side of image (excluding top or bottom row)
            else if(j == 0)
                sum = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
            //Right side of image (excluding top or bottom row)
            else if(j == width - 1)
                sum = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;
            else {
                sum = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
            }
            image[i][j].rgbtRed = (unsigned char)sum;

        }
    }
}
