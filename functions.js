// value is int or string 
// space is only int 
// Delimiter is only string 
var InsertDelimiter = function(value, space, Delimiter) {
    const tmp_value_str = String(value.toString().split('').reverse().join(''));
    let value_str = '';
    const len = tmp_value_str.length;

    for(let i = 0; i < len; ++i){
        if(i % space == 0) value_str += Delimiter;
        value_str += tmp_value_str[i];
    }
    
    if(value_str[value_str.length - 1] == ',') value_str.slice(0, -1);
    value_str = value_str.split('').reverse().join('');
    value_str = value_str.slice(0, -1)
    return value_str;
}
