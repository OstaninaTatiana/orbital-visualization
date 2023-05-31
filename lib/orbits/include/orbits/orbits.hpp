#pragma once
#ifndef orbits
#define orbits

#include <array>
#include <vector>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

namespace vec
{
	class Dot
	{
	public:
		Dot() = default;
		Dot(double x, double y)
		{
			x_ = x;
			y_ = y;
		}

		double x()
		{
			return x_;
		}

		double y()
		{
			return y_;
		}

	private:
		double x_ = 0;
		double y_ = 0;
	};

	class Vector
	{
	public:
		Vector() = default;

		Vector(double x, double y)
		{
			x_ = x;
			y_ = y;
		};

		Vector(vec::Dot dot)
		{
			x_ = dot.x();
			y_ = dot.y();
		}

		Vector(vec::Dot dot1, vec::Dot dot2)
		{
			x_ = dot2.x() - dot1.x();
			y_ = dot2.y() - dot1.y();
		}

		~Vector() = default;
		
		double x()
		{
			return x_;
		}

		double y()
		{
			return y_;
		}



		double length()
		{
			return std::sqrt(x_ * x_ + y_ * y_);
		}

		vec::Vector normalized()
		{
			return vec::Vector(x_ / length(), y_ / length());
		}

	private:
		double x_ = 0;
		double y_ = 0;
	};

	vec::Vector operator*(vec::Vector a, double c) noexcept
	{
		return vec::Vector(a.x() * c, a.y() * c);
	};

	vec::Vector operator+(Vector a, Vector b) noexcept
	{
		return vec::Vector(a.x() + b.x(), a.y() + b.y());
	};

	vec::Dot operator+(vec::Dot dot, vec::Vector vec)
	{
		return vec::Dot(dot.x() + vec.x(), dot.y() + vec.y());
	}
}

namespace orbit
{
	const std::runtime_error index_error("index out of range");

	class Colour
	{
	public:

		Colour() = default;
		Colour(std::string name)
		{
			if (name == "red")
			{
				name_ = "red";
				r_ = 255;
				g_ = 0;
				b_ = 0;
			}
			else if (name == "green")
			{
				name_ = "green";
				r_ = 0;
				g_ = 255;
				b_ = 0;
			}
			else if (name == "blue")
			{
				name_ = "blue";
				r_ = 0;
				g_ = 0;
				b_ = 255;
			}
		}

		~Colour() = default;

		std::string name()
		{
			return name_;
		}

		int r()
		{
			return r_;
		}

		int g()
		{
			return g_;
		}

		int b()
		{
			return b_;
		}

	private:
		int r_ = 0;
		int g_ = 0;
		int b_ = 0;
		std::string name_ = "";
	};

	class Orbit
	{
	public:
		Orbit()
		{
			used_amount_ = 0;
			dots_ = std::vector<vec::Dot>{};
		}
		Orbit(int n, std::vector<vec::Dot> all_dots, std::string colour)
		{
			dots_.reserve(1000);
			for (int i = 0; i < n; i++)
			{
				dots_.push_back(all_dots[i]);
				update_k(all_dots[i]);
			}
			used_amount_ = n;
			colour_ = Colour(colour);
		};
		~Orbit() = default;

		void add_dot(vec::Dot dot)
		{
			if (used_amount_ < max_dots_)
			{
				dots_.push_back(dot);
				used_amount_ += 1;
			}
			else
			{
				dots_[delta_] = dot;
				delta_ = (delta_ + 1) % max_dots_;
			}
			update_k(dot);
		}

		vec::Dot operator[](int n)
		{
			if (n >= used_amount_)
			{
				throw index_error;
			}
			return dots_[(n + delta_) % max_dots_];
		}

		int lenght()
		{
			return used_amount_;
		}

		void change_colour(std::string colour)
		{
			colour_ = Colour(colour);
		}

		double left()
		{
			return left_;
		};
		double right()
		{
			return right_;
		};
		double top()
		{
			return top_;
		};
		double down()
		{
			return down_;
		};
		double k()
		{
			return k_;
		}
		Colour colour()
		{
			return colour_;
		}

	private:
		void update_k(vec::Dot dot)
		{
			if (dot.x() < left_)
			{
				left_ = dot.x();
			}
			if (dot.x() > right_)
			{
				right_ = dot.x();
			}
			if (dot.y() < down_)
			{
				down_ = dot.y();
			}
			if (dot.y() > top_)
			{
				top_ = dot.y();
			}
			k_ = std::max(top_ - down_, right_ - left_) / (size_ - 100);
			if (k_ < 0.0025)
			{
				k_ = 0.0025;
			}
		}

	private:
		static const int max_dots_ = 1000;
		std::vector<vec::Dot> dots_{};
		int used_amount_ = 0;
		int delta_ = 0;
		Colour colour_ = Colour();
		int size_ = 500;
		double left_ = 0;
		double right_ = 0;
		double top_ = 0;
		double down_ = 0;
		double k_ = 1;
	};

	class Body
	{
	public:
		Body() = default;
		Body(double m, vec::Dot pos, vec::Vector v, std::string colour)
		{
			m_ = m;
			pos_ = pos;
			v_ = v;
			std::vector<vec::Dot> vec = std::vector<vec::Dot>{ pos };
			orbit_ = orbit::Orbit(1, std::vector<vec::Dot>{pos}, colour);
		}

		double m()
		{
			return m_;
		}

		vec::Dot pos()
		{
			return pos_;
		}

		void change_pos(vec::Dot new_pos)
		{
			pos_ = new_pos;
			orbit_.add_dot(new_pos);
		}

		vec::Vector v()
		{
			return v_;
		}

		void change_v(vec::Vector v)
		{
			v_ = v;
		}

