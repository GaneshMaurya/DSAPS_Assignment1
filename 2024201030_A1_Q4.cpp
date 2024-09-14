// #include <iostream>
// #include <opencv2/opencv.hpp>
// using namespace cv;
// using namespace std;

// int main(int args, char *argv[])
// {
//     string path = argv[1];
//     Mat inputImage = imread(path, IMREAD_GRAYSCALE);
//     if (inputImage.empty())
//     {
//         cout << "Error in opening the image.\n";
//         return 1;
//     }

//     Mat gradX, gradY;
//     Mat absGradX, absGradY;

//     Sobel(inputImage, gradX, CV_16S, 1, 0, 3);
//     Sobel(inputImage, gradY, CV_16S, 0, 1, 3);

//     convertScaleAbs(gradX, absGradX);
//     convertScaleAbs(gradY, absGradY);

//     Mat outputImage;
//     addWeighted(absGradX, 0.5, absGradY, 0.5, 0, outputImage);

//     // imshow("Gradient", outputImage);

//     int imgWidth = outputImage.cols;
//     int imgHeight = outputImage.rows;

//     int matrix[imgHeight][imgWidth];
//     memset(matrix, 0, sizeof(matrix));
//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             uchar pixel = outputImage.at<uchar>(i, j);
//             matrix[i][j] = (int)pixel;
//         }
//     }

//     int dp[imgHeight][imgWidth];
//     memset(dp, 0, sizeof(dp));
//     for (int i = 0; i < imgWidth; i++)
//     {
//         dp[0][i] = matrix[0][i];
//     }

//     for (int i = 1; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             int left = INT_MAX;
//             int up = INT_MAX;
//             int right = INT_MAX;
//             if (i - 1 >= 0 && j - 1 >= 0)
//             {
//                 left = dp[i - 1][j - 1];
//             }
//             if (i - 1 >= 0 && j >= 0)
//             {
//                 up = dp[i - 1][j];
//             }
//             if (i - 1 >= 0 && j + 1 < imgWidth)
//             {
//                 right = dp[i - 1][j + 1];
//             }

//             dp[i][j] = matrix[i][j] + min({left, up, right});
//         }
//     }

//     int minLast = INT_MAX;
//     int seamIndexes[imgHeight];
//     memset(seamIndexes, 0, sizeof(seamIndexes));
//     int mini = 0;
//     for (int i = 0; i < imgWidth; i++)
//     {
//         if (matrix[imgHeight - 1][i] < minLast)
//         {
//             minLast = matrix[imgHeight - 1][i];
//             mini = i;
//         }
//     }

//     seamIndexes[imgHeight - 1] = mini;
//     int j = mini;

//     for (int i = imgHeight - 1; i >= 0; i--)
//     {
//         int left = INT_MAX;
//         int up = INT_MAX;
//         int right = INT_MAX;
//         if (i - 1 >= 0 && j - 1 >= 0)
//         {
//             left = dp[i - 1][j - 1];
//         }
//         if (i - 1 >= 0 && j >= 0)
//         {
//             up = dp[i - 1][j];
//         }
//         if (i - 1 >= 0 && j + 1 < imgWidth)
//         {
//             right = dp[i - 1][j + 1];
//         }

//         int temp = min({left, up, right});
//         if (temp == left)
//         {
//             j = j - 1;
//         }
//         else if (temp == up)
//         {
//             j = j;
//         }
//         else
//         {
//             j = j + 1;
//         }

//         seamIndexes[i] = j;
//     }

//     Mat colorImage;
//     cvtColor(outputImage, colorImage, COLOR_GRAY2BGR);

//     for (int i = 0; i < imgHeight; i++)
//     {
//         colorImage.at<Vec3b>(i, seamIndexes[i]) = Vec3b(0, 0, 255);
//     }

//     imshow("Seam", colorImage);

// int reqHeight = stoi(argv[2]);
// int reqWidth = stoi(argv[3]);

//     waitKey(0);

//     return 0;
// }

// #include <iostream>
// #include <opencv2/opencv.hpp>

// using namespace cv;
// using namespace std;

// int main(int argc, char *argv[])
// {
//     string path = argv[1];
//     Mat inputImage = imread(path, IMREAD_GRAYSCALE);
//     if (inputImage.empty())
//     {
//         cout << "Error in opening the image.\n";
//         return 1;
//     }

//     Mat gradX, gradY;
//     Mat absGradX, absGradY;

//     Sobel(inputImage, gradX, CV_16S, 1, 0, 3);
//     Sobel(inputImage, gradY, CV_16S, 0, 1, 3);

//     convertScaleAbs(gradX, absGradX);
//     convertScaleAbs(gradY, absGradY);

//     Mat outputImage;
//     addWeighted(absGradX, 0.5, absGradY, 0.5, 0, outputImage);

//     int imgWidth = outputImage.cols;
//     int imgHeight = outputImage.rows;

//     int reqWidth = stoi(argv[2]);
//     int reqHeight = stoi(argv[3]);

//     int reducedWidth = imgWidth - reqWidth;
//     int reducedHeight = imgHeight - reqHeight;

