// #include <iostream>
// #include <opencv2/opencv.hpp>
// using namespace cv;
// using namespace std;

// int main(int argc, char *argv[])
// {
//     string path = argv[1];
//     Mat inputImage = imread(path, IMREAD_COLOR);
//     if (inputImage.empty())
//     {
//         cout << "Error in opening the image.\n";
//         return 1;
//     }

//     Mat grayImage;
//     cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

//     Mat gradX, gradY;
//     Mat absGradX, absGradY;

//     Sobel(grayImage, gradX, CV_64F, 1, 0, 3);
//     Sobel(grayImage, gradY, CV_64F, 0, 1, 3);

//     // convertScaleAbs(gradX, absGradX);
//     // convertScaleAbs(gradY, absGradY);

//     Mat energyImage;
//     // addWeighted(absGradX, 0.5, absGradY, 0.5, 0, energyImage);
//     addWeighted(gradX, 0.5, gradY, 0.5, 0, energyImage);
//     magnitude(gradX, gradY, energyImage);
//     energyImage.convertTo(energyImage, CV_64F);
//     imwrite("energyImage.jpg", energyImage);
//     if (energyImage.empty())
//     {
//         cout << "Error in writing the image.\n";
//         return 1;
//     }

//     int imgWidth = inputImage.cols;
//     int imgHeight = inputImage.rows;

//     int reqWidth = stoi(argv[2]);
//     int reqHeight = stoi(argv[3]);

//     int reducedWidth = imgWidth - reqWidth;
//     int reducedHeight = imgHeight - reqHeight;

//     double **matrix = new double *[imgHeight];
//     double **dp = new double *[imgHeight];
//     Vec3b **colorMatrix = new Vec3b *[imgHeight];

//     for (int i = 0; i < imgHeight; i++)
//     {
//         matrix[i] = new double[imgWidth];
//         dp[i] = new double[imgWidth];
//         colorMatrix[i] = new Vec3b[imgWidth];
//     }

//     for (int i = 0; i < imgHeight; i++)
//     {
//         for (int j = 0; j < imgWidth; j++)
//         {
//             matrix[i][j] = energyImage.at<uchar>(i, j);
//             colorMatrix[i][j] = inputImage.at<Vec3b>(i, j);
//         }
//     }

//     double **dupMatrix = new double *[imgHeight];
//     for (int i = 0; i < imgHeight; i++)
//     {
//         dupMatrix[i] = new double[imgWidth];
//         for (int j = 0; j < imgWidth; j++)
//         {
//             dupMatrix[i][j] = matrix[i][j];
//         }
//     }

//     while (reducedWidth > 0)
//     {
//         for (int i = 0; i < imgWidth; i++)
//         {
//             dp[0][i] = dupMatrix[0][i];
//         }

//         for (int i = 1; i < imgHeight; i++)
//         {
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 double left = DBL_MAX;
//                 double up = DBL_MAX;
//                 double right = DBL_MAX;
//                 if (i - 1 >= 0 && j - 1 >= 0)
//                 {
//                     left = dp[i - 1][j - 1];
//                 }
//                 if (i - 1 >= 0 && j >= 0)
//                 {
//                     up = dp[i - 1][j];
//                 }
//                 if (i - 1 >= 0 && j + 1 < imgWidth)
//                 {
//                     right = dp[i - 1][j + 1];
//                 }
//                 dp[i][j] = dupMatrix[i][j] + min({left, up, right});
//             }
//         }

//         int minLast = INT_MAX;
//         int minInd = 0;
//         for (int i = 0; i < imgWidth; i++)
//         {
//             if (dp[imgHeight - 1][i] < minLast)
//             {
//                 minLast = dp[imgHeight - 1][i];
//                 minInd = i;
//             }
//         }

//         double *seamIndexes = new double[imgHeight];
//         seamIndexes[imgHeight - 1] = minInd;

//         int j = minInd;
//         for (int i = imgHeight - 1; i > 0; i--)
//         {
//             double left = DBL_MAX;
//             double up = DBL_MAX;
//             double right = DBL_MAX;
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

//             double temp = min({left, up, right});
//             if (temp == left)
//             {
//                 j = j - 1;
//             }
//             else if (temp == right)
//             {
//                 j = j + 1;
//             }