		orbit::Orbit orbit()
		{
			return orbit_;
		}


	private:
		double m_ = 0;
		vec::Dot pos_;
		vec::Vector v_;
		orbit::Orbit orbit_ = orbit::Orbit();;
	};

	
}


namespace calc
{
	const double G = 6.67 * 0.00000000001;
	void calculate_orbit(orbit::Body& body1, orbit::Body& body2, double timestep=1)
	{
		double f = G * body1.m() * body2.m() / std::sqrt(std::pow(body1.pos().x() - body2.pos().x(), 2) + std::pow(body1.pos().y() - body2.pos().y(), 2));
		
		vec::Vector a1 = vec::Vector(body1.pos(), body2.pos()).normalized() * (f / body1.m());
		vec::Vector a2 = vec::Vector(body2.pos(), body1.pos()).normalized() * (f / body2.m());
		vec::Vector v1 = body1.v() + a1 * timestep;
		vec::Vector v2 = body2.v() + a2 * timestep;
		vec::Dot pos1 = body1.pos() + v1 * timestep;
		vec::Dot pos2 = body2.pos() + v2 * timestep;

		body1.change_pos(pos1);
		body2.change_pos(pos2);
		body1.change_v(v1);
		body2.change_v(v2);
	};

	void calculate_orbit(orbit::Body& body1, orbit::Body& body2, orbit::Body& body3, double timestep = 1)
	{
		double f = G * body1.m() * body2.m() / std::sqrt(std::pow(body1.pos().x() - body2.pos().x(), 2) + std::pow(body1.pos().y() - body2.pos().y(), 2));

		vec::Vector a1 = vec::Vector(body1.pos(), body2.pos()).normalized() * (f / body1.m()) +
						 vec::Vector(body1.pos(), body3.pos()).normalized() * (f / body1.m());
		vec::Vector a2 = vec::Vector(body2.pos(), body1.pos()).normalized() * (f / body2.m()) +
						 vec::Vector(body2.pos(), body3.pos()).normalized() * (f / body2.m());
		vec::Vector a3 = vec::Vector(body3.pos(), body1.pos()).normalized() * (f / body3.m()) +
						 vec::Vector(body3.pos(), body2.pos()).normalized() * (f / body3.m());
		vec::Vector v1 = body1.v() + a1 * timestep;
		vec::Vector v2 = body2.v() + a2 * timestep;
		vec::Vector v3 = body3.v() + a3 * timestep;
		vec::Dot pos1 = body1.pos() + v1 * timestep;
		vec::Dot pos2 = body2.pos() + v2 * timestep;
		vec::Dot pos3 = body3.pos() + v3 * timestep;

		body1.change_pos(pos1);
		body2.change_pos(pos2);
		body3.change_pos(pos3);
		body1.change_v(v1);
		body2.change_v(v2);
		body3.change_v(v3);
	};

	void print_orbits(std::vector<orbit::Orbit> all_orbits, int size_=500, std::string window="window")
	{
		cv::Mat img = cv::Mat(cv::Size(size_, size_), CV_8UC3, cv::Scalar(0, 0, 0));
		double left = 0;
		double right = 0;
		double top = 0;
		double down = 0;
		if (all_orbits.size() == 2)
		{
			left = std::min(all_orbits[0].left(), all_orbits[1].left());
			right = std::max(all_orbits[0].right(), all_orbits[1].right());
			top = std::max(all_orbits[0].top(), all_orbits[1].top());
			down = std::min(all_orbits[0].down(), all_orbits[1].down());
		}
		if (all_orbits.size() == 3)
		{
			left = std::min(std::min(all_orbits[0].left(), all_orbits[1].left()), all_orbits[2].left());
			right = std::max(std::max(all_orbits[0].right(), all_orbits[1].right()), all_orbits[2].right());
			top = std::max(std::max(all_orbits[0].top(), all_orbits[1].top()), all_orbits[2].top());
			down = std::min(std::min(all_orbits[0].down(), all_orbits[1].down()), all_orbits[2].down());
		}

		double k = std::max(top - down, right - left) / (size_ - 100);
		if (k < 0.0025)
		{
			k = 0.0025;
		}

		for (int i = 0; i < all_orbits.size(); i++)
		{
			for (int j = 0; j < all_orbits[i].lenght(); j++) 
			{
				/*
				img.at<cv::Vec3b>(int(all_orbits[i][j].x() / k) - left + 10, 500 - (int(all_orbits[i][j].y() / k) - down + 10))[0] = all_orbits[i].colour().b();
				img.at<cv::Vec3b>(int(all_orbits[i][j].x() / k) - left + 10, 500 - (int(all_orbits[i][j].y() / k) - down + 10))[1] = all_orbits[i].colour().g();
				img.at<cv::Vec3b>(int(all_orbits[i][j].x() / k) - left + 10, 500 - (int(all_orbits[i][j].y() / k) - down + 10))[2] = all_orbits[i].colour().r();
				*/
				img.at<cv::Vec3b>(500 - (int((all_orbits[i][j].y() - down) / k) + 10), int((all_orbits[i][j].x() - left) / k) + 10)[0] = all_orbits[i].colour().b();
				img.at<cv::Vec3b>(500 - (int((all_orbits[i][j].y() - down) / k) + 10), int((all_orbits[i][j].x() - left) / k) + 10)[1] = all_orbits[i].colour().g();
				img.at<cv::Vec3b>(500 - (int((all_orbits[i][j].y() - down) / k) + 10), int((all_orbits[i][j].x() - left) / k) + 10)[2] = all_orbits[i].colour().r();

			}

		}				
		cv::imshow(window, img);
		cv::waitKey(10);
	}

}
#endif