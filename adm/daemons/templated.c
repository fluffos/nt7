// This program is a part of NITAN MudLIB
// templated.c

// 模板精灵工作的流程：

// 一、创建物件方式
//  1、获得模板基准文件名，创建基准物件。
//  2、获得模板文件将要处理的 DBASE 的格式。
//  3、获得物件的所有数据，根据传入的参数(arg)找到本次物件的数据。
//  4、如果有专门的基准物件，则创建专门的。
//  5、设定 DBASE(m[DBASE_KEY1] = DBASE VALUE)。
//  6、呼叫基准物件中的函数(call_other(ob, "function", argument))。
//  7、返回该物件。

// 模板文件准备的数据结构：
// mixed *dbase_format = ({ DBASE_KEY1, DBASE_KEY2, });
// mapping object_data = ({ "arg1" : ({ ({ DBASE_VALUE1, DBASE_VALUE2, }),
//                         ([ "function1" : ({ argument1, }) ]), }) });
// 或下面结构
// mapping object_data = ({ "arg1" : ({ ([ DBASE_KEY1 : DBASE_VALUE1, DBASE_KEY2 : DBASE_VALUE2, ]),
//                         ([ "function1" : ({ argument1, }) ]), , "extra_base_file", }) });

// 模板物件提供的接口函数：
// query_base_file()       - 基准物件名
// query_dbase_format()    - dbase 格式
// query_function_format() - function 格式
// query_entire_data()     - 所有数据
// query_template_data()   - 指定的数据

#include <ansi.h>
#include <template.h>


#define COMMENT_ENTRY   "/* COMMENT_ENTRY */"
#define COMMENT_EXIT    "/* COMMENT_EXIT  */"

#define NAME_ENTRY      "/* NAME_ENTRY */"
#define NAME_EXIT       "/* NAME_EXIT  */"

#define DBASE_ENTRY     "/* DBASE_ENTRY */"
#define DBASE_EXIT      "/* DBASE_EXIT  */"

#define FUNCTION_ENTRY  "/* FUNCTION_ENTRY */"
#define FUNCTION_EXIT   "/* FUNCTION_EXIT  */"

#ifdef DEBUG
#define monitor(x)              CHANNEL_D->do_channel(this_object(), "sys", x)
#else
#define monitor(x)
#endif

