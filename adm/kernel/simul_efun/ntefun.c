#include <ansi.h>

#define SUCCESS 0
#define FAIL 1

int mapping_eqv(mapping m1, mapping m2);

#ifndef __PACKAGE_DBASE__
varargs mixed query(string prop, object ob)
{
    // debug_message("ob = " + ob);
    if (!objectp(ob))
    {
        ob = previous_object();
    }
    // debug_message("ob = " + ob);
    // debug_message("prop = " + prop);

    return ob->query_db(prop);
}

varargs mixed delete(string prop, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->delete_db(prop);
}

varargs mixed set(string prop, string msg, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->set_db(prop, msg);
}

varargs mixed addn(string prop, string msg, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->add(prop, msg);
}

varargs mixed query_temp(string prop, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->query_temp_db(prop);
}

varargs mixed delete_temp(string prop, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->delete_temp_db(prop);
}

varargs mixed set_temp(string prop, string msg, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->set_temp_db(prop, msg);
}

varargs mixed addn_temp(string prop, string msg, object ob)
{
    if (!objectp(ob))
    {
        ob = previous_object();
    }

    return ob->add_temp_db(prop, msg);
}
#endif

mixed f_rmtree(string dir)
{
    mixed *res;
    string *files;

    if (!previous_object())
        return 0;

    if (!is_root(previous_object()))
        return 0;

    res = allocate(2);
    res[0] = allocate(0);
    res[1] = allocate(0);

    if (dir[ < 1] != '/')
        dir += "/";

    if (file_size(dir) != -2)
        return 0;

    if (sizeof(files = get_dir(dir)) < 1)
        return 0;

    foreach (string file in files)
    {
        if (file_size(dir + file) == -2)
            f_rmtree(dir + file);
        else if (rm(dir + file))
            res[SUCCESS] += ({dir + file});
        else
            res[FAIL] += ({dir + file});
    }

    if (rmdir(dir))
        res[SUCCESS] += ({dir});
    else
        res[FAIL] += ({dir});

    return res;
}

mixed rmtree(string dir)
{
    mixed *res;

    if (!previous_object())
        return 0;

    if (!is_root(previous_object()))
        return 0;

    res = allocate(2);
    res[0] = allocate(0);
    res[1] = allocate(0);

    res = f_rmtree(dir);

    return res;
}

mixed f_cptree(string dir, string dst)
{
    mixed *res;
    string *files;

    if (!previous_object())
        return 0;

    if (!is_root(previous_object()))
        return 0;

    res = allocate(2);
    res[0] = allocate(0);
    res[1] = allocate(0);

    if (dir[ < 1] != '/')
        dir += "/";

    if (file_size(dir) != -2)
        return 0;

    if (file_size(dst) != -2)
    {
        if (mkdir(dst))
            res[SUCCESS] += ({dst});
        else
            res[FAIL] += ({dst});
    }

    if (sizeof(files = get_dir(dir)) < 1)
        return 0;

    foreach (string file in files)
    {
        if (file_size(dir + file) == -2)
            f_cptree(dir + file, dst + file);
        else if (cp(dir + file, dst + file))
            res[SUCCESS] += ({dst + file});
        else
            res[FAIL] += ({dst + file});
    }

    return res;
}

mixed cptree(string dir, string dst)
{
    mixed *res;

    if (!previous_object())
        return 0;

    if (!is_root(previous_object()))
        return 0;

    res = allocate(2);
    res[0] = allocate(0);
    res[1] = allocate(0);

    // 2b14中可用下面的方式
    // string *res = allocate(2, allocate(0));

    res = f_cptree(dir, dst);

    return res;
}

int range_random(int i, int j)
{
    return random(i < j ? j - i + 1 : i - j + 1) + ((i < j) ? i : j);
}

void add_slash(string path)
{
    if (path[ < 1] != '/')
        path += "/";
}

string *deep_path_list(string dir)
{
    int i;
    string *flist, *result = ({});
    string file;

    flist = get_dir(dir);

    for (i = 0; i < sizeof(flist); i++)
    {
        file = dir + flist[i];

        if (file_size(file + "/") == -2)
            result += deep_path_list(file + "/");
        else
            result += ({file});
    }

    return result;
}

