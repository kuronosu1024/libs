#pragma once
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <array>
#include <string.h>


namespace nskr{
    using ll = long long;
    using lll = __int128;
    // 参考 https://trap.jp/post/2887/
    struct fastIn{
        char* buf;
        char* pos = buf;
        fastIn() {
            struct stat st;
            fstat(0, &st);
            buf = (char*)mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0);
            pos = buf;
        }
        ll nextNum(){
            ll ret = 0; bool m = false;
            while (*pos != '-' && (*pos < '0' || *pos > '9') ) pos++;
            if(*pos == '-'){ m = true; pos++; } 
            while ('0' <= *pos && *pos <= '9'){
                ret = ret*10+(*pos - '0');
                pos++;
            }
            return ret * (m?-1:1);
        }
        lll nextNum128(){
            ll ret = 0; bool m = false;
            while (*pos != '-' && (*pos < '0' || *pos > '9') ) pos++;
            if(*pos == '-'){ m = true; pos++; } 
            while ('0' <= *pos && *pos <= '9'){
                ret = ret*10+(*pos - '0');
                pos++;
            }
            return ret * (m?-1:1);
        }
        
    } fIn;

    static constexpr auto makeLUT () {
        std::array<char, 40000> res{};
        char *p = res.data();
        char a = '0', b = '0', c = '0', d = '0';
        do {
            *p++ = a, *p++ = b, *p++ = c, *p++ = d;
        } while (
            d++ < '9' || (d = '0',
                c++ < '9' || (c = '0',
                    b++ < '9' || (b = '0', a++ < '9')
                )
            )
        );
        return res;
    };
    static constexpr auto LUT = makeLUT();

    struct fastOut{
        char buf[1<<26];
        char* pos = buf;
        ~fastOut(){
            fwrite(buf, 1, pos-buf, stdout);
        }

        static constexpr lll p10(int n){
            lll res = 1;
            for(int i = 0; i < n; i++) res *= 10;
            return res;
        }

        int getlen(lll x){
            if (x < p10(1)) return 1;
            if (x < p10(2)) return 2;
            if (x < p10(3)) return 3;
            if (x < p10(4)) return 4;
            if (x < p10(5)) return 5;
            if (x < p10(6)) return 6;
            if (x < p10(7)) return 7;
            if (x < p10(8)) return 8;
            if (x < p10(9)) return 9;
            if (x < p10(10)) return 10;
            if (x < p10(11)) return 11;
            if (x < p10(12)) return 12;
            if (x < p10(13)) return 13;
            if (x < p10(14)) return 14;
            if (x < p10(15)) return 15;
            if (x < p10(16)) return 16;
            if (x < p10(17)) return 17;
            if (x < p10(18)) return 18;
            if (x < p10(19)) return 19;
            if (x < p10(20)) return 20;
            if (x < p10(21)) return 21;
            if (x < p10(22)) return 22;
            if (x < p10(23)) return 23;
            if (x < p10(24)) return 24;
            if (x < p10(25)) return 25;
            if (x < p10(26)) return 26;
            if (x < p10(27)) return 27;
            if (x < p10(28)) return 28;
            if (x < p10(29)) return 29;
            if (x < p10(30)) return 30;
            if (x < p10(31)) return 31;
            if (x < p10(32)) return 32;
            if (x < p10(33)) return 33;
            if (x < p10(34)) return 34;
            if (x < p10(35)) return 35;
            if (x < p10(36)) return 36;
            if (x < p10(37)) return 37;
            if (x < p10(38)) return 38;
            return 39;
        }


        void printNum(lll x){
            if(x==0) {*pos++ = '0'; return;}
            if(x<0) {*pos++ = '-'; printNum(-x); return;}
            int len = getlen(x);
            char* p = pos + len;
            pos = p;
            while(x>10000){
                int rem = x%10000;
                x /= 10000;
                p -= 4;
                memcpy(p, &LUT[rem*4], 4);
            }
            while(x>=10){
                *--p = (x%10) + '0';
                x /= 10;
            }
            *--p = x + '0';
        }
    } fOut;
}