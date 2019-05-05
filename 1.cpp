#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <unordered_map>
#include <climits>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <type_traits>
#include <random>
#include <ctime>
#include <time.h>

using namespace std;

string my_rnd(int k) {
    srand(clock());
    string res = "";
    int r = 0;
    for (int i = 0; i < k; i++) {
        r = rand() % 10;
        if (i == 0 && r == 0) r += 1;
        res += to_string(r);
    }
    return res;
}

string zeros(double k) {
    string res = "";
    for (double i = 0; i < k; i++) {
        res += '0';
    }
    return res;
}

string sum(string f, string s) {
    double fl = f.length();
    double sl = s.length();
    if (fl < sl)
        f = zeros(sl - fl) + f;
    if (sl < fl)
        s = zeros(fl - sl) + s;
    double l = max(fl, sl);
    string res = "";
    int rem = 0;
    int cur = 0;
    for (double i = l - 1; i >= 0; i--) {
        cur = (f[i] - '0') + (s[i] - '0') + rem;
        if (cur < 10) {
            res += to_string(cur);
            rem = 0;
        }
        else {
            res += to_string(cur % 10);
            rem = 1;
        }
        cur = 0;
    }
    if (res[l - 1] == 0) res += '1';
    if (rem) res += to_string(rem);
    string res2 = "";
    for (int i = res.length() - 1; i >= 0; i--) {
        res2 += res[i];
    }
    return res2;
}

bool isEven(string s) {
    int l = s.length();
    return !(s[l - 1] % 2);
}

bool isZero(string s) {
    int l = s.length();
    int count = 0;
    for (int i = 0; i < l; i++)
        count += s[i] - '0';
    return !(count);
}

string longDivision(string number, int divisor) { 
    string ans; 
    int idx = 0; 
    int temp = number[idx] - '0'; 
    while (temp < divisor) 
       temp = temp * 10 + (number[++idx] - '0'); 
    while (number.size() > idx) { 
        ans += (temp / divisor) + '0'; 
        temp = (temp % divisor) * 10 + number[++idx] - '0'; 
    } 
    if (ans.length() == 0) 
        return "0";  
    return ans; 
} 

string minus1(string s) {
    string res = "";
    int l = s.length();
    int rem = 0;
    for (int i = l - 1; i >= 0; i--) {
        if (rem) {
            if (s[i] - '0' == 0) {
                res += '9';
                rem = 1;
            }
            else {
                res += to_string(s[i] - '0' - 1);
                rem = 0;
            }
            
        }
        else {
            if (i == l - 1) {
                if (s[i] - '0' > 0){
                    res += to_string(s[i] - '0' - 1);
                }
                else {
                    res += '9';
                    rem = 1;
                }
            }
            else {
                res += s[i];
            }
        }
    }
    string res2 = "";
    for (int i = res.length() - 1; i >= 0; i--) {
        res2 += res[i];
    }
    return res2;
}

string SchMult(string f1, string s1) {
    vector<string> v;
    string elem = "";
    double l = s1.length();
    for (int i = 0; i < l; i++) {
        string str = "";
        elem = "0";
        for (int j = 0; j < s1[l - 1 - i] - '0'; j++) {
            elem = sum(elem, f1);
        }
        str += elem + zeros(i);
        v.push_back(str);
    }
    elem = v[0];
    for (int i = 1; i < v.size(); i++) {
        elem = sum(elem, v[i]);
    }
    return elem;
}

string DivCo(string a, string b) {
    if (isZero(a)) return "0";
    if (isEven(a)) return SchMult(to_string(2), DivCo(longDivision(a, 2), b));
    return sum(b, SchMult(to_string(2), DivCo(longDivision(minus1(a), 2), b)));
}

std::vector< pair<double, double> > v;

class Multiplicator {
public:
    Multiplicator (string first, string second) : first(first), second(second) {}

    string rnd(int k) { return my_rnd(k); }

    string Mult() { return SchMult(first, second); }

    string DaC() { return DivCo(first, second); }

    void testing(int N) {
        int t = 1;
        while (t <= N) {
            double t1 = 0, t2 = 0;
            pair<double, double> time_elem;
            for (int i = 1; i < 1000; i++) {
                string fir = my_rnd(t);
                string sec = my_rnd(t);
                Multiplicator one(fir, sec);
                clock_t f = clock();
                one.Mult();
                f = clock() - f;
                t1 += (double)(f)/CLOCKS_PER_SEC;
                f = clock();
                one.DaC();
                f = clock() - f;
                t2 += (double)(f)/CLOCKS_PER_SEC;
            }
            time_elem.first = t1/1000.0;
            time_elem.second = t2/1000.0;
            v.push_back(time_elem);
            t++;
        }
    }
 
private:
    string first, second;
};

void writeCSV() {
    ofstream file;
    file.open ("time.csv");
    Multiplicator one("12", "12");
    one.testing(5);
    for (int i = 0; i < 5; i++) {
        file << i+1 << "," << v[i].first << "," << v[i].second << endl;
    }
}

int main() {
    writeCSV();
}



