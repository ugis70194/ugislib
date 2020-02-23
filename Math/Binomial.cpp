#include<iostream>
#include<cstdint>

using i64 = int_fast64_t;
struct mint{
    using i64 = int_fast64_t;
    i64 x;
    const i64 MOD = 1000000007;

    mint(const i64 y = (i64)0) noexcept : x(y) { if(x >= MOD) x %= MOD; }
    mint operator+() const noexcept {return x;}
    mint operator-() const noexcept {return -x;}

    mint operator+(const mint y) const noexcept {return (mint)*this += y; }
    mint operator-(const mint y) const noexcept {return (mint)*this -= y; }
    mint operator*(const mint y) const noexcept {return (mint)*this *= y;}
    mint operator/(const mint y) const noexcept {return (mint)*this /= y;}

    mint& operator+=(const mint y) noexcept {
        x += y.x; 
        if(x >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint y) noexcept {
        x -= y.x;
        if(x < 0) x += MOD;
        return *this;
    }
    mint& operator*=(const mint y) noexcept {
        x *= y.x;
        if(x >= MOD) x %= MOD;
        return *this;
    }
    mint& operator/=(mint y) noexcept {
        i64 exp = MOD - 2;
        while(exp){
            if(exp & 1) *this *= y;
            y *= y;
            exp /= 2;
        }
        return *this;
    }
    friend std::ostream& operator<< (std::ostream& os, const mint& m);
    friend std::istream& operator>> (std::istream& in, mint& m);
};
std::ostream& operator<<(std::ostream& os, const mint& m){
    os << m.x;
    return os;
}
std::istream& operator>> (std::istream& in, mint& m){
    in >> m.x; 
    if(m.x < 0) m.x += 1000000007;
    if(m.x >= 1000000007) m.x %= 1000000007;
    return in; 
}

mint comb(i64 n, i64 k) {
    mint res = 1;
    for(int i = 0; i < k; i++) {
        res *= mint(n-i) / mint(k-i);
    }
    return res;
};