//     int **matrix = new int *[imgHeight];
//     int **dp = new int *[imgHeight];
//     Vec3b **colorMatrix = new Vec3b *[imgHeight];

//     for (int i = 0; i < imgHeight; i++)
//     {
//         matrix[i] = new int[imgWidth];
//         dp[i] = new int[imgWidth];
//         colorMatrix[i] = new Vec3b[imgWidth];
//     }

//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             uchar pixel = outputImage.at<uchar>(i, j);
//             matrix[i][j] = (int)pixel;
//         }
//     }

//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             colorMatrix[i][j] = inputImage.at<Vec3b>(i, j);
//         }
//     }

//     int **dupMatrix = new int *[imgHeight];
//     for (int i = 0; i < imgHeight; i++)
//     {
//         dupMatrix[i] = new int[imgWidth];
//     }

//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             dupMatrix[i][j] = matrix[i][j];
//         }
//     }

//     while (reducedWidth--)
//     {
// for (int i = 0; i < imgWidth; i++)
// {
//     dp[0][i] = dupMatrix[0][i];
// }

// for (int i = 1; i < imgHeight; i++)
// {
//     for (int j = 0; j < imgWidth; j++)
//     {
//         int left = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
//         int up = dp[i - 1][j];
//         int right = (j + 1 < imgWidth) ? dp[i - 1][j + 1] : INT_MAX;
//         dp[i][j] = dupMatrix[i][j] + min({left, up, right});
//     }
// }

// int minLast = INT_MAX;
// int mini = 0;
// for (int i = 0; i < imgWidth; i++)
// {
//     if (dp[imgHeight - 1][i] < minLast)
//     {
//         minLast = dp[imgHeight - 1][i];
//         mini = i;
//     }
// }

// int *seamIndexes = new int[imgHeight];
// seamIndexes[imgHeight - 1] = mini;

//         int j = mini;
//         for (int i = imgHeight - 1; i > 0; i--)
//         {
//             int left = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
//             int up = dp[i - 1][j];
//             int right = (j + 1 < imgWidth) ? dp[i - 1][j + 1] : INT_MAX;

//             int temp = min({left, up, right});
//             if (temp == left)
//             {
//                 j--;
//             }
//             else if (temp == right)
//             {
//                 j++;
//             }
//             seamIndexes[i - 1] = j;
//         }

//         int **newMatrix = new int *[imgHeight];
//         imgWidth--;
//         for (int i = 0; i < imgHeight; i++)
//         {
//             newMatrix[i] = new int[imgWidth];
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             int k = 0;
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 if (k < imgWidth && j != seamIndexes[i])
//                 {
//                     newMatrix[i][j] = matrix[i][k];
//                     k++;
//                 }
//             }
//         }

//         Vec3b **newColorMatrix = new Vec3b *[imgHeight];
//         imgWidth--;
//         for (int i = 0; i < imgHeight; i++)
//         {
//             newColorMatrix[i] = new Vec3b[imgWidth];
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             int k = 0;
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 if (k < imgWidth && j != seamIndexes[i])
//                 {
//                     newColorMatrix[i][j] = colorMatrix[i][k];
//                     k++;
//                 }
//             }
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             delete[] colorMatrix[i];
//         }
//         delete[] colorMatrix;

//         colorMatrix = newColorMatrix;

//         cout << "Width: " << reducedWidth << endl;
//     }

//     Mat finalImage(imgHeight, imgWidth, CV_8UC3);
//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             finalImage.at<Vec3b>(i, j) = colorMatrix[i][j];
//         }
//     }

//     imwrite("output.jpg", finalImage);
//     waitKey(0);

//     for (int i = 0; i < imgHeight; i++)
//     {
//         delete[] matrix[i];
//         delete[] dp[i];
//         delete[] colorMatrix[i];
//         delete[] dupMatrix[i];
//     }
//     delete[] matrix;
//     delete[] dp;
//     delete[] colorMatrix;
//     delete[] dupMatrix;

//     return 0;
// }

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
                int left = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
                int up = dp[i - 1][j];
                int right = (j + 1 < imgWidth) ? dp[i - 1][j + 1] : INT_MAX;
                dp[i][j] = dupMatrix[i][j] + min({left, up, right});
            }
        }

        int minLast = INT_MAX;
        int mini = 0;
        for (int i = 0; i < imgWidth; i++)
        {
            if (dp[imgHeight - 1][i] < minLast)
            {
                minLast = dp[imgHeight - 1][i];
                mini = i;
            }
        }

        int *seamIndexes = new int[imgHeight];
        seamIndexes[imgHeight - 1] = mini;

        int j = mini;
        for (int i = imgHeight - 1; i > 0; i--)
        {
            int left = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
            int up = dp[i - 1][j];
            int right = (j + 1 < imgWidth) ? dp[i - 1][j + 1] : INT_MAX;

            int temp = min({left, up, right});
            if (temp == left)
            {
                j--;
            }
            else if (temp == right)
            {
                j++;
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
        cout << "Width: " << imgWidth << endl;
    }

    // transpose

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