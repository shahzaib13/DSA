#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// CONSTANTS
const int Binary = 2;
const int Octal = 8;
const int Decimal = 10;
const int HexaDecimal = 16;
// :: FUNCTONS :: 
// UTILS
char int_to_hex(int value);
int hex_to_int(char character);
// Checkers
bool is_valid_number(string input, int base);
// Conversions
string decimal_to_any_base(string decimal, int output_base);
string any_base_to_decimal(string value, int input_base);
// declaration of class
class NumberSystem;
// STREAM OVERLOAD
ostream &operator<<(ostream &os, const NumberSystem &num);
// CLASS IMPELMENTATION
class NumberSystem
{
private:
    string value;
    int base;
public:
    NumberSystem(string value, int base){
        setBase(base);
        setValue(value);
    }
    string converter(int output_base){
        if (base == output_base) return value;
        string decimalVal = any_base_to_decimal(value, base);
        if (output_base == Decimal) return decimalVal;
        return decimal_to_any_base(decimalVal, output_base);
    }
    // Getters
    string getValue() { return value; }
    int getBase() { return base; }
    // Setters
    void setValue(string new_value){
        while (!is_valid_number(new_value, base)){
            cout << "Invalid Value for base " << base << "! Enter again: ";
            cin >> new_value;
        }
        value = new_value;
    }
    void setBase(int new_base){
        while (!(new_base == Binary || new_base == Octal ||
                 new_base == Decimal || new_base == HexaDecimal))
        {
            cout << "Invalid Base! Enter again (2, 8, 10, 16): ";
            cin >> new_base;
        }
        base = new_base;
    }
    // :: ARTHEMATIC OPERATORS OVERLOAD ::
    NumberSystem operator+(const NumberSystem &obj){
        int a = stoi(any_base_to_decimal(this->value, this->base));
        int b = stoi(any_base_to_decimal(obj.value, obj.base));
        string sum = to_string(a + b);
        if (base > obj.base){
            string result = decimal_to_any_base(sum, obj.base);
            return NumberSystem(result, obj.base);
        }
        else{
            string result = decimal_to_any_base(sum, base);
            return NumberSystem(result, base);
        }
    }
    NumberSystem operator-(const NumberSystem &obj)
    {
        int a = stoi(any_base_to_decimal(this->value, this->base));
        int b = stoi(any_base_to_decimal(obj.value, obj.base));
        string substract = to_string(a - b);
        if (base > obj.base){
            string result = decimal_to_any_base(substract, obj.base);
            return NumberSystem(result, obj.base);
        }
        else{
            string result = decimal_to_any_base(substract, base);
            return NumberSystem(result, base);
        }
    }
    NumberSystem operator*(const NumberSystem &obj){
        int a = stoi(any_base_to_decimal(this->value, this->base));
        int b = stoi(any_base_to_decimal(obj.value, obj.base));
        if (base > obj.base){
            string result = decimal_to_any_base(multiplication, obj.base);
            return NumberSystem(result, obj.base);
        }
        else{
            string result = decimal_to_any_base(multiplication, base);
            return NumberSystem(result, base);
        }
    }
    NumberSystem operator/(const NumberSystem &obj){
        int a = stoi(any_base_to_decimal(this->value, this->base));
        int b = stoi(any_base_to_decimal(obj.value, obj.base));
        string division = to_string(a / b);
        if (base > obj.base){
            string result = decimal_to_any_base(division, obj.base);
            return NumberSystem(result, obj.base);
        }
        else{
            string result = decimal_to_any_base(division, base);
            return NumberSystem(result, base);
        }
    }
    // Stream overload
    friend ostream &operator<<(ostream &os, const NumberSystem &num);
};
// MAIN
int main(){
    NumberSystem binary("1111", Binary);
    NumberSystem hex("FF", HexaDecimal);
    cout << binary + hex;
}
// UTILS
char int_to_hex(int value){
    if (value >= 0 && value <= 9)
        return '0' + value;
    else if (value >= 10 && value <= 15)
        return 'A' + (value - 10);
    return '?';
}

int hex_to_int(char character){
    if (character >= '0' && character <= '9')
        return character - '0';
    else if (character >= 'A' && character <= 'F')
        return (character - 'A') + 10;
    else if (character >= 'a' && character <= 'f')
        return (character - 'a') + 10;
    return -1;
}

// Checkers
bool is_valid_number(string input, int base){
    for (char c : input)
    {
        int value = hex_to_int(c);
        if (value < 0 || value >= base)
            return false;
    }
    return true;
}
// Conversions
string decimal_to_any_base(string decimal, int output_base = 2){
    int val = stoi(decimal);
    if (val == 0) return "0";
    string ans;
    while (val > 0)
    {
        int remainder = val % output_base;
        ans.push_back(int_to_hex(remainder));
        val /= output_base;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
string any_base_to_decimal(string value, int input_base = 2){
    int decimal = 0;
    for (char c : value)
    {
        decimal = decimal * input_base + hex_to_int(c);
    }
    return to_string(decimal);
}
// STREAM OVERLOAD (implementation)
ostream &operator<<(ostream &os, const NumberSystem &num){
    os << "Value : " << num.value << "\n";
    os << "Base  : " << num.base;
    return os;
}