//             seamIndexes[i - 1] = j;
//         }

//         double **newMatrix = new double *[imgHeight];
//         Vec3b **newColorMatrix = new Vec3b *[imgHeight];
//         for (int i = 0; i < imgHeight; i++)
//         {
//             newMatrix[i] = new double[imgWidth - 1];
//             newColorMatrix[i] = new Vec3b[imgWidth - 1];
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             int k = 0;
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 if (j != seamIndexes[i])
//                 {
//                     newMatrix[i][k] = dupMatrix[i][j];
//                     newColorMatrix[i][k] = colorMatrix[i][j];
//                     k++;
//                 }
//             }
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             delete[] dupMatrix[i];
//             delete[] colorMatrix[i];
//         }
//         delete[] dupMatrix;
//         delete[] colorMatrix;

//         dupMatrix = newMatrix;
//         colorMatrix = newColorMatrix;
//         imgWidth--;

//         Mat middlImage(imgHeight, imgWidth, CV_64F);
//         for (int i = 0; i < imgHeight; i++)
//         {
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 middlImage.at<Vec3b>(i, j) = colorMatrix[i][j];
//             }
//         }

//         Mat grayImage;
//         cvtColor(middlImage, grayImage, COLOR_BGR2GRAY);

//         Mat gradX, gradY;
//         Mat absGradX, absGradY;

//         Sobel(grayImage, gradX, CV_64F, 1, 0, 3);
//         Sobel(grayImage, gradY, CV_64F, 0, 1, 3);

//         Mat energyImage;
//         addWeighted(gradX, 0.5, gradY, 0.5, 0, energyImage);
//         magnitude(gradX, gradY, energyImage);
//         energyImage.convertTo(energyImage, CV_64F);

//         for (int i = 0; i < imgHeight; i++)
//         {
//             for (int j = 0; j < imgWidth; j++)
//             {
//                 dupMatrix[i][j] = energyImage.at<uchar>(i, j);
//                 colorMatrix[i][j] = inputImage.at<Vec3b>(i, j);
//             }
//         }

//         delete[] seamIndexes;

//         reducedWidth--;
//         cout << "Width: " << reducedWidth << endl;
//     }

//     while (reducedHeight > 0)
//     {
//         for (int i = 0; i < imgHeight; i++)
//         {
//             dp[i][0] = dupMatrix[i][0];
//         }

//         for (int j = 1; j < imgWidth; j++)
//         {
//             for (int i = 0; i < imgHeight; i++)
//             {
//                 double left = DBL_MAX;
//                 double back = DBL_MAX;
//                 double down = DBL_MAX;

//                 if (i - 1 >= 0 && j - 1 >= 0)
//                 {
//                     left = dp[i - 1][j - 1];
//                 }
//                 if (i - 1 >= 0 && j - 1 >= 0)
//                 {
//                     back = dp[i][j - 1];
//                 }
//                 if (i + 1 < imgHeight && j - 1 >= 0)
//                 {
//                     down = dp[i + 1][j - 1];
//                 }

//                 dp[i][j] = dupMatrix[i][j] + min({left, back, down});
//             }
//         }

//         int minLast = INT_MAX;
//         int minInd = 0;
//         for (int i = 0; i < imgHeight; i++)
//         {
//             if (dp[i][imgWidth - 1] < minLast)
//             {
//                 minLast = dp[i][imgWidth - 1];
//                 minInd = i;
//             }
//         }

//         double *seamIndexes = new double[imgWidth];
//         seamIndexes[imgWidth - 1] = minInd;

//         int i = minInd;
//         for (int j = imgWidth - 1; j > 0; j--)
//         {
//             double left = DBL_MAX;
//             double back = DBL_MAX;
//             double down = DBL_MAX;

//             if (i - 1 >= 0 && j - 1 >= 0)
//             {
//                 left = dp[i - 1][j - 1];
//             }
//             if (i - 1 >= 0 && j - 1 >= 0)
//             {
//                 back = dp[i][j - 1];
//             }
//             if (i + 1 < imgHeight && j - 1 >= 0)
//             {
//                 down = dp[i + 1][j - 1];
//             }

//             int temp = min({left, back, down});
//             if (temp == left)
//             {
//                 i = i - 1;
//             }
//             else if (temp == down)
//             {
//                 i = i + 1;
//             }

