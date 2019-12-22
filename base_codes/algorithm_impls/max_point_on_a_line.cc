#include <map>
#include "../algorithm.h"

struct compare {
    bool operator () (const std::pair<int, int> &ls, 
                      const std::pair<int, int> &rs) const {  
      return ls.first < rs.first || (ls.first == rs.first && ls.second < rs.second);  
      
    }  
};

int max_common_divisor(int a, int b) {
    if (a % b == 0) return b;
    return max_common_divisor(b, a % b);
}

int max_point_on_a_line(vector<Point> &points){
    int result = 0;
    if (points.size() <= 2) return points.size();
    for (int i=0; i < points.size(); i++){
        int tmp = 0;
        std::map<std::pair<int, int>, int, compare> map;
        int horiztonal = 0;
        int vertical = 0;
        int overleap = 0;

        for (int j = i + 1; j < points.size(); j++) {
            int gx = points[j].x - points[i].x;
            int gy = points[j].y - points[i].y;
            if (gx == 0 && gy == 0) overleap++;
            else if (gx == 0) {
                horiztonal++;
                tmp = std::max(tmp, horiztonal);
            }
            else if (gy == 0) {
                vertical++;
                tmp = std::max(tmp, vertical);
            }
            else{
                int gcd = max_common_divisor(gx, gy);
                std::pair<int, int> rate = std::make_pair(gx/gcd, gy/gcd);
                std::map<std::pair<int, int>, int>::iterator iter = map.find(rate);
                if (iter != map.end()) {
                    iter->second = iter->second + 1;
                }
                else{
                    map[rate] = 1;
                }
                tmp = std::max(tmp, map[rate]);
            }
        }
        result = std::max(result, tmp + overleap + 1);
    }
    return result;
}
