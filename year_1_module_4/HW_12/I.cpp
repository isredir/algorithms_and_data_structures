#include <bits/stdc++.h>

using namespace std;

class big_integer {
    static const int BASE = 1000000000;

    std::vector<int> _digits;

    bool _is_negative;

    void _remove_leading_zeros();

    void _shift_right();

public:
    big_integer();

    big_integer(std::string);

    big_integer(int);

    big_integer operator-() const;

    friend std::ostream& operator <<(std::ostream&, const big_integer&);

    friend bool operator==(const big_integer &, const big_integer &);

    friend bool operator!=(const big_integer &, const big_integer &);

    friend bool operator<(const big_integer &, const big_integer &);

    friend bool operator<=(const big_integer &, const big_integer &);

    friend big_integer operator+(big_integer, const big_integer &);

    friend big_integer operator-(big_integer, const big_integer &);

    friend big_integer abs(const big_integer &);

    friend big_integer operator*(const big_integer &, const big_integer &);

    friend big_integer operator/(const big_integer &, const big_integer &);

    friend big_integer operator%(const big_integer &, const big_integer &);

    bool odd() const;

    big_integer pow(big_integer) const;
};

big_integer::big_integer() {
    this->_is_negative = false;
}

big_integer::big_integer(std::string str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_is_negative = true;
        } else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        this->_remove_leading_zeros();
    }
}

void big_integer::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

std::ostream& operator <<(std::ostream& os, const big_integer& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}

bool operator==(const big_integer &left, const big_integer &right) {
    if (left._is_negative != right._is_negative) return false;
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

bool operator!=(const big_integer &left, const big_integer &right) {
    return !(left == right);
}

big_integer big_integer::operator-() const {
    big_integer copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

bool operator<(const big_integer &left, const big_integer &right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    } else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        } else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

bool operator<=(const big_integer &left, const big_integer &right) {
    return (left < right || left == right);
}

big_integer operator+(big_integer left, const big_integer &right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    } else if (right._is_negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= big_integer::BASE;
        if (carry != 0) left._digits[i] -= big_integer::BASE;
    }

    return left;
}

big_integer::big_integer(int i) {
    if (i < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(i) % big_integer::BASE);
    i /= big_integer::BASE;
    if (i != 0) this->_digits.push_back(std::abs(i));
}

big_integer operator-(big_integer left, const big_integer &right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += big_integer::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

big_integer operator*(const big_integer &left, const big_integer &right) {
    big_integer result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                            left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % big_integer::BASE);
            carry = static_cast<int>(cur / big_integer::BASE);
        }
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

void big_integer::_shift_right() {
    if (this->_digits.empty()) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

big_integer operator/(const big_integer &left, const big_integer &right) {
    big_integer b = right;
    b._is_negative = false;
    big_integer result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

big_integer operator %(const big_integer& left, const big_integer& right) {
    big_integer result = left - (left / right) * right;
    if (result._is_negative) result = result + right;
    return result;
}

bool big_integer::odd() const {
    if (this->_digits.empty()) return false;
    return this->_digits[0] & 1;
}

big_integer big_integer::pow(big_integer n) const {
    big_integer a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result = result * a;
        a = a * a;
        n = n / 2;
    }
    return result;
}

big_integer abs(const big_integer &n) {
    if (n._is_negative) {
        return -n;
    } else {
        return n;
    }
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    string a, b, c, d;
    cin >> a >> b >> c >> d;
    big_integer A(a), B(b), C(c), D(d);
    if ((A == 0 && B <= 0) || (C == 0 && D <= 0)) {
        cout << "incorrect";
        return 0;
    }
    if ((A == 1 || B == 0) && (C == 1 || D == 0)) {
        cout << "correct";
        return 0;
    }
    if ((A == 0 && C != 0) || (A != 0 && C == 0)) {
        cout << "incorrect";
        return 0;
    }
    if (A == 0 && C == 0) {
        cout << "correct";
        return 0;
    }
    if (A < 0 && B % 2 == 0) {
        A = -A;
    }
    if (C < 0 && D % 2 == 0) {
        C = -C;
    }
    if (A < 0 && B % 2 != 0 && 0 < C) {
        cout << "incorrect";
        return 0;
    }
    if (C < 0 && D % 2 != 0 && 0 < A) {
        cout << "incorrect";
        return 0;
    }
    if (A < 0) {
        A = -A;
    }
    if (C < 0) {
        C = -C;
    }
    if ((A == 1 || B == 0) && (C == 1 || D == 0)) {
        cout << "correct";
        return 0;
    }
    if (B < 0 && 0 < D) {
        cout << "incorrect";
        return 0;
    }
    if (D < 0 && 0 < B) {
        cout << "incorrect";
        return 0;
    }
    if (D < 0) {
        D = -D;
    }
    if (B < 0) {
        B = -B;
    }
    while (true) {
        if (A < C) {
            swap(A, C);
            swap(B, D);
        }
        if ((A == 1 || B == 0) && (C == 1 || D == 0)) {
            cout << "correct";
            return 0;
        }
        if (A % C != 0) {
            cout << "incorrect";
            return 0;
        }
        big_integer k = A / C;
        A = k;
        D = D - B;
    }
    cout << "correct";
    return 0;
}