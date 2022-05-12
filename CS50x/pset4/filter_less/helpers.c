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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each pixel
        for (int j = 0; j < width; j++)
        {
            // Just applying given formulae
            int red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            // Checking if all values of colors are less than or equal to 255
            // If greater than 255, assign tham maximum value which is 255
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
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
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
    for (int i = 0; i < height; i++)
    {
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
