#include <vector>
#include "../geometric_algs.h"

namespace geometric_alg
{

int gcd(int x, int y) {
    if (x%y==0) return y;
    return gcd(y, x%y);
}

bool checkStraightLine(std::vector<std::vector<int>>& coordinates) {
    if (coordinates.size()==2) return true;
    int n = coordinates.size();
    int i = 1;
    // override
    while(i<n && coordinates[i][0]==coordinates[0][0] && coordinates[i][1] == coordinates[0][1]) i++;
    if (i==n) return true;
    int delta_x = coordinates[0][0] - coordinates[i][0];
    int delta_y = coordinates[0][1] - coordinates[i][1];
    if (delta_x==0) {
        while(i<n && coordinates[0][0]==coordinates[i][0]) i++;
        if (i==n) return true;
        return false;
    }
    else if (delta_y == 0) {
        while(i<n && coordinates[0][1]==coordinates[i][1]) i++;
        if (i==n) return true;
        return false;
    }
    else {
        int common_divisor = gcd(delta_x, delta_y);
        delta_x /= common_divisor;
        delta_y /= common_divisor;
        while(i<n) {
            int tmp_delta_x = coordinates[0][0] - coordinates[i][0];
            int tmp_delta_y = coordinates[0][1] - coordinates[i][1];
            if (tmp_delta_x == 0 || tmp_delta_y==0) return false;
            common_divisor = gcd(tmp_delta_x, tmp_delta_y);
            tmp_delta_x /= common_divisor;
            tmp_delta_y /= common_divisor;
            if(tmp_delta_x != delta_x && tmp_delta_y != delta_y) return false;
            i++;
        }
        return true;
    }
    return false;
}

} // namespace geometric_alg
