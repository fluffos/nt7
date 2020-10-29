// sword.c
// The template of auto-created sword.
// An example of object template.

// 包含模板系统宏定义文件
#include <template.h>

// 继承模板物件
inherit TEMPLATE_OB;

// 将所需数据保存在变量中

// dbase 格式
mixed *dbase_format = ({ "long" });

// 函数格式
mixed *function_format = ({ "set_weight", "init_damage" });

// 模板数据
mapping template_data = ([
        // 英文名(索引)  : ({ 描述(long), ({ 重量(set_weight) - 伤害(init_damage) }), 额外基准文件 })
        "short sword"    : ({ "这是一柄银光闪闪的窄鞘短剑。\n",     ({ 5000,  10, }), }),
        "scimitar"       : ({ "这是一柄身作弧形的弯刀。\n",         ({ 7000,  20, }), }),
        "sabre"          : ({ "这是一柄狭长略弯的马刀。\n",         ({ 9000,  25, }), }),
        "war sword"      : ({ "这是一把宽大锐利，战场使用的剑。\n", ({ 9000,  30, }), }),
        "fachion"        : ({ "这是一把既宽且长的大刀。\n",         ({ 12000, 30, }), }),
        "long sword"     : ({ "这是一把狭长锋利的长剑。\n",         ({ 7000,  10, }), }),
        "crystal sword"  : ({ "这是一把晶光闪闪的弯形剑。\n",       ({ 12000, 35, }), }),
        "broad sword"    : ({ "这是一把剑身特别宽阔的大剑。\n",     ({ 13000, 40, }), }),
        "two-hand sword" : ({ "这是一柄双手皆可拿的长剑。\n",       ({ 12000, 35, }), }),
        "claymore"       : ({ "这是一把两边都带刃的锋锐长刀。\n",   ({ 12000, 40, }), }),
        "giant sword"    : ({ "这是一把身形巨大的重剑。\n",         ({ 20000, 40, }), }),
        "bastard sword"  : ({ "这是一柄带着各色金属光泽的长剑。\n", ({ 15000, 40, }), }),
        "flamberge"      : ({ "这是一把红光灼灼的血色长剑。\n",     ({ 15000, 45, }), }),
        "great sword"    : ({ "这是一把非常巨大的重剑。\n",         ({ 30000, 50, }), }),
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
        set_base_file("weapon/sword");

        // 设置 dbase 格式
        set_dbase_format(dbase_format);

        // 设置函数格式
        set_function_format(function_format);

        // 设置模板数据
        set_template_data(template_data);

        ::setup();
}
