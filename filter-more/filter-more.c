#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // take of average red, green, and blue values
            float blue = image[i][j].rgbtBlue, green = image[i][j].rgbtGreen, red = image[i][j].rgbtRed;
            int avg = round((blue + green + red) / 3);

            // set pixel values to avg
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // find mid-point of image
    int half = width % 2 != 0 ? round(width / 2) : width / 2;
    // create variable for last pixel in a row
    int last = width - 1;

    // for each row for entire height
    for (int i = 0; i < height; i++)
    {
        // for each column for first half of image
        for (int j = 0; j < half; j++)
        {
            // create buffer for swapping values
            RGBTRIPLE buffer[height][width];
            // copy pixel into buffer
            buffer[i][j] = image[i][j];
            // replace pixel [i][j] with its mirrored pixel in second half (width - j)
            image[i][j] = image[i][last - j];
            // replace mirrored pixel in second half with [i][j]
            image[i][last - j] = buffer[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy original image
    RGBTRIPLE original_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    // modify image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // create kernel for each pixel
            RGBTRIPLE kernel[3][3];
            // clear kernel memory
            for (int r = 0; r < 3; r++)
            {
                for (int s = 0; s < 3; s++)
                {
                    kernel[r][s].rgbtBlue = 0;
                    kernel[r][s].rgbtGreen = 0;
                    kernel[r][s].rgbtRed = 0;
                }
            }

            // populate kernel for each pixel
            float count = 0;
            if (i != 0 && j != 0)
            {
                kernel[0][0] = original_image[i - 1][j - 1];
                count++;
            };
            if (i != 0)
            {
                kernel[0][1] = original_image[i - 1][j];
                count++;
            };
            if (i != 0 && j != width - 1)
            {
                kernel[0][2] = original_image[i - 1][j + 1];
                count++;
            };
            if (j != 0)
            {
                kernel[1][0] = original_image[i][j - 1];
                count++;
            };
            kernel[1][1] = original_image[i][j];
            count++;
            if (j != width - 1)
            {
                kernel[1][2] = original_image[i][j + 1];
                count++;
            };
            if (i != height - 1 && j != 0)
            {
                kernel[2][0] = original_image[i + 1][j - 1];
                count++;
            };
            if (i != height - 1)
            {
                kernel[2][1] = original_image[i + 1][j];
                count++;
            };
            if (i != height - 1 && j != width - 1)
            {
                kernel[2][2] = original_image[i + 1][j + 1];
                count++;
            };

            // create variables for color sums
            float total_blue = 0;
            float total_green = 0;
            float total_red = 0;

            // add totals via kernel array as index
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    total_blue += kernel[k][l].rgbtBlue;
                    total_green += kernel[k][l].rgbtGreen;
                    total_red += kernel[k][l].rgbtRed;
                }
            }

            // update pixel
            image[i][j].rgbtBlue = round(total_blue / count);
            image[i][j].rgbtGreen = round(total_green / count);
            image[i][j].rgbtRed = round(total_red / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy original image
    RGBTRIPLE original_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    // modify image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // create original kernel for each pixel and clear memory
            RGBTRIPLE kernel[3][3];
            for (int r = 0; r < 3; r++)
            {
                for (int s = 0; s < 3; s++)
                {
                    kernel[r][s].rgbtBlue = 0;
                    kernel[r][s].rgbtGreen = 0;
                    kernel[r][s].rgbtRed = 0;
                }
            }

            // populate original kernel for each pixel
            if (i != 0 && j != 0)
            {
                kernel[0][0] = original_image[i - 1][j - 1];
            };
            if (i != 0)
            {
                kernel[0][1] = original_image[i - 1][j];
            };
            if (i != 0 && j != width - 1)
            {
                kernel[0][2] = original_image[i - 1][j + 1];
            };
            if (j != 0)
            {
                kernel[1][0] = original_image[i][j - 1];
            };
            kernel[1][1] = original_image[i][j];
            if (j != width - 1)
            {
                kernel[1][2] = original_image[i][j + 1];
            };
            if (i != height - 1 && j != 0)
            {
                kernel[2][0] = original_image[i + 1][j - 1];
            };
            if (i != height - 1)
            {
                kernel[2][1] = original_image[i + 1][j];
            };
            if (i != height - 1 && j != width - 1)
            {
                kernel[2][2] = original_image[i + 1][j + 1];
            };

            // create Gx kernel
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

            // create Gy kernel
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // create variables for products/sums
            int total_blue = 0;
            int total_green = 0;
            int total_red = 0;
            int sumX_blue = 0;
            int sumX_green = 0;
            int sumX_red = 0;
            int sumY_blue = 0;
            int sumY_green = 0;
            int sumY_red = 0;

            // multiply each original kernel value by corresponding Gx value
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sumX_blue += round(kernel[k][l].rgbtBlue * Gx[k][l]);
                    sumX_green += round(kernel[k][l].rgbtGreen * Gx[k][l]);
                    sumX_red += round(kernel[k][l].rgbtRed * Gx[k][l]);
                }
            }

            // multiply each original kernel value by corresponding Gy value
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sumY_blue += round(kernel[k][l].rgbtBlue * Gy[k][l]);
                    sumY_green += round(kernel[k][l].rgbtGreen * Gy[k][l]);
                    sumY_red += round(kernel[k][l].rgbtRed * Gy[k][l]);
                }
            }

            // compute totals -- square root of Gx² + Gy²
            total_blue = round(sqrt((sumX_blue * sumX_blue) + (sumY_blue * sumY_blue)));
            total_green = round(sqrt((sumX_green * sumX_green) + (sumY_green * sumY_green)));
            total_red = round(sqrt((sumX_red * sumX_red) + (sumY_red * sumY_red)));

            image[i][j].rgbtBlue = total_blue > 255 ? 255 : total_blue;
            image[i][j].rgbtGreen = total_green > 255 ? 255 : total_green;
            image[i][j].rgbtRed = total_red > 255 ? 255 : total_red;
        }
    }
    return;
}