// 创建物件
varargs object create_object(string file, string arg, mapping dbase_data,
                             int model, mapping function_data)
{
        object  tob;     // 模板物件
        object  ob;      // 创建的物件

        string  template;// 模板文件名
        string  type;    // 所属类型

        int     full;    // 是否在 data 中指定 key 和 value
        mixed   format;  // dbase、function 格式
        mixed   data;    // 数据
        mixed   key;     // 数据(mapping)中的一个 key
        mapping dbase;   // 物件的 dbase
        int     i, max;  // 计数器
        object  shadow_ob;
        mapping applied_prop, temp;
        string *apply;

        if( file[<2..<1] != FILE_EXTENSION )
                file += FILE_EXTENSION;

        if( file_size(file) < 1 )
                return 0;

        if( !objectp(tob = find_object(file)) &&
                catch(tob = load_object(file)) )
                return 0;

        if( !sscanf(file, TEMPLATE_DIR "%s.c", template) ) {
                // 非模板文件创造物件
                if( !objectp(ob = new(file)) )
                        return 0;

                dbase = ob->query_entire_dbase();
                if( sizeof(dbase_data) ) {
                        format = keys(dbase_data);
                        foreach( key in format ) {
                                if( !model )
                                        dbase[key] = dbase_data[key];
                                else
                                {
                                        if( mapp(dbase[key]) && mapp(dbase_data[key]) )
                                        {
                                                applied_prop = copy(dbase[key]);
                                                temp = copy(dbase_data[key]);
                                                apply = keys(temp);
                                                for( i = 0; i < sizeof(apply); i++ )
                                                {
                                                        if( undefinedp(applied_prop[apply[i]]) )
                                                                applied_prop[apply[i]] = temp[apply[i]];
                                                        else
                                                        {
                                                                if( (mapp(applied_prop[apply[i]]) && mapp(temp[apply[i]])) ||
                                                                    (arrayp(applied_prop[apply[i]]) && arrayp(temp[apply[i]])) )
                                                                        applied_prop[apply[i]] = applied_prop[apply[i]] + temp[apply[i]];
                                                                else
                                                                        applied_prop[apply[i]] = temp[apply[i]];
                                                        }
                                                }
                                                dbase[key] = copy(applied_prop);
                                        }
                                        else if( arrayp(dbase[key]) && arrayp(dbase_data[key]) )
                                                dbase[key] = dbase[key] + dbase_data[key];
                                        else
                                                dbase[key] = dbase_data[key];
                                }
                        }

                        if( shadow_ob = ob->query_default_object() )
                                dbase["shadow_ob"] = shadow_ob;

                        dbase["set_data"] = 1;
                }

                // 设置名称
                if( member_array(F_NAME, deep_inherit_list(ob)) != -1 ) {
                        if( !undefinedp(dbase_data["name"]) )
                                ob->set_name(dbase_data["name"], ({ arg }));
                        else
                                X_NameD->x_name(ob, arg);

                        dbase["set_data"] = 1;
                }

                if( sizeof(function_data) ) {
                        set("function", function_data, ob);
                        format = keys(function_data);
                        foreach( key in format )
                                call_other(ob, key, function_data[key]);
                }

                return ob;
        }

        // 模板文件创造物件
        if( !arrayp(data = tob->query_template_data(arg)) || !sizeof(data) )
                return 0;

        // 是否有专门的基准文件？
        if( sizeof(data) > EXTRA_BASE_DATA )
                file = data[EXTRA_BASE_DATA];

        if( sizeof(data) <= EXTRA_BASE_DATA || file_size(file) <= 0 ) {
                // 有无基准物件文件
                if( !stringp(file = tob->query_base_file()))
                        return 0;
        }

        // 根据基准文件创建的物件能否加载？
        if( !objectp(ob = new(file)) )
                return 0;

        // 配置 dbase 数据
        if( !arrayp(format = tob->query_dbase_format()) || !sizeof(format) )
                full = 1;
        else    full = 0;

        // 将模板中的 dbase 数据转入物件中
        dbase = ob->query_entire_dbase();
        switch (full)
        {
        // 采用全格式模式
        case 1:
                if( !mapp(data[DBASE_DATA]) ||
                    !sizeof(data[DBASE_DATA]) )
                        return 0;

                format = keys(data[DBASE_DATA]);
                foreach( key in format )
                        dbase[key] = data[DBASE_DATA][key];

                break;
        // 采用格式对应模式
        default:
                if( !arrayp(format) )
                        return 0;

                // 如果格式中只有一项，而数据又不是数组型的，
                // 则直接把 dbase 中的那唯一的格式设为数据。
                max = sizeof(format);
                if( max == 1 && !arrayp(data[DBASE_DATA]) )
                        dbase[format[0]] = data[DBASE_DATA];
                else {
                        for (i = 0; i < max; i++)
                                dbase[format[i]] = data[DBASE_DATA][i];
                }

                break;
        }

        // 处理外部传入的 dbase_data 数据
        if( sizeof(dbase_data) ) {
                format = keys(dbase_data);
                foreach( key in format ) {
                        if( !model )
                                dbase[key] = dbase_data[key];
                        else
                        {
                                if( mapp(dbase[key]) && mapp(dbase_data[key]) )
                                {
                                        applied_prop = copy(dbase[key]);
                                        temp = copy(dbase_data[key]);
                                        apply = keys(temp);
                                        for( i = 0; i < sizeof(apply); i++ )
                                        {
                                                if( undefinedp(applied_prop[apply[i]]) )
                                                        applied_prop[apply[i]] = temp[apply[i]];
                                                else
                                                {
                                                        if( (mapp(applied_prop[apply[i]]) && mapp(temp[apply[i]])) ||
                                                            (arrayp(applied_prop[apply[i]]) && arrayp(temp[apply[i]])) )
                                                                applied_prop[apply[i]] = applied_prop[apply[i]] + temp[apply[i]];
                                                        else
                                                                applied_prop[apply[i]] = temp[apply[i]];
                                                }
                                        }
                                        dbase[key] = copy(applied_prop);
                                }
                                if( arrayp(dbase[key]) && arrayp(dbase_data[key]) )
                                        dbase[key] = dbase[key] + dbase_data[key];
                                else
                                        dbase[key] = dbase_data[key];
                        }

                        if( shadow_ob = ob->query_default_object() )
                                dbase["shadow_ob"] = shadow_ob;

                        dbase["set_data"] = 1;
                }
        }

        if( member_array(F_NAME, deep_inherit_list(ob)) != -1 ) {
                // 设置名称
                if( !undefinedp(dbase_data["name"]) ) {
                        i = strsrch(template, "/") + 1;
                        type = template[i..<1];

                        ob->set_name(dbase_data["name"], ({ arg, type }));
                } else
                        ob->set_name(dbase["name"], ({ arg, type }));

                dbase["set_data"] = 1;
        }

        // 是否预备了 function (模板数据的第二项)的格式？
        // 若无，则采用全格式模式，即模板数据的首项为
        // mapping。否则就采用 array 格式。
        if( !arrayp(format = tob->query_function_format()) || !sizeof(format) )
                full = 1;
        else
                full = 0;

        // 呼叫函数数据
        // 对物件呼叫模板中指定的函数
        if( sizeof(data) > FUNCTION_DATA &&
           // (mapp(data[FUNCTION_DATA]) || arrayp(data[FUNCTION_DATA])) &&
           sizeof(data[FUNCTION_DATA]) ) {
                // 使用全格式模式
                if( full ) {
                        format = keys(data[FUNCTION_DATA]);

                        foreach( key in format ) {
                                monitor(sprintf("create_object执行%O->%s(%O)", ob, key,
                                                data[FUNCTION_DATA][key]));
                                call_other(ob, key, data[FUNCTION_DATA][key]);
                        }
                } else { // 使用格式对应模式
                        if( !arrayp(format) )
                                return 0;

                        // 如果格式中只有一项，而数据又不是数组型的，
                        // 则直接以这一项为参数呼叫那个函数。
                        if( sizeof(format) == 1 && !arrayp(data[FUNCTION_DATA]) )
                                call_other(ob, format[0], data[FUNCTION_DATA]);
                        else {
                                max = sizeof(format);

                                for( i = 0; i < max; i++ ) {
                                        // 若这个函数无须参数
                                        if( undefinedp(data[DBASE_DATA][i]) )
                                                call_other(ob, format[i]);
                                        else
                                                call_other(ob, format[i], data[DBASE_DATA][i]);
                                }
                        }
                }
        }

        // 处理外部传入的 function_data 数据
        if( sizeof(function_data) ) {
                dbase["function"] = function_data;
                format = keys(function_data);
                foreach( key in format )
                        call_other(ob, key, function_data[key]);
        }

        return ob;
}

