// jewel.c
#include <ansi.h>
#include <template.h>

inherit TEMPLATE_OB;

mixed *dbase_format = ({ "long", "value", "enchase", });

// 模板数据
mapping template_data = ([
        "skull1"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头, 有些裂纹。\n" NOR,              80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull1.c"
                          }),
        "skull2"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，完整无缺无丝毫裂纹。\n" NOR,    10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull2.c"
                          }),
        "skull3"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，给人以不同寻常的感觉。\n" NOR,  12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull3.c"
                          }),
        "skull4"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull4.c"
                          }),
        "skull5"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull5.c"
                          }),
        "skull6"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull6.c"
                          }),
        "skull7"    : ({ ({ BLU "一个冒着幽蓝色光芒的骷髅头，让人感到一阵阵的心悸。\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull7.c"
                          }),
]);

// 初始化模板
void create()
{
        setup();
}

// 在这里配置是否使用全格式模式或格式对应模式
void setup()
{
        // 即基准文件为 "/inherit/template/gem/skull.c"。
        set_base_file("gem/skull");

        // 设置 dbase 格式
        set_dbase_format(dbase_format);

        // 设置模板数据
        set_template_data(template_data);

        ::setup();
}

