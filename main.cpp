#include <orbits/orbits.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <jsoncpp/json/json.h>

int main()
{
    /*
    std::vector<vec::Dot> o{vec::Dot(5, 5), vec::Dot(50, 50) };
    orbit::Orbit a = orbit::Orbit(2, o, "red");
    a.print("result");
    a.add_dot(vec::Dot(100, 100));
    a.print("result");
    a.change_colour("blue");
    */


    // TEST 1
    //orbit::Body body1 = orbit::Body(1000, vec::Dot(0, 0), vec::Vector(50, -50), "red");
    //orbit::Body body2 = orbit::Body(100000000000000, vec::Dot(1000, 2000), vec::Vector(0, 0), "blue");

    /* TEST 2 */
    orbit::Body body1 = orbit::Body(1000000000, vec::Dot(0, 0), vec::Vector(0, 0), "red");
    orbit::Body body2 = orbit::Body(1000000000, vec::Dot(100, 0), vec::Vector(0, 0), "blue");
    orbit::Body body3 = orbit::Body(1000000000, vec::Dot(0, 100), vec::Vector(0, 0), "green");

    //TEST 3
    /*orbit::Body body1 = orbit::Body(10000000000, vec::Dot(0, 0), vec::Vector(0, -0.5), "red");
    orbit::Body body2 = orbit::Body(10000000000, vec::Dot(10, 0), vec::Vector(0, 0.5), "blue");*/

    /*TEST 4*/
    /*orbit::Body body1 = orbit::Body(1000000000, vec::Dot(0, 100), vec::Vector(0, 0), "red");
    orbit::Body body2 = orbit::Body(1000000000, vec::Dot(100, 50), vec::Vector(0, 0), "blue");
    orbit::Body body3 = orbit::Body(1000000000, vec::Dot(0, 0), vec::Vector(0, 0), "green");*/

    /*orbit::Body body1 = orbit::Body(1000000000, vec::Dot(100, 67), vec::Vector(0, 0), "red");
    orbit::Body body2 = orbit::Body(1000000000, vec::Dot(28, 53), vec::Vector(0, 0), "blue");
    orbit::Body body3 = orbit::Body(1000000000, vec::Dot(2, 70), vec::Vector(0, 0), "green");*/

    //bool is_opened = true;
    int key_pressed = -200;
    cv::namedWindow("window");
    while (cv::getWindowProperty("window", cv::WND_PROP_VISIBLE) != 0)
    {
        calc::calculate_orbit(body1, body2, 1);
        calc::print_orbits(std::vector<orbit::Orbit>{body1.orbit(), body2.orbit()}, 500, "window");
        key_pressed = cv::waitKey(10);
        if (key_pressed == 27)
        {
            cv::destroyWindow("window");
        }
        
    }
}
