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
        "liangyin whip" : ({ ({ "这是一柄银光闪闪的亮银鞭，上面发出阵阵寒气袭人夺目。\n", 100 }), ({ 5000,  20, }), }),
        "zhujie whip"   : ({ ({ "这是一柄竹节钢鞭。\n", 150 }), ({ 5000,  40, }), }),
        "baowei whip"   : ({ ({ "这是一柄豹尾鞭。\n", 200 }), ({ 5000, 60, }), }),
        "dajiang whip"  : ({ ({ "这是一柄打将鞭。\n", 250 }), ({ 5000, 80, }), }),
        "tuogu whip"    : ({ ({ "这是一柄驼骨阴风鞭。\n", 300 }), ({ 5000, 100, }), }),
        "jinlong whip"  : ({ ({ "这是一柄金龙鞭。\n", 350 }), ({ 5000, 120, }), }),
        "huwei whip"    : ({ ({ "这是一柄虎尾钢鞭。\n", 400 }), ({ 5000, 140, }), }),
        "bingtie whip"  : ({ ({ "这是一柄镔铁鞭。\n", 450 }), ({ 5000, 160, }), }),
        "longtou whip"  : ({ ({ "这是一柄龙头凤尾鞭。\n", 500 }), ({ 5000, 180, }), }),                
        "huyan whip"    : ({ ({ "这是一柄虎眼钢鞭。\n", 550 }), ({ 5000, 200, }), }),  
        "jinsi whip"    : ({ ({ "这是一柄金丝软鞭。\n", 600 }), ({ 5000, 220, }), }),  
        "hulu whip"     : ({ ({ "这是一柄葫芦鞭。\n", 650 }), ({ 5000, 240, }), }),  
        "guigu whip"    : ({ ({ "这是一柄龟骨鞭。\n", 700 }), ({ 5000, 260, }), }),  
        "yugu whip"     : ({ ({ "这是一柄鱼尾鞭。\n", 750 }), ({ 5000, 280, }), }),  
        "shegu whip"    : ({ ({ "这是一柄蛇骨鞭。\n", 800 }), ({ 5000, 300, }), }),  
        "yinsi whip"    : ({ ({ "这是一柄银丝软鞭。\n", 850 }), ({ 5000, 320, }), }),  
        "zheyun whip"   : ({ ({ "这是一柄遮云扫龙鞭。\n", 900 }), ({ 5000, 350, }), }),         
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
        set_base_file("weapon/whip");

        // 设置 dbase 格式
        set_dbase_format(dbase_format);

        // 设置函数格式
        set_function_format(function_format);

        // 设置模板数据
        set_template_data(template_data);

        ::setup();
}