// add mapping
protected string prop_segment(mapping p, string path)
{
        string path2;
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path2 = path + ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path2);
                } else
                {
                        if( arrayp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %O);\n",
                                       path + ks[i], p[ks[i]]);
                        else
                        if( stringp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", \"%s\");\n",
                                       path + ks[i], (string)p[ks[i]]);
                        else
                        if( intp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %d);\n",
                                       path + ks[i], (int)p[ks[i]]);
                }
        }

        return buf;
}

// 编译为文件
varargs string create_file(string tfile, string arg, mapping dbase_data,
                           int model, mapping function_data)
{
        string  bfile;          // 基准物件文件名
        string  cfile;          // 待编译的文件名
        string  type;           // 物件类型
        string  name;

        string  template;       // 模板文件名
        string *content;        // 编译的文件内容
        string  content_str;    // 编译的文件内容
        string  content_line;   // 编译中一行的内容

        int     i;              // 计数器
        int     n;              // 文件行数
        int     l;
        int     j;              // 计数器
        int     k;              // dbase / 函数数目
        string  t;              // 当前时间

        int     comment_on;     // 正在书写注释
        int     dbase_on;       // 正在书写 dbase 数据
        int     function_on;    // 正在书写函数数据

        object  tob;            // 模板物件
        object  ob;

        int     full_dbase;     // 是否完整 dbase 格式
        int     full_function;  // 是否完整函数格式

        string *dbase_format;   // dbase 格式
        string *function_format;// 函数格式
        string  temp_str1;
        string  temp_str2;

        mixed   data;           // 模板数据
        mixed   format;         // dbase、function 格式
        mixed   key;            // 数据(mapping)中的一个 key
        mixed   dbase;
        mapping applied_prop, temp;
        string *apply;

        if( tfile[<2..<1] != FILE_EXTENSION )
                tfile += FILE_EXTENSION;

        if( file_size(tfile) < 1 )
                return 0;

        if( !objectp(tob = find_object(tfile)) &&
                catch(tob = load_object(tfile)) )
                return 0;

        if( !sscanf(tfile, TEMPLATE_DIR "%s.c", template) ) {
                data = tob->query_entire_dbase();

                if( sizeof(dbase_data) && !undefinedp(dbase_data["name"]) ) {
                        name = dbase_data["name"];
                        map_delete(dbase_data, "name");
                } else
                        name = data["name"];

                if( sizeof(dbase_data) && !undefinedp(dbase_data["id"]) )
                        map_delete(dbase_data, "id");

                if( sizeof(dbase_data) && !undefinedp(dbase_data["shadow_ob"]) )
                        map_delete(dbase_data, "shadow_ob");

                while( 1 ) {
                        // 生成待编译的文件名
                        cfile = sprintf("%sunknow/%s-%d.c", TEMPLATE_DATA, arg, time() + random(99999999));
                        // 将空格替换为 "_"
                        cfile = replace_string(cfile, " ", CONNECT_CHAR);
                        if( file_size(cfile) == -1 )
                                break;
                }

                assure_file(cfile);
                content_str = read_file(tfile);
                content_str = replace_string(content_str, "\r", "");
                content = explode(content_str, "\n");

                n = sizeof(content);
                t = ctime(time());
                content_str = "";

                for( i = 0; i < n; i++ ) {
                        // 找到处理外部传入 dbase_data 数据的位置
                        temp_str1 = content[i];
                        temp_str1 = replace_string(temp_str1, " ", "");

                        if( !j && strsrch(temp_str1, "setup(") != -1 )
                                j = i;

                        if( strsrch(temp_str1, "set_name") != -1 )
                                content[i] = sprintf("\tset_name(\"%s\", ({ \"%s\" }));",
                                                     name, arg);

                        // 处理外部传入 dbase_data 和文件本身有重叠部分
                        if( sizeof(dbase_data) ) {
                                format = keys(dbase_data);
                                foreach (key in format)
                                if( strsrch(temp_str1, sprintf("set(\"%s\"", key)) != -1
                                ||  strsrch(temp_str1, sprintf("set(\"%s/", key)) != -1 ) {
                                        dbase_on = 1;

                                        if( !model )
                                                dbase = dbase_data[key];
                                        else {
                                                if( mapp(data[key]) && mapp(dbase_data[key]) )
                                                {
                                                        applied_prop = copy(data[key]);
                                                        temp = copy(dbase_data[key]);
                                                        apply = keys(temp);
                                                        for( int p = 0; p < sizeof(apply); p++ )
                                                        {
                                                                if( undefinedp(applied_prop[apply[p]]) )
                                                                        applied_prop[apply[p]] = temp[apply[p]];
                                                                else
                                                                {
                                                                        if( (mapp(applied_prop[apply[p]]) && mapp(temp[apply[p]])) ||
                                                                             (arrayp(applied_prop[apply[p]]) && arrayp(temp[apply[p]])) )
                                                                                applied_prop[apply[p]] = applied_prop[apply[p]] + temp[apply[p]];
                                                                        else
                                                                                applied_prop[apply[p]] = temp[apply[p]];
                                                                }
                                                        }
                                                        dbase[key] = copy(applied_prop);
                                                }
                                                if( arrayp(data[key]) && arrayp(dbase_data[key]) )
                                                        dbase[key] = data[key] + dbase_data[key];
                                                else
                                                        dbase[key] = dbase_data[key];
                                                /////////////////////
                                        }
                                        // 这里有个排版的问题
                                        content[i] = sprintf("\tset(\"%s\", %O);",
                                                             key, dbase);

                                        l = i;
                                        while( l < (n -1) ) {
                                                l++;
                                                temp_str2 = content[l];
                                                temp_str2 = replace_string(temp_str2, " ", "");
                                                if( dbase_on && (strsrch(temp_str2, "set_") != -1 ||
                                                    strsrch(temp_str2, "set(") != -1 ||
                                                    strsrch(temp_str2, "init") != -1 ||
                                                    strsrch(temp_str2, "if") != -1 ||
                                                    strsrch(temp_str2, "else") != -1 ||
                                                    strsrch(temp_str2, "setup(") != -1 ||
                                                    (strsrch(temp_str2, "}") != -1 && strsrch(temp_str2, "})") == -1)) )
                                                        dbase_on = 0;

                                                if( dbase_on ) {
                                                        content[l] = "";
                                                        continue;
                                                }

                                                if( strsrch(temp_str2,sprintf("set(\"%s\"", key)) != -1
                                                ||  strsrch(temp_str2, sprintf("set(\"%s/", key)) != -1 ) {
                                                        dbase_on = 1;
                                                        content[l] = "";
                                                }
                                        }

                                        map_delete(dbase_data, key);
                                }
                        }

                        if( sizeof(function_data) ) {
                                format = keys(function_data);
                                for (k = 0; k < sizeof(format); k++ ) {
                                        if( strsrch(temp_str1, sprintf("%s", format[k])) != -1 ) {
                                                content[i] = sprintf("\t%s(%O);",
                                                                     format[k],
                                                                     function_data[format[k]]);
                                                break;
                                        }
                                }
                        }
                }

                content_line = sprintf("// %s.c\n", replace_string(arg, " ", CONNECT_CHAR));
                content_line += sprintf("// Create by TEMPLATE_D. %s.", t);

                // 写入一行
                content_str += content_line + "\n";

                for( i = 0; i < j; i++ )
                        content_str += content[i] + "\n";

                // 处理外部传入 dbase_data 数据
                content_str += prop_segment(dbase_data, "");
                /*
                if( sizeof(dbase_data) ) {
                        format = keys(dbase_data);
                        foreach( key in format )
                                content_str += sprintf("\tset\(\"%s\", %O\);\n",
                                                       key, dbase_data[key]);
                }
                */

                for( i = j; i < n; i++ )
                        content_str += content[i] + "\n";

                // 可receive_summon接口
                content_str += @SUMMON
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// 隐藏物品
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}

SUMMON;
                // 生成文件
                write_file(cfile, content_str, 1);

                // 返回文件
                return cfile;
        }

        // 模板数据是否符合格式？
        if( !arrayp(data = tob->query_template_data(arg)) || !sizeof(data))
                return 0;

        // 是否有专门的基准文件？
        if( sizeof(data) > EXTRA_BASE_DATA)
                bfile = data[EXTRA_BASE_DATA];
        // 否则使用预设的基准文件
        else
                bfile = tob->query_base_file();

        if( !stringp(bfile) || file_size(bfile) < 1)
                return 0;

        if( !objectp(ob = get_object(bfile)))
                return 0;

        if( sizeof(dbase_data) && !undefinedp(dbase_data["name"]))
        {
                name = dbase_data["name"];
                map_delete(dbase_data, "name");
        } else
                name=query("name", ob);

        while(1)
        {
                // 生成待编译的文件名
                cfile = sprintf("%s%s/%s-%d.c", TEMPLATE_DATA, template, arg, time() + random(99999999));
                // 将空格替换为 "_"
                cfile = replace_string(cfile, " ", CONNECT_CHAR);
                if( file_size(cfile) == -1)
                        break;
        }

        // 准备编译所需数据

        // 是否预备了 dbase (模板数据的第一项)的格式？
        if( !arrayp(dbase_format = tob->query_dbase_format()) ||
            !sizeof(dbase_format))
                full_dbase = 1;
        else
                full_dbase = 0;

        // 是否预备了函数(模板数据的第二项)的格式？
        if( !arrayp(function_format = tob->query_function_format()) ||
            !sizeof(function_format))
                full_function = 1;
        else
                full_function = 0;

        // 开始编译

        assure_file(cfile);

        content_str = read_file(bfile);
        content_str = replace_string(content_str, "\r", "");
        content = explode(content_str, "\n");

        n = sizeof(content);
        t = ctime(time());
        content_str = "";

        i = strsrch(template, "/") + 1;
        type = template[i..<1];

        for (i = 0; i < n; i++)
        {
                // 书写注释
                if( strsrch(content[i], COMMENT_ENTRY) != -1 && !comment_on)
                {
                        comment_on = 1;
                        content_line = sprintf("// %s.c\n", replace_string(arg, " ", CONNECT_CHAR));
                        content_line += sprintf("// Create by TEMPLATE_D. %s.", t);

                        // 写入一行
                        content_str += content_line + "\n";
                        continue;
                }

                if( strsrch(content[i], NAME_ENTRY) != -1)
                {
                        content_line = sprintf("\tset_name(\"%s\", ({ \"%s\", \"%s\" }));",
                                               name, arg, type);
                        content_str += content_line + "\n";
                        continue;
                }

                // 书写 dbase 数据
                if( strsrch(content[i], DBASE_ENTRY) != -1)
                {
                        dbase_on = 1;

                        // 使用格式对应模式
                        if( !full_dbase)
                        {
                                if( !arrayp(dbase_format))
                                        continue;

                                k = sizeof(dbase_format);

                                if( k == 1 && !arrayp(data[DBASE_DATA]))
                                {
                                        dbase = data[DBASE_DATA];
                                        if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[0]]))
                                        {
                                                if( !model)
                                                        dbase = dbase_data[dbase_format[0]];
                                                else
                                                {
                                                        if( mapp(dbase) && mapp(dbase_data[dbase_format[0]]))
                                                                dbase = dbase + dbase_data[dbase_format[0]];
                                                        else
                                                                dbase = dbase_data[dbase_format[0]];
                                                }
                                                map_delete(dbase_data, dbase_format[0]);
                                        }
                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               dbase_format[0], dbase);
                                        content_str += content_line + "\n";
                                } else
                                {
                                        for (j = 0; j < k; j++)
                                        {
                                                dbase = data[DBASE_DATA][j];
                                                if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[j]]))
                                                {
                                                        if( !model)
                                                                dbase = dbase_data[dbase_format[j]];
                                                        else
                                                        {
                                                                if( (mapp(dbase) && mapp(dbase_data[dbase_format[j]])) ||
                                                                    (arrayp(dbase) && arrayp(dbase_data[dbase_format[j]])))
                                                                        dbase = dbase + dbase_data[dbase_format[j]];
                                                                else
                                                                        dbase = dbase_data[dbase_format[j]];
                                                        }
                                                        map_delete(dbase_data, dbase_format[j]);
                                                }
                                                if( stringp(dbase))
                                                        dbase = replace_string(dbase, "\n", "\\n");

                                                content_line = sprintf("\t\tset(\"%s\", %O);",
                                                                       dbase_format[j], dbase);
                                                content_str += content_line + "\n";
                                        }
                                }
                        } else
                        // 使用全格式模式
                        {
                                if( !mapp(data[DBASE_DATA]) || !sizeof(data[DBASE_DATA]))
                                        continue;

                                dbase_format = keys(data[DBASE_DATA]);
                                k = sizeof(dbase_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[DBASE_DATA][dbase_format[j]];
                                        if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[j]]))
                                        {
                                                if( !model)
                                                        dbase = dbase_data[dbase_format[j]];
                                                else
                                                {
                                                        if( (mapp(dbase) && mapp(dbase_data[dbase_format[j]])) ||
                                                            (arrayp(dbase) && arrayp(dbase_data[dbase_format[j]])))
                                                                dbase = dbase + dbase_data[dbase_format[j]];
                                                        else
                                                                dbase = dbase_data[dbase_format[j]];
                                                }
                                                map_delete(dbase_data, dbase_format[j]);
                                        }

                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               dbase_format[j], dbase);
                                        content_str += content_line + "\n";
                                }
                        }

                        if( sizeof(dbase_data))
                        {
                                format = keys(dbase_data);
                                foreach (key in format)
                                {
                                        dbase = dbase_data[key];
                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               key, dbase);
                                        content_str += content_line + "\n";
                                }
                        }
                        continue;
                }

                // 书写函数数据
                if( strsrch(content[i], FUNCTION_ENTRY) != -1)
                {
                        function_on = 1;

                        // 使用格式对应模式
                        if( !full_function)
                        {
                                k = sizeof(function_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[FUNCTION_DATA][j];
                                        if( sizeof(function_data) && !undefinedp(function_data[function_format[j]]))
                                        {
                                                dbase = function_data[function_format[j]];
                                                map_delete(function_data, function_format[j]);
                                        }
                                        content_line = sprintf("\t%s(%O);",
                                                               function_format[j],
                                                               dbase);
                                        content_str += content_line + "\n";
                                }
                        } else
                        // 使用全格式模式
                        {
                                if( !mapp(data[FUNCTION_DATA]) || !sizeof(data[FUNCTION_DATA]))
                                        continue;

                                function_format = keys(data[FUNCTION_DATA]);
                                k = sizeof(function_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[FUNCTION_DATA][function_format[j]];
                                        if( sizeof(function_data) && !undefinedp(function_data[function_format[j]]))
                                        {
                                                dbase = function_data[function_format[j]];
                                                map_delete(function_data, function_format[j]);
                                        }
                                        content_line = sprintf("\t%s(%O);",
                                                               function_format[j],
                                                               dbase);
                                        content_str += content_line + "\n";
                                }
                        }

                        if( sizeof(function_data))
                        {
                                format = keys(function_data);
                                foreach (key in format)
                                {
                                        dbase = function_data[key];
                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               key, dbase);
                                        content_str += content_line + "\n";
                                }
                        }
                        continue;
                }

                // 检查书写结束标志

                // 书写注释结束
                if( strsrch(content[i], COMMENT_EXIT) != -1)
                {
                        comment_on = 0;
                        continue;
                }

                // 书写名称结束
                if( strsrch(content[i], NAME_EXIT) != -1)
                        continue;

                // 书写 dbase 结束
                if( strsrch(content[i], DBASE_EXIT) != -1)
                {
                        dbase_on = 0;
                        continue;
                }

                // 书写函数结束
                if( strsrch(content[i], FUNCTION_EXIT) != -1)
                {
                        function_on = 0;
                        continue;
                }

                // 若正在书写注释，忽略
                if( comment_on) continue;

                // 若正在书写 dbase，忽略
                if( dbase_on) continue;

                // 若正在书写函数，忽略
                if( function_on) continue;

                // 否则直接添加这一行
                content_str += content[i] + "\n";
        }

        // 生成文件
        write_file(cfile, content_str, 1);

        // 返回文件
        return cfile;
}
