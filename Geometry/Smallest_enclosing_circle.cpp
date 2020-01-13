#include <algorithm>
#include <vector>
#include <cmath>

struct coor{ long double x, y;};
class smallest_enclosing_circle{
private:
    std::vector<coor> points;
    coor c;
    long double r;

    long double dist(coor P, coor Q) const {
        long double dx = P.x - Q.x;
        long double dy = P.y - Q.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    long double max_dist(long double x, long double y){
        long double res = 0;
        coor P = {x, y};
        for(coor& Q : points){
            res = std::max(res, dist(P, Q));
        } 
        return res;
    }

    long double min_y(long double x){
        long double left = 0, right = 1000;
        for(int i = 0; i < 100; i++){
            long double y1 = (left*2 + right) / 3.0;
            long double y2 = (left + right*2) / 3.0;

            if(max_dist(x, y1) > max_dist(x, y2)) left = y1; 
            else right = y2;
        }
        return left; 
    }

public:
    smallest_enclosing_circle() = delete;
    smallest_enclosing_circle &operator=(const smallest_enclosing_circle) = delete;
    smallest_enclosing_circle(std::vector<coor>&& p) : points(p) {}
    void solve(){
        long double left = 0, right = 1000;
        for(int i = 0; i < 100; i++){
            long double x1 = (left*2 + right) / 3.0;
            long double x2 = (left + right*2) / 3.0;

            long double y1 = min_y(x1);
            long double y2 = min_y(x2);

            if(max_dist(x1, y1) > max_dist(x2, y2)) left = x1;
            else right = x2;
        }

        long double x = left;
        long double y = min_y(x);

        c = {x, y};
        r = max_dist(x, y);
    }

    coor center(){ return c; }
    long double radius(){ return r; }
};