//             seamIndexes[j - 1] = i;
//         }

//         double **newMatrix = new double *[imgHeight - 1];
//         Vec3b **newColorMatrix = new Vec3b *[imgHeight - 1];
//         for (int i = 0; i < imgHeight - 1; i++)
//         {
//             newMatrix[i] = new double[imgWidth];
//             newColorMatrix[i] = new Vec3b[imgWidth];
//         }

//         for (int j = 0; j < imgWidth; j++)
//         {
//             int k = 0;
//             for (int i = 0; i < imgHeight; i++)
//             {
//                 if (i != seamIndexes[j])
//                 {
//                     newMatrix[k][j] = dupMatrix[i][j];
//                     newColorMatrix[k][j] = colorMatrix[i][j];
//                     k++;
//                 }
//             }
//         }

//         for (int i = 0; i < imgHeight; i++)
//         {
//             delete[] dupMatrix[i];
//             delete[] colorMatrix[i];
//         }
//         delete[] dupMatrix;
//         delete[] colorMatrix;

//         dupMatrix = newMatrix;
//         colorMatrix = newColorMatrix;
//         imgHeight--;

//         delete[] seamIndexes;

//         reducedHeight--;
//         cout << "Height: " << reducedHeight << endl;
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

//     for (int i = 0; i < imgHeight; i++)
//     {
//         delete[] matrix[i];
//         delete[] dp[i];
//         delete[] dupMatrix[i];
//         delete[] colorMatrix[i];
//     }
//     delete[] matrix;
//     delete[] dp;
//     delete[] dupMatrix;
//     delete[] colorMatrix;

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat calculateEnergyImage(const Mat &inputImage)
{
    Mat grayImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    Mat gradX, gradY;
    Sobel(grayImage, gradX, CV_64F, 1, 0, 3);
    Sobel(grayImage, gradY, CV_64F, 0, 1, 3);

    Mat energyImage;
    magnitude(gradX, gradY, energyImage);
    energyImage.convertTo(energyImage, CV_64F);

    return energyImage;
}

void initializeMatrices(const Mat &energyImage, const Mat &inputImage, double **&matrix, Vec3b **&colorMatrix)
{
    int imgHeight = energyImage.rows;
    int imgWidth = energyImage.cols;

    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            matrix[i][j] = energyImage.at<double>(i, j);
            colorMatrix[i][j] = inputImage.at<Vec3b>(i, j);
        }
    }
}

Mat createFinalImage(Vec3b **colorMatrix, int imgHeight, int imgWidth)
{
    Mat finalImage(imgHeight, imgWidth, CV_8UC3);
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            finalImage.at<Vec3b>(i, j) = colorMatrix[i][j];
        }
    }
    return finalImage;
}

