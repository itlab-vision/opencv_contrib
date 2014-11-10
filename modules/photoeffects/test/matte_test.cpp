#include "test_precomp.hpp"

using namespace cv;
using namespace cv::photoeffects;

using namespace std;

TEST(photoeffects_matte, bad_intensity)
{
   Mat image(10, 10, CV_32FC3),dst;
   EXPECT_ERROR(CV_StsAssert, matte(image, dst, -15.0f));
}

TEST(photoeffects_matte, bad_image)
{
    Mat src(10, 10, CV_8UC1);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, matte(src, dst,25));
}

TEST(photoeffects_matte, regression)
{
    string input = "./doc/fake-root/modules/photoeffects/doc/pics/lena_orig.png";
    string expectedOutput = "./doc/fake-root/modules/photoeffects/doc/pics/lena_matte.png";
    Mat src = imread(input, CV_LOAD_IMAGE_COLOR);
    Mat expectedDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);
    if(src.empty())
    {
        FAIL() << "Can't read " + input + "image";
    }
    if(expectedDst.empty())
    {
        FAIL() << "Can't read " + expectedOutput + "image";
    }
    Mat dst;
    matte(src, dst, 25);

    Mat diff = abs(expectedDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
