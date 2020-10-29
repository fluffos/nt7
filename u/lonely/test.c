string test()
{
        string result, passwd1, passwd2, passwd;
        int i, x, y, a, b, r;
        string str1, str2, str3, str4;
        mixed all = ({ ({2, 7, 8, 1, 0, 3, 6, 5, 4, 9}), 
                       ({9, 4, 6, 0, 2, 7, 1, 8, 5, 3}),
                       ({4, 7, 0, 9, 6, 5, 1, 2, 8, 3}),  
                       ({5, 3, 2, 4, 7, 1, 8, 0, 6, 9}),
                       ({3, 8, 6, 5, 9, 7, 4, 2, 0, 1}),
                       ({7, 5, 2, 9, 0, 6, 8, 4, 1, 3}),
                       ({0, 8, 4, 9, 5, 3, 1, 6, 7, 2}),
                       ({6, 0, 1, 2, 9, 5, 7, 4, 3, 8}),
                       ({5, 9, 1, 3, 0, 7, 8, 4, 6, 2}),
                       ({8, 0, 6, 1, 9, 3, 4, 5, 2, 7}), });

        // 取出4个坐标
        x = random(10);
        y = random(10);
        str1 = to_string(x)+to_string(y);
        x = random(10);
        y = random(10);
        str2 = to_string(x)+to_string(y);
        x = random(10);
        y = random(10);
        str3 = to_string(x)+to_string(y);
        x = random(10);
        y = random(10);
        str4 = to_string(x)+to_string(y);
        
        // CDEFJHIJ
        result = str1+str2+str3+str4; 
        
        b = random(10); // 决定奇偶数B
        r = random(10); // 随机干扰数
        a = random(9);   // 干扰数字的位置A
        result = result[0..a-1]+to_string(r)+result[a..];
        result = to_string(a)+to_string(b)+result;  // 密文
        write(sprintf("%s\n", result));
        
        if( b%2 )
        {
                passwd1 = all[to_int(str1[0..0])][to_int(str1[1..1])]*all[to_int(str2[0..0])][to_int(str2[1..1])];
                passwd2 = all[to_int(str3[0..0])][to_int(str3[1..1])]*all[to_int(str4[0..0])][to_int(str4[1..1])];
                passwd  = to_string(passwd1) + to_string(passwd2);
        }
        else
        {
                passwd1 = all[to_int(str1[0..0])][to_int(str1[1..1])]+all[to_int(str2[0..0])][to_int(str2[1..1])];
                passwd2 = all[to_int(str3[0..0])][to_int(str3[1..1])]+all[to_int(str4[0..0])][to_int(str4[1..1])];
                passwd  = to_string(passwd1) + to_string(passwd2);
        }

                write(sprintf("str1 is %s\n", str1));
                write(sprintf("str2 is %s\n", str2));
                write(sprintf("str3 is %s\n", str3));
                write(sprintf("str4 is %s\n", str4));
                write(sprintf("pwd1 is %d\n", passwd1));
                write(sprintf("pwd2 is %d\n", passwd2));
                write(sprintf("pwd is %s\n", passwd));
        return passwd; // 名文
}

