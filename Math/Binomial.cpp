#include<iostream>
#include<cstdint>
#include<vector>
#include<algorithm>

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

class Binomial {
private:
    #define MOD 1000000007
    std::vector<mint> fac, finv, inv;
    size_t sz;

    mint for_big_N(const int& n, const int& r) const noexcept{
        mint res = 1;
        const int k = std::min(r, n-r);
        for(int i = 0; i < k; i++){
            res *= mint(n - i) / mint(k - i);
        }
        return res;
    }
public:
    Binomial operator=(const Binomial) = delete;
    Binomial (const Binomial&) = delete;
    Binomial(size_t s = 510000) noexcept : sz(s), fac(s, 1), inv(s, 1), finv(s, 1){
        fac[0] = fac[1] = 1;
        inv[1] = 1;
        finv[0] = finv[1] = 1;
        for(int i = 2; i < sz; i++){
            fac[i] = fac[i-1] * mint(i);
            inv[i] = -inv[MOD % i] * mint(MOD / i);
            finv[i] = finv[i-1] * inv[i];
        }
    }
    mint operator() (const int& n, const int& r) const noexcept {
        if(n < r) return mint(0);
        if(n < 0 || r < 0) return mint(0);
        if(n >= sz) return for_big_N(n, r);

        return fac[n] * finv[n-r] * finv[r];
    }
};