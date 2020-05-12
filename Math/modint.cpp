#include<iostream>
#include<cstdint>

struct mint{
    using i64 = int_fast64_t;
    const i64 MOD = 1000000007;
    i64 x;

    mint(const i64 y = (i64)0) noexcept : x(y) { 
        if(x >= MOD) x %= MOD; 
        if(x < 0) x += MOD;
    }
    mint operator+() const noexcept {return x;}
    mint operator-() const noexcept {return x ? MOD - x : 0;}
    mint operator+(const mint y) const noexcept {return (mint)*this += y; }
    mint operator-(const mint y) const noexcept {return (mint)*this -= y; }
    mint operator*(const mint y) const noexcept {return (mint)*this *= y;}
    mint operator/(const mint y) const noexcept {return (mint)*this /= y;}

    mint operator=(const mint y) noexcept {
        x = y.x;
        if(x >= MOD) x -= MOD;
        if(x < 0) x += MOD;
        return *this;
    }
    mint operator=(const i64 y) noexcept {
        x = y;
        if(x >= MOD) x -= MOD;
        if(x < 0) x += MOD;
        return *this;
    }
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
    friend std::ostream& operator<< (std::ostream& os, const mint& m) noexcept {
        os << m.x;
        return os;
    }
    friend std::istream& operator>> (std::istream& in, mint& m) noexcept {
        const int mod = 1000000007;
        in >> m.x; 
        if(m.x < 0) m.x += mod;
        if(m.x >= mod) m.x %= mod;
        return in; 
    }
    friend mint mod_pow(mint n, i64 k) noexcept {
        mint res = 1;
        while(k){
            if(k&1) res *= n;
            n *= n;
            k >>= 1;
        }
        return res;
    }
};