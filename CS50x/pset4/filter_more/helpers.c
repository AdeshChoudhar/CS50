#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each pixel
        for (int j = 0; j < width; j++)
        {
            // Calculating average and assigning same to red, green and blue attributes
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through first half of the row and swapping
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a temporary variable to store the new values of pixels
    RGBTRIPLE tmp[height][width];

    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each pixel
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (0 <= (i + k) && (i + k) < height && 0 <= (j + l) && (j + l) < width)
                    {
                        sum_red = sum_red + image[i + k][j + l].rgbtRed;
                        sum_green = sum_green + image[i + k][j + l].rgbtGreen;
                        sum_blue = sum_blue + image[i + k][j + l].rgbtBlue;
                        count++;
                    }
                }
            }
            tmp[i][j].rgbtRed = round((float)sum_red / count);
            tmp[i][j].rgbtGreen = round((float)sum_green / count);
            tmp[i][j].rgbtBlue = round((float)sum_blue / count);
        }
    }

    // Assigning values of tmp to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a temporary variable to store the new values of pixels
    RGBTRIPLE tmp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each pixel
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gy_red = 0;
            int Gx_green = 0, Gy_green = 0;
            int Gx_blue = 0, Gy_blue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (0 <= (i + k) && (i + k) < height && 0 <= (j + l) && (j + l) < width)
                    {
                        Gx_red = Gx_red + Gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        Gx_green = Gx_green + Gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        Gx_blue = Gx_blue + Gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                        Gy_red = Gy_red + Gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        Gy_green = Gy_green + Gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        Gy_blue = Gy_blue + Gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                    }
                }
            }
            
            // G = sqrt(Gx^2 + Gy^2)
            int red = round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2)));
            int green = round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2)));
            int blue = round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2)));

            // Capping out values larger than 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            tmp[i][j].rgbtRed = red;
            tmp[i][j].rgbtGreen = green;
            tmp[i][j].rgbtBlue = blue;
        }
    }

    // Copying values of temporary variable to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}
