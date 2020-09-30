#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //grey scale converter = gsc//
            float gsc = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            int gscr = round(gsc);

            image[i][j].rgbtBlue = gscr;
            image[i][j].rgbtGreen = gscr;
            image[i][j].rgbtRed = gscr;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //remove float error//
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            int sr = round(sepiaRed);
            {
                if (sr >= 255)
                {
                    sr = 255;
                }
            }

            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            int sg = round(sepiaGreen);
            {
                if (sg >= 255)
                {
                    sg = 255;
                }
            }

            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            int sb = round(sepiaBlue);
            {
                if (sb >= 255)
                {
                    sb = 255;
                }
            }

            image[i][j].rgbtRed = sr;
            image[i][j].rgbtGreen = sg;
            image[i][j].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            //swap function//
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float bred = 0.00;
            float bgreen = 0.00;
            float bblue = 0.00;
            float counter = 0.00;

            //check for pixel in height//
            for (int h = -1; h <= 1; h++)
            {
                //check for pixel in width//
                for (int k = - 1; k <= 1; k++)
                {
                    //if pixel exist add counter and apply filter//
                    if (i + h >= 0 && i + h <= height - 1 && j + k >= 0 && j + k <= width - 1)
                    {
                        counter++;

                        bred += image[i + h][j + k].rgbtRed;
                        bgreen += image[i + h][j + k].rgbtGreen;
                        bblue += image[i + h][j + k].rgbtBlue;
                    }

                }
            }

            temp[i][j].rgbtRed = round(bred / counter);
            temp[i][j].rgbtGreen = round(bgreen / counter);
            temp[i][j].rgbtBlue = round(bblue / counter);
        }
    }
    //replace original with filter//
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}