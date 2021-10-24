#include<string>
using i64 = int_fast64_t;

i64 expression(std::string::const_iterator &itr);
i64 term(std::string::const_iterator &itr);
i64 factor(std::string::const_iterator &itr);
i64 number(std::string::const_iterator &itr);

// 四則演算の式をパースしてその評価結果を返す
i64 expression(std::string::const_iterator &itr){
    i64 val = term(itr);

    while(true){
        if(*itr == '+'){
            itr++;
            val += term(itr);
        }else if(*itr == '-'){
            itr++;
            val -= term(itr);
        }else{
            break;
        }
    }

    return val;
}

// 乗算除算の式をパースしてその評価結果を返す
i64 term(std::string::const_iterator &itr){
    i64 val = factor(itr);

    while(true){
        if(*itr == '*'){
            itr++;
            val *= number(itr);
        }else if(*itr == '/'){
            itr++;
            val /= number(itr);
        }else{
            break;
        }
    }

    return val;
}

// 括弧か数をパースしてその評価結果を返す
i64 factor(std::string::const_iterator &itr){
    if(*itr == '('){
        itr++;
        i64 val = expression(itr);
        itr++;  // '('
        return val;
    }
    
    return number(itr);
}
// 数字の列をパースしてその数を返す
i64 number(std::string::const_iterator &itr){
    i64 val = 0;
    while(std::isdigit(*itr)){
        val *= 10;
        val += (i64)(*itr - '0');
        itr++;
    }
    return val;
}