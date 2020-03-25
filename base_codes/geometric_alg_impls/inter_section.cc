#include <vector>
#include <algorithm>
#include "../geometric_algs.h"

namespace geometric_alg
{


std::vector<double> intersection(std::vector<int>& start1, std::vector<int>& end1, std::vector<int>& start2, std::vector<int>& end2) {
    std::vector<double> result;
    // inorder
    if (start1[0]>end1[0]||(start1[0]==end1[0]&&start1[1]>end1[1])) {
        std::vector<int> tmp(start1);
        start1 = end1;
        end1 = tmp;
    }
    if (start2[0]>end2[0]||(start2[0]==end2[0]&&start2[1]>end2[1])) {
        std::vector<int> tmp(start2);
        start2 = end2;
        end2 = tmp;
    }

    // get accorss range
    std::pair<int, int> line1_x = {std::min(start1[0], end1[0]), std::max(start1[0], end1[0])};
    std::pair<int, int> line1_y = {std::min(start1[1], end1[1]), std::max(start1[1], end1[1])};
    std::pair<int, int> line2_x = {std::min(start2[0], end2[0]), std::max(start2[0], end2[0])};
    std::pair<int, int> line2_y = {std::min(start2[1], end2[1]), std::max(start2[1], end2[1])};
    std::pair<int, int> x = {std::max(line1_x.first, line2_x.first), std::min(line1_x.second, line2_x.second)};
    std::pair<int, int> y = {std::max(line1_y.first, line2_y.first), std::min(line1_y.second, line2_y.second)};
    if (x.first>x.second || y.first > y.second) return result;

    // line1: ax+by+c=0
    // a = y2-y1; b=x1-x2; c=y1*x2 - y2*x1;
    int a1 = end1[1] - start1[1];
    int b1 = start1[0] - end1[0];
    int c1 = start1[1] * end1[0] - end1[1] * start1[0];
    // line2
    int a2 = end2[1] - start2[1];
    int b2 = start2[0] - end2[0];
    int c2 = start2[1] * end2[0] - end2[1] * start2[0];


    // horizatial or vectial
    if (a1==0) {
        if (a2==0) {
            // c1*b2 == c2*b1
            if (c1 * b2 == c2 * b1)  {
                result.push_back(x.first);
                result.push_back(y.first);
            }
        }
        else {
            double tmp_x = -(c2 + b2 * start1[1]) * 1.0 / a2;
            if (tmp_x>= x.first && tmp_x<=x.second){
                result.push_back(tmp_x);
                result.push_back(y.first);
            }
        }
    }
    else if (b1==0) {
        if (b2==0) {
            if (c1*a2==c2*a1) {
                result.push_back(x.first);
                result.push_back(y.first);
            }
        }
        else {
            double tmp_y = -(c2 + a2 * x.first) * 1.0 / b2;
            if (tmp_y >= y.first && tmp_y <= y.second) {
                result.push_back(x.first);
                result.push_back(tmp_y);
            }
        }
    }
    else {
        if (a2*b1==b2*a1) {
            // override
            if (a2*start1[0]+b2*start1[1]+c2==0) {
                result.push_back(x.first);
                result.push_back(y.first);
            }
        }
        else {
            double tmp_x = (b2*c1-c2*b1)*1.0/(a2*b1-b2*a1);
            double tmp_y = (a1*c2-a2*c1)*1.0/(a2*b1-b2*a1);
            if (tmp_x>=x.first && tmp_x<=x.second && tmp_y>=y.first && tmp_y<=y.second) {
                result.push_back(tmp_x);
                result.push_back(tmp_y);
            }
        }
    }
    return result;
}


} // namespace geometric_alg
