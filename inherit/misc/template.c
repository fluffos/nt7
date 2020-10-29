// template.c

#include <template.h>

nosave mixed  *dbase_format;    // dbase 格式
nosave mixed  *function_format; // 函数格式

nosave mapping template_data;   // 模板数据
nosave string  base_file;       // 基准文件

// 这是一个模板
int is_template() { return 1; }

// 查询 dbase 格式
mixed *query_dbase_format()
{
        return (sizeof(dbase_format) ? dbase_format : 0);
}

// 查询函数格式
mixed *query_function_format()
{
        return (sizeof(function_format) ? function_format : 0);
}

// 查询基准文件
string query_base_file() { return sprintf("%s%s.c", BASIC_OB_DIR, base_file); }

// 查询全部模板数据
mapping query_entire_data() { return template_data; }

// 查询指定模板数据
mixed *query_template_data(string template)
{
        if( undefinedp(template_data[template]) )
                return 0;

        return template_data[template];
}

void set_dbase_format(string *format)
{
        if( !arrayp(format) || !sizeof(format) )
                return;

        dbase_format = format;
}

void set_function_format(string *format)
{
        if( !arrayp(format) || !sizeof(format) )
                return;

        function_format = format;
}

// 设置基准文件
void set_base_file(string file)
{
        if( !stringp(file) || file == "" )
                return;

        base_file = file;
}

// 设置模板数据
void set_template_data(mapping data)
{
        if( !mapp(data) || !sizeof(data) )
                return;

        template_data = data;
}

// 模板的初始化
void setup()
{
        if( !this_object()->is_template() )
                return;
}
