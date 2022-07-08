#include <iostream>
#include <cmath>
using namespace std;
class __INT__ {
private :
    int m_n;    
public :
    __INT__(int n = 0) { m_n = n; }
    bool isOdd() const { return (bool)(m_n % 2); }
    bool isEven() const { return !isOdd(); }
    bool isPrime() const;
    void Show() const { cout << m_n; }
    friend __INT__ ADD(const __INT__ &n,const __INT__ &m) {
            return __INT__(n.m_n + m.m_n);
        }
    friend __INT__ SUB(const __INT__ &n,const __INT__ &m) {
            return __INT__(n.m_n - m.m_n);
        }
    friend __INT__ MULT(const __INT__ &n,const __INT__ &m) {
            return __INT__(n.m_n * m.m_n);
        }
    friend double DividE(const __INT__ &n,const __INT__ &m) {
            return 1.0 * n.m_n / m.m_n;
        }
};
bool __INT__::isPrime() const {
    bool is;
    if(m_n < 2) return false;
    for(int i = 2; i < sqrt(m_n) && is; ++i) is = m_n % i;
    return is;
}