// 反转 arr 阵列，使最后一个元素变成第一个元素，元素位置完全对调。
void reverse_array(string *arr)
{
    if (!arrayp(arr) || !sizeof(arr))
        return;

    foreach (mixed element in arr)
        arr = ({element}) + arr[0.. < 2];
}
/*
int array_eqv(mixed a1, mixed a2)
{
        int a_size;
        string a_type;

        if( !a1 && !a2 )
                return 1;

        a_size = sizeof(a1);
        if( a_size != sizeof(a2) )
                return 0;

        if( a_size < 1 ) return 1;

        for (int i = 0; i < sizeof(a1); i++) {
                a_type = typeof(a1[i]);
                if( a_type != typeof(a2[i]) )
                        return 0;
                else
                if( a_type == "mapping" && !mapping_eqv(a1[i], a2[i]) )
                        return 0;
                else
                if( a_type == "array" && !array_eqv(a1[i], a2[1]) )
                        return 0;
                else
                if( a1[i] != a2[i] )
                        return 0;
        }
        return 1;
}

int mapping_eqv(mapping m1, mapping m2)
{
        string index, m_type;

        if( !m1 && !m2 )
                return 1;

        if( sizeof(m1) != sizeof(m2) )
                return 0;

        if( sizeof(m1) < 1 ) return 1;

        foreach (index in keys(m1)) {
                m_type = typeof(m1[index]);
                if( m_type != typeof(m2[index]) )
                        return 0;
                else
                if( m_type == "mapping" && !mapping_eqv(m1[index], m2[index]) )
                        return 0;
                else
                if( m_type == "array" && !array_eqv(m1[index], m2[index]) )
                        return 0;
                else
                if( m1[index] != m2[index] )
                        return 0;
        }
        return 1;
}
*/
int array_eqv(mixed arr1, mixed arr2)
{
    int s_arr = sizeof(arr1);
    if (s_arr != sizeof(arr2))
        return 0;
    if (s_arr < 1)
        return 1;
    for (int i = 0; i < sizeof(arr1); i++)
    {
        if (arrayp(arr1[i]) && arrayp(arr2[i]))
        {
            if (!array_eqv(arr1[i], arr2[i]))
                return 0;
        }
        else if (mapp(arr1[i]) && mapp(arr2[i]))
        {
            if (!mapping_eqv(arr1[i], arr2[i]))
                return 0;
        }
        else if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

int mapping_eqv(mapping map1, mapping map2)
{
    int m_arr = sizeof(map1);
    mixed m_keys1, m_keys2;

    if (m_arr != sizeof(map2))
        return 0;
    if (m_arr < 1)
        return 1;
    m_keys1 = keys(map1);
    m_keys2 = keys(map2);

    for (int i = 0; i < sizeof(m_keys1); i++)
    {
        if (mapp(m_keys1[i]) && mapp(m_keys2[i]))
        {
            if (!mapping_eqv(m_keys1[i], m_keys2[i]))
                return 0;
        }
        else if (arrayp(m_keys1[i]) && arrayp(m_keys2[i]))
        {
            if (!array_eqv(m_keys1[i], m_keys2[i]))
                return 0;
        }
        else if (m_keys1[i] != m_keys2[i])
        {
            return 0;
        }

        // Value check
        if (mapp(map1[m_keys1[i]]) && mapp(map2[m_keys2[i]]))
        {
            if (!mapping_eqv(map1[m_keys1[i]], map2[m_keys2[i]]))
                return 0;
        }
        else if (arrayp(map1[m_keys1[i]]) && arrayp(map2[m_keys1[i]]))
        {
            if (!array_eqv(map1[m_keys1[i]], map2[m_keys2[i]]))
                return 0;
        }
        else if (map1[m_keys1[i]] != map2[m_keys2[i]])
            return 0;
    }
    return 1;
}

// 将 int 阵列元素全部相加
int int_array_addition(int *arr)
{
    int total;

    foreach (int i in arr)
        total += i;

    return total;
}

// 机率
// ([ elem1 : prob1, elem2 : prob2,... ])
mixed probability(mapping data)
{
    string *keys = keys(data);
    int *values = values(data);
    int prob, size = sizeof(data);

    while (size--)
    {
        prob = int_array_addition(values[0..size]);

        if (random(prob) < values[size])
            return keys[size];
    }
}

string big_number_check(mixed bn)
{
    int negtive;

    if (!bn)
        return 0;

    if (intp(bn))
        return bn + "";
    else if (!stringp(bn))
        return 0;

    if (bn[0] == '-')
    {
        bn = bn[1..];
        negtive = 1;
    }

    bn = replace_string(bn, ",", "");

    /*
        if( bn[<1] == 'k' || bn[<1] == 'K' )
                bn = bn[0..<2]+"000";
        else if( bn[<1] == 'm' || bn[<1] == 'M' )
                bn = bn[0..<2]+"000000";
        else if( bn[<1] == 'g' || bn[<1] == 'G' )
                bn = bn[0..<2]+"000000000";
        */
    while (bn[0] == '0')
        bn = bn[1..];

    foreach (int i in bn)
        if (i < '0' || i > '9')
            return 0;

    if (bn == "")
        return 0;
    else
        return negtive ? "-" + bn : bn;
}

/*
名称：
        object_parse() - 传回符合条件的物件。
语法：
        object object_parse(string arg, object* objects);
用法：
        依照字串 arg 的内容，由物件阵列 objects 之中取得正确的物件元素
        并传回此物件，若没有任何物件元素符合条件，则回传 0。

        例如
                arg 为 "rice 2"
                则会搜寻物件阵列 objects 中第二个可以被称为 rice 的物件
                即第二个 id("rice") 回传 1 值的物件
*/
object object_parse(string arg, object *objects)
{
    int which = 1;
    int which_temp;
    string amount;
    string objectname;
    object ob;

    if (!arg || !arg[0] || !sizeof(objects))
        return 0;

    // 试着取得 which
    if (sscanf(arg, "%s %d", objectname, which) != 2)
        objectname = arg;

    if (which < 1)
        return 0;

    // 若送入的语法包括 amount, 则取出 amount 的部分
    if (sscanf(objectname, "%s %s", amount, objectname) == 2)
    {
        if (!big_number_check(amount))
            objectname = amount + " " + objectname;
    }

    objectname = lower_case(objectname);

    which_temp = which;

    foreach (ob in objects)
        if (ob->query_id(1) == objectname && !(--which_temp))
            return ob;

    foreach (ob in objects)
        if (ob->id(objectname) && !(--which))
            return ob;

    return 0;
}

/*
名称：
        process_function() - 依序执行传入的阵列内容。
语法：
        void process_function(array arr);
用法：
        依照顺序执行传入的阵列内容, 若阵列内容为整数则代表延迟
        其整数秒再继续执行接下来的元素, 若元素为函式指标则会执
        行其函式, 若函式回传 -1, 则会立即中止整个 process, 接下
        来的元素便不会被执行。

        ex: arr = ({ 2, <function1>, 3, <function2>, <function3> })
        则 process_function(arr) 后会先间隔两秒后再执行 function1,
        接着再间隔 3 秒后再连续执行 function2 与 function3
*/
void process_function(string *fp)
{
    int second;

    if (!sizeof(fp))
        return;

    if (functionp(fp[0]))
    {
        catch
        {
            if (evaluate(fp[0]) == -1)
                return;
        };
    }

    if (intp(fp[0]))
        second = atoi(fp[0]);

    call_out((
                 : process_function:),
             second, fp[1..]);
}

// 单引号语法解析
string *single_quote_parse(string p)
{
    int i, j, size;
    string *ret = allocate(0), *tmp = explode(p, " ");

    size = sizeof(tmp);

    for (i = 0; i < size; i++, j++)
    {
        if (tmp[i][0] == '\'')
        {
            ret += ({tmp[i][1..]});

            while (++i < size)
            {
                ret[j] += " " + tmp[i];

                if (tmp[i][0] && tmp[i][ < 1] == '\'')
                {
                    ret[j] = ret[j][0.. < 2];
                    break;
                }
            }
        }
        else
            ret += ({tmp[i]});
    }

    return ret - ({""});
}

string convert_color(string arg)
{
    arg = replace_string(arg, "BLK", BLK);
    arg = replace_string(arg, "RED", RED);
    arg = replace_string(arg, "GRN", GRN);
    arg = replace_string(arg, "YEL", YEL);
    arg = replace_string(arg, "BLU", BLU);
    arg = replace_string(arg, "MAG", MAG);
    arg = replace_string(arg, "CYN", CYN);
    arg = replace_string(arg, "WHT", WHT);
    arg = replace_string(arg, "HIR", HIR);
    arg = replace_string(arg, "HIG", HIG);
    arg = replace_string(arg, "HIY", HIY);
    arg = replace_string(arg, "HIB", HIB);
    arg = replace_string(arg, "HIM", HIM);
    arg = replace_string(arg, "HIC", HIC);
    arg = replace_string(arg, "HIW", HIW);
    arg = replace_string(arg, "NOR", NOR);

    return arg;
}

varargs string column_string(string msg1, string msg2, int width)
{
    string *field1, *field2;
    string msg;
    int max_line, i;
    int len;

    if (msg1 == "")
        return msg2;
    else
        field1 = explode(msg1, "\n");

    if (msg2 == "")
        return msg1;
    else
        field2 = explode(msg2, "\n");

    max_line = (sizeof(field1) > sizeof(field2)) ? sizeof(field1) : sizeof(field2);

    msg = "";

    for (i = 0; i < max_line; i++)
    {
        if (i < sizeof(field1))
        {
            len = strlen(filter_color(field1[i], 1));
            if (width > 0 && width > len)
            {
                msg += field1[i];
                msg += repeat_string(" ", (width - len));
            }
            else if (width > 0 && width < len)
                msg += field1[i][0..width - 1];
            else
                msg += field1[i];
        }

        if (i < sizeof(field2))
        {
            if (width > 0 && i >= sizeof(field1))
                msg += repeat_string(" ", width);

            msg += field2[i];
        }
        msg += "\n";
    }
    return msg;
}

string base_dir(object obj)
{
    string filename;
    int at;

    filename = base_name(obj);
    at = strsrch(filename, "/", -1);
    filename = filename[0..at];
    return filename;
}

varargs string format_string(string str, int wrap, int ignore_return)
{
    string tmp = "";
    int len = 0, ansi = 0, clen = 0; // clen 是已出现的汉字个数。

    if (!str || !stringp(str))
        return 0;

    if (!wrap)
        wrap = 56;

    foreach (int ch in str)
    {
        if (ch == '\n' && ignore_return) // return char
            continue;                    // ignore it.

        tmp += sprintf("%c", ch);

        if (ch == 0x1b)
        { // esc char
            ansi = 1;
        }
        if (!ansi)
        {
            len++;
            if (ch > 127)
                clen++;
            // printf("ch %c clen: %d len %d ch=%d\n", ch, clen,len,ch);
        }
        else if (ch == 'm' || ch == 'H' || ch == 'J')
        {
            ansi = 0;
        }
        if (len >= wrap)
            if ((!(clen % 2)) || (ch == ' '))
            {
                // printf("str: %s ch %c clen: %d len %d ch=%d\n", tmp, ch, clen,len,ch);
                tmp += "\n";
                wrap = 60;
                len = 0;
            }
    }
    return tmp + "\n";
}

varargs int new_random(int random_access)
{
    int x = 1, y;

    if (random_access < 30000)
        return random(random_access);

    else if (random_access > 600000000)
    {
        random_access /= 123;
        x = 150;
    }

    y = sqrt(efun::to_float(random_access));
    return x * random(y) * random(y);
}

mixed count(mixed a, mixed b, mixed c)
{
    string *usercount = allocate(3);
    mixed result;

    usercount[0] = a;
    usercount[1] = b;
    usercount[2] = c;
    usercount = map(usercount, (: CHINESE_D->chinese_to_number($1) :));
    result = implode(usercount, (: $1 + $2:));
    return result;
}

#ifdef __PACKAGE_ARITH_OPERATOR__
string count_add(mixed n1, mixed n2)
{
    return efun::count(n1, "+", n2);
}

string count_mul(mixed n1, mixed n2)
{
    return efun::count(n1, "*", n2);
}

string count_sub(mixed n1, mixed n2)
{
    return efun::count(n1, "-", n2);
}

string count_div(mixed n1, mixed n2)
{
    return efun::count(n1, "/", n2);
}

int count_lt(mixed n1, mixed n2)
{
    return efun::count(n1, "<", n2);
}

int count_gt(mixed n1, mixed n2)
{
    return efun::count(n1, ">", n2);
}

int count_le(mixed n1, mixed n2)
{
    return efun::count(n1, "<=", n2);
}

int count_ge(mixed n1, mixed n2)
{
    return efun::count(n1, ">=", n2);
}

int count_eq(mixed n1, mixed n2)
{
    return efun::count(n1, "==", n2);
}

// 大数次方运算
string big_number_pow(mixed number, mixed exponent)
{
    mixed result = number;

    if (count(exponent, "<", 0))
        error("exponent must be > 0.");

    if (count(exponent, "==", 0))
        return "1";

    while (count(exponent = count(exponent, "-", 1), ">", 0))
        result = count(result, "*", number);

    return result;
}

/*
string big_number_random(string count)
{
        int a, b;
        string result;
        string part;

        a = sizeof(count);

        if( a < 10 ) {
                result = to_string(random(atoi(count)));
                return result;
        }

        result = repeat_string("0", random(a) + 1);

        if( sizeof(result) != a ) {
                foreach(int ref i in result)
                        i = random(10) + 48;
        } else {
                part = result[1..];
                foreach(int ref i in part)
                        i = random(10) + 48;

                // 如果 part > count[1..]
                if( count_ge(part, count[1..]) )
                        b = random(count[0] - 48);
                else
                        b = random(count[0] - 48 + 1);

                result = to_string(b) + part;
        }

        return result;
}
*/

#endif

#ifndef __PACKAGE_TRIM__
string trim(string str)
{
    int i, j;
    int len = strlen(str);

    for (i = 0; i < len; ++i)
        if (str[i] != ' ')
            break;

    for (j = 1; j <= len; ++j)
        if (str[ < j] != ' ')
            break;

    return str[i..< j];
}
#endif
