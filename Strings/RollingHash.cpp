#include<vector>
#include<string>
#include<cstdint>

class RollingHash{
    using uint = uint_fast64_t;
    const uint MASK30 = (1UL << 30) - 1;
    const uint MASK31 = (1UL << 31) - 1;
    const uint MOD = (1UL << 61) - 1;
    const uint POSITIVIZER = MOD * ((1UL << 3) - 1);
    uint Base = 1007;
    std::vector<uint> powMemo;
    std::vector<uint> hash;
public:
    RollingHash() = delete;
    RollingHash(std::string& s) : powMemo(s.length()+1), hash(s.length()+1){   
        powMemo[0] = 1;
        for (int i = 1; i < powMemo.size(); i++){
            powMemo[i] = CalcMod(Mul(powMemo[i - 1], Base));
        }
        for (int i = 0; i < s.length(); i++){
            hash[i + 1] = CalcMod(Mul(hash[i], Base) + s[i]);
        }
    }

    uint Slice(int begin, int length){
        return CalcMod(hash[begin + length] + POSITIVIZER - Mul(hash[begin], powMemo[length]));
    }

    uint Mul(uint l, uint r){
        uint lu = l >> 31;
        uint ld = l & MASK31;
        uint ru = r >> 31;
        uint rd = r & MASK31;
        uint middleBit = ld * ru + lu * rd;
        return ((lu * ru) << 1) + ld * rd + ((middleBit & MASK30) << 31) +(middleBit >> 30);
    }

    uint CalcMod(uint val){
        val = (val & MOD) + (val >> 61);
        if (val > MOD) val -= MOD;
        return val;
    }
};  