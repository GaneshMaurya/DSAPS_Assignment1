#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    string path = argv[1];
    Mat inputImage = imread(path, IMREAD_COLOR);
    if (inputImage.empty())
    {
        cout << "Error in opening the image.\n";
        return 1;
    }

    Mat grayImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    Mat gradX, gradY;
    Mat absGradX, absGradY;

    Sobel(grayImage, gradX, CV_16S, 1, 0, 3);
    Sobel(grayImage, gradY, CV_16S, 0, 1, 3);

    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);

    Mat energyImage;
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, energyImage);

    int imgWidth = inputImage.cols;
    int imgHeight = inputImage.rows;

    int reqWidth = stoi(argv[2]);
    int reqHeight = stoi(argv[3]);

    int reducedWidth = imgWidth - reqWidth;
    int reducedHeight = imgHeight - reqHeight;

    int **matrix = new int *[imgHeight];
    int **dp = new int *[imgHeight];
    Vec3b **colorMatrix = new Vec3b *[imgHeight];

    for (int i = 0; i < imgHeight; i++)
    {
        matrix[i] = new int[imgWidth];
        dp[i] = new int[imgWidth];
        colorMatrix[i] = new Vec3b[imgWidth];
    }

    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            matrix[i][j] = energyImage.at<uchar>(i, j);
            colorMatrix[i][j] = inputImage.at<Vec3b>(i, j);
        }
    }

    int **dupMatrix = new int *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        dupMatrix[i] = new int[imgWidth];
        for (int j = 0; j < imgWidth; j++)
        {
            dupMatrix[i][j] = matrix[i][j];
        }
    }

    while (reducedWidth > 0)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            dp[0][i] = dupMatrix[0][i];
        }

        for (int i = 1; i < imgHeight; i++)
        {
            for (int j = 0; j < imgWidth; j++)
            {
                int left = INT_MAX;
                int up = INT_MAX;
                int right = INT_MAX;
                if (i - 1 >= 0 && j - 1 >= 0)
                {
                    left = dp[i - 1][j - 1];
                }
                if (i - 1 >= 0 && j >= 0)
                {
                    up = dp[i - 1][j];
                }
                if (i - 1 >= 0 && j + 1 < imgWidth)
                {
                    right = dp[i - 1][j + 1];
                }
                dp[i][j] = dupMatrix[i][j] + min({left, up, right});
            }
        }

        int minLast = INT_MAX;
        int minInd = 0;
        for (int i = 0; i < imgWidth; i++)
        {
            if (dp[imgHeight - 1][i] < minLast)
            {
                minLast = dp[imgHeight - 1][i];
                minInd = i;
            }
        }

        int *seamIndexes = new int[imgHeight];
        seamIndexes[imgHeight - 1] = minInd;

        int j = minInd;
        for (int i = imgHeight - 1; i > 0; i--)
        {
            int left = INT_MAX;
            int up = INT_MAX;
            int right = INT_MAX;
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                left = dp[i - 1][j - 1];
            }
            if (i - 1 >= 0 && j >= 0)
            {
                up = dp[i - 1][j];
            }
            if (i - 1 >= 0 && j + 1 < imgWidth)
            {
                right = dp[i - 1][j + 1];
            }

            int temp = min({left, up, right});
            if (temp == left)
            {
                j = j - 1;
            }
            else if (temp == right)
            {
                j = j + 1;
            }

            seamIndexes[i - 1] = j;
        }

        int **newMatrix = new int *[imgHeight];
        Vec3b **newColorMatrix = new Vec3b *[imgHeight];
        for (int i = 0; i < imgHeight; i++)
        {
            newMatrix[i] = new int[imgWidth - 1];
            newColorMatrix[i] = new Vec3b[imgWidth - 1];
        }

        for (int i = 0; i < imgHeight; i++)
        {
            int k = 0;
            for (int j = 0; j < imgWidth; j++)
            {
                if (j != seamIndexes[i])
                {
                    newMatrix[i][k] = dupMatrix[i][j];
                    newColorMatrix[i][k] = colorMatrix[i][j];
                    k++;
                }
            }
        }

        for (int i = 0; i < imgHeight; i++)
        {
            delete[] dupMatrix[i];
            delete[] colorMatrix[i];
        }
        delete[] dupMatrix;
        delete[] colorMatrix;

        dupMatrix = newMatrix;
        colorMatrix = newColorMatrix;
        imgWidth--;

        delete[] seamIndexes;

        reducedWidth--;
        cout << "Width: " << reducedWidth << endl;
    }

    while (reducedHeight > 0)
    {
        for (int i = 0; i < imgHeight; i++)
        {
            dp[i][0] = dupMatrix[i][0];
        }

        for (int j = 1; j < imgWidth; j++)
        {
            for (int i = 0; i < imgHeight; i++)
            {
                int up = INT_MAX;
                int left = dp[i][j];
                int down = INT_MAX;

                if (i > 0)
                {
                    up = dp[i - 1][j];
                }

                if (i < imgHeight - 1)
                {
                    down = dp[i + 1][j];
                }
                dp[i][j] = dupMatrix[i][j] + min({up, left, down});
            }
        }

        int minLast = INT_MAX;
        int minInd = 0;
        for (int i = 0; i < imgHeight; i++)
        {
            if (dp[i][imgWidth - 1] < minLast)
            {
                minLast = dp[i][imgWidth - 1];
                minInd = i;
            }
        }

        int *seamIndexes = new int[imgWidth];
        seamIndexes[imgWidth - 1] = minInd;

        int i = minInd;
        for (int j = imgWidth - 2; j >= 0; j--)
        {
            int i = seamIndexes[j + 1];
            int up = INT_MAX;
            int left = dp[i][j];
            int down = INT_MAX;

            if (i > 0)
            {
                up = dp[i - 1][j];
            }

            if (i < imgHeight - 1)
            {
                down = dp[i + 1][j];
            }

            if (up <= left && up <= down)
            {
                seamIndexes[j] = i - 1;
            }
            else if (down <= left && down <= up)
            {
                seamIndexes[j] = i + 1;
            }
            else
            {
                seamIndexes[j] = i;
            }
        }

        int **newMatrix = new int *[imgHeight - 1];
        Vec3b **newColorMatrix = new Vec3b *[imgHeight - 1];
        for (int i = 0; i < imgHeight - 1; i++)
        {
            newMatrix[i] = new int[imgWidth];
            newColorMatrix[i] = new Vec3b[imgWidth];
        }

        for (int j = 0; j < imgWidth; j++)
        {
            int k = 0;
            for (int i = 0; i < imgHeight; i++)
            {
                if (i != seamIndexes[j])
                {
                    newMatrix[k][j] = dupMatrix[i][j];
                    newColorMatrix[k][j] = colorMatrix[i][j];
                    k++;
                }
            }
        }

        for (int i = 0; i < imgHeight; i++)
        {
            delete[] dupMatrix[i];
            delete[] colorMatrix[i];
        }
        delete[] dupMatrix;
        delete[] colorMatrix;

        dupMatrix = newMatrix;
        colorMatrix = newColorMatrix;
        imgHeight--;

        delete[] seamIndexes;

        reducedHeight--;
        cout << "Height: " << reducedHeight << endl;
    }

    Mat finalImage(imgHeight, imgWidth, CV_8UC3);
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            finalImage.at<Vec3b>(i, j) = colorMatrix[i][j];
        }
    }

    imwrite("output.jpg", finalImage);

    for (int i = 0; i < imgHeight; i++)
    {
        delete[] matrix[i];
        delete[] dp[i];
        delete[] dupMatrix[i];
        delete[] colorMatrix[i];
    }
    delete[] matrix;
    delete[] dp;
    delete[] dupMatrix;
    delete[] colorMatrix;

    return 0;
}