// jewel.c
#include <ansi.h>
#include <template.h>

inherit TEMPLATE_OB;

mixed *dbase_format = ({ "long", "value", "enchase", });

// 模板数据
mapping template_data = ([
        "red gem1"    : ({ ({ RED "一片宝石碎片。\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem1.c" 
                          }),
        "red gem2"    : ({ ({ RED "一块金光闪闪的精美宝石，华丽异常。\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem2.c" 
                          }),
        "red gem3"    : ({ ({ RED "一块金光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem3.c" 
                          }),
        "red gem4"    : ({ ({ RED "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem4.c" 
                          }),
        "red gem5"    : ({ ({ RED "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem5.c" 
                          }),
        "red gem6"    : ({ ({ RED "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem6.c" 
                          }),
        "red gem7"    : ({ ({ RED "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem7.c" 
                          }),
        "grn gem1"    : ({ ({ GRN "一片宝石碎片。\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem1.c" 
                          }),
        "grn gem2"    : ({ ({ GRN "一块金光闪闪的精美宝石，华丽异常。\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem2.c"  
                          }),
        "grn gem3"    : ({ ({ GRN "一块金光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem3.c" 
                          }),
        "grn gem4"    : ({ ({ GRN "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem4.c" 
                          }),       
        "grn gem5"    : ({ ({ GRN "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem5.c" 
                          }),
        "grn gem6"    : ({ ({ GRN "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem6.c" 
                          }),
        "grn gem7"    : ({ ({ GRN "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  20000,                                 
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem7.c" 
                          }),
        "yel gem1"    : ({ ({ YEL "一片宝石碎片。\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem1.c" 
                          }),
        "yel gem2"    : ({ ({ YEL "一块金光闪闪的精美宝石，华丽异常。\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem2.c"
                          }),
        "yel gem3"    : ({ ({ YEL "一块金光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem3.c"
                          }),
        "yel gem4"    : ({ ({ YEL "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem4.c"
                          }),
        "yel gem5"    : ({ ({ YEL "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem5.c"
                          }),
        "yel gem6"    : ({ ({ YEL "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem6.c"
                          }),
        "yel gem7"    : ({ ({ YEL "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem7.c"
                          }),
        "blu gem1"    : ({ ({ BLU "一片宝石碎片。\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem1.c"
                          }),
        "blu gem2"    : ({ ({ BLU "一块金光闪闪的精美宝石，华丽异常。\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem2.c"
                          }),
        "blu gem3"    : ({ ({ BLU "一块金光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem3.c"
                          }),
        "blu gem4"    : ({ ({ BLU "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem4.c"
                          }),
        "blu gem5"    : ({ ({ BLU "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem5.c"
                          }),
        "blu gem6"    : ({ ({ BLU "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem6.c"
                          }),
        "blu gem7"    : ({ ({ BLU "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem7.c"
                          }),
        "mag gem1"    : ({ ({ MAG "一片宝石碎片。\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem1.c"
                          }),
        "mag gem2"    : ({ ({ MAG "一块金光闪闪的精美宝石，华丽异常。\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem2.c"
                          }),
        "mag gem3"    : ({ ({ MAG "一块金光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem3.c"
                          }),
        "mag gem4"    : ({ ({ MAG "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem4.c"
                          }),
        "mag gem5"    : ({ ({ MAG "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem5.c"
                          }),
        "mag gem6"    : ({ ({ MAG "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem6.c"
                          }),
        "mag gem7"    : ({ ({ MAG "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem7.c"
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
        // 即基准文件为 "/inherit/template/gem/gem.c"。
        set_base_file("gem/gem");

        // 设置 dbase 格式
        set_dbase_format(dbase_format);

        // 设置模板数据
        set_template_data(template_data);

        ::setup();
}
