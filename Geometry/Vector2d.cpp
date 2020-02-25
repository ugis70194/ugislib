struct Vector2d {
    long double x, y;
    Vector2d(long double x0, long double y0) : x(x0), y(y0) {}
    long double norm_p2() { return x*x + y*y; }
    long double inner(Vector2d& v){
        return x*v.x + y*v.y;
    }
    Vector2d proj(Vector2d& v){
        return (*this)*(this->inner(v) / this->norm_p2());
    }
    Vector2d operator+(const Vector2d& v){
        return Vector2d(this->x + v.x, this->y + v.y);
    }
    Vector2d operator-(const Vector2d& v){
        return Vector2d(this->x - v.x, this->y - v.y);
    }
    Vector2d operator*(long double k){
        return Vector2d(k*this->x, k*this->y);
    }
    
};