int main(int argc, char *argv[])
{
    string path = argv[1];
    Mat inputImage = imread(path, IMREAD_COLOR);
    if (inputImage.empty())
    {
        cout << "Error in opening the image.\n";
        return 1;
    }

    int imgWidth = inputImage.cols;
    int imgHeight = inputImage.rows;

    int reqWidth = stoi(argv[2]);
    int reqHeight = stoi(argv[3]);

    int reducedWidth = imgWidth - reqWidth;
    int reducedHeight = imgHeight - reqHeight;

    Mat energyImage = calculateEnergyImage(inputImage);

    double **matrix = new double *[imgHeight];
    double **dp = new double *[imgHeight];
    double **dupMatrix = new double *[imgHeight];
    Vec3b **colorMatrix = new Vec3b *[imgHeight];

    for (int i = 0; i < imgHeight; i++)
    {
        matrix[i] = new double[imgWidth];
        dp[i] = new double[imgWidth];
        dupMatrix[i] = new double[imgWidth];
        colorMatrix[i] = new Vec3b[imgWidth];
    }

    initializeMatrices(energyImage, inputImage, matrix, colorMatrix);

    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            dupMatrix[i][j] = matrix[i][j];
        }
    }

    while (reducedWidth > 0)
    {
        double *seamIndexes = new double[imgHeight];

        for (int i = 0; i < imgWidth; i++)
        {
            dp[0][i] = dupMatrix[0][i];
        }

        for (int i = 1; i < imgHeight; i++)
        {
            for (int j = 0; j < imgWidth; j++)
            {
                double left = DBL_MAX;
                double up = DBL_MAX;
                double right = DBL_MAX;
                if (j - 1 >= 0)
                {
                    left = dp[i - 1][j - 1];
                }
                if (j + 1 < imgWidth)
                {
                    right = dp[i - 1][j + 1];
                }
                up = dp[i - 1][j];
                dp[i][j] = dupMatrix[i][j] + min({left, up, right});
            }
        }

        int minInd = 0;
        double minLast = DBL_MAX;
        for (int i = 0; i < imgWidth; i++)
        {
            if (dp[imgHeight - 1][i] < minLast)
            {
                minLast = dp[imgHeight - 1][i];
                minInd = i;
            }
        }

        seamIndexes[imgHeight - 1] = minInd;

        int j = minInd;
        for (int i = imgHeight - 1; i > 0; i--)
        {
            double left = DBL_MAX;
            double up = DBL_MAX;
            double right = DBL_MAX;
            if (j - 1 >= 0)
            {
                left = dp[i - 1][j - 1];
            }
            if (j + 1 < imgWidth)
            {
                right = dp[i - 1][j + 1];
            }
            up = dp[i - 1][j];

            double temp = min({left, up, right});
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

        double **newMatrix = new double *[imgHeight];
        Vec3b **newColorMatrix = new Vec3b *[imgHeight];
        for (int i = 0; i < imgHeight; i++)
        {
            newMatrix[i] = new double[imgWidth - 1];
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

        Mat middleImage = createFinalImage(colorMatrix, imgHeight, imgWidth);
        energyImage = calculateEnergyImage(middleImage);

        initializeMatrices(energyImage, middleImage, dupMatrix, colorMatrix);

        reducedWidth--;
        cout << "Width: " << reducedWidth << endl;
    }

    while (reducedHeight > 0)
    {
        double *seamIndexes = new double[imgWidth];

        for (int i = 0; i < imgHeight; i++)
        {
            dp[i][0] = dupMatrix[i][0];
        }

        for (int j = 1; j < imgWidth; j++)
        {
            for (int i = 0; i < imgHeight; i++)
            {
                double left = DBL_MAX;
                double back = DBL_MAX;
                double down = DBL_MAX;

                if (i - 1 >= 0)
                {
                    left = dp[i - 1][j - 1];
                }
                if (i + 1 < imgHeight)
                {
                    down = dp[i + 1][j - 1];
                }
                back = dp[i][j - 1];

                dp[i][j] = dupMatrix[i][j] + min({left, back, down});
            }
        }

        int minInd = 0;
        double minLast = DBL_MAX;
        for (int i = 0; i < imgHeight; i++)
        {
            if (dp[i][imgWidth - 1] < minLast)
            {
                minLast = dp[i][imgWidth - 1];
                minInd = i;
            }
        }

        seamIndexes[imgWidth - 1] = minInd;

        int i = minInd;
        for (int j = imgWidth - 1; j > 0; j--)
        {
            double left = DBL_MAX;
            double back = DBL_MAX;
            double down = DBL_MAX;

            if (i - 1 >= 0)
            {
                left = dp[i - 1][j - 1];
            }
            if (i + 1 < imgHeight)
            {
                down = dp[i + 1][j - 1];
            }
            back = dp[i][j - 1];

            double temp = min({left, back, down});
            if (temp == left)
            {
                i = i - 1;
            }
            else if (temp == down)
            {
                i = i + 1;
            }

            seamIndexes[j - 1] = i;
        }

        double **newMatrix = new double *[imgHeight - 1];
        Vec3b **newColorMatrix = new Vec3b *[imgHeight - 1];
        for (int i = 0; i < imgHeight - 1; i++)
        {
            newMatrix[i] = new double[imgWidth];
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

        Mat middleImage = createFinalImage(colorMatrix, imgHeight, imgWidth);
        energyImage = calculateEnergyImage(middleImage);

        initializeMatrices(energyImage, middleImage, dupMatrix, colorMatrix);

        reducedHeight--;
        cout << "Height: " << reducedHeight << endl;
    }

    Mat finalImage = createFinalImage(colorMatrix, imgHeight, imgWidth);
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
