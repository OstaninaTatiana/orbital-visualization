#include <orbits/orbits.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

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

    /* TEST 2
    orbit::Body body1 = orbit::Body(1000000000, vec::Dot(0, 0), vec::Vector(0, 0), "red");
    orbit::Body body2 = orbit::Body(1000000000, vec::Dot(100, 0), vec::Vector(0, 0), "blue");
    orbit::Body body3 = orbit::Body(1000000000, vec::Dot(0, 100), vec::Vector(0, 0), "green");
    */

    orbit::Body body1 = orbit::Body(10000000000, vec::Dot(0, 0), vec::Vector(0, -0.5), "red");
    orbit::Body body2 = orbit::Body(10000000000, vec::Dot(10, 0), vec::Vector(0, 0.5), "blue");
    while (true)
    {
        calc::calculate_orbit(body1, body2, 0.1);
        calc::print_orbits(std::vector<orbit::Orbit>{body1.orbit(), body2.orbit()});
    }
}
