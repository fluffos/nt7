// sword.c
// The template of auto-created sword.
// An example of object template.

// 包含模板系统宏定义文件
#include <template.h>

// 继承模板物件
inherit TEMPLATE_OB;

// 将所需数据保存在变量中

// dbase 格式
mixed *dbase_format = ({ "long", "value" });

// 函数格式
mixed *function_format = ({ "set_weight", "init_damage" });

// 模板数据
mapping template_data = ([
        // 英文名(索引)  : ({ 描述(long), ({ 重量(set_weight) - 伤害(init_damage) }), 额外基准文件 })
        "scimitar"       : ({ ({ "这是一柄身作弧形的弯刀。\n", 100 }),        ({ 7000,  20, }), }),
        "sabre"          : ({ ({"这是一柄狭长略弯的马刀。\n", 200 }),        ({ 9000,  25, }), }),
        "fachion"        : ({ ({"这是一把既宽且长的大刀。\n", 300 }),        ({ 12000, 30, }), }),
        "claymore"       : ({ ({ "这是一把两边都带刃的锋锐长刀。\n", 400 }),  ({ 12000, 40, }), }),
]);

// 初始化模板
void create()
{
        setup();
}

// 在这里配置是否使用全格式模式或格式对应模式
void setup()
{
        // 即基准文件为 "/inherit/template/weapon/sword.c"。
        set_base_file("weapon/blade");

        // 设置 dbase 格式
        set_dbase_format(dbase_format);

        // 设置函数格式
        set_function_format(function_format);

        // 设置模板数据
        set_template_data(template_data);

        ::setup();
}
