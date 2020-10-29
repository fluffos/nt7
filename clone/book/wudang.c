// wudang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "炼丹秘本" NOR, ({ "liandan miben", "miben" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", "这是一本泛黄的书籍，上面用小篆书"
                            "写着“炼丹秘本”几个字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "liandan-shu",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 155,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "shujing"  : 80,        // 舒筋活络丹
                        "dieda"    : 80,        // 跌打伤愈膏
                        "jiedu"    : 100,       // 牛黄解毒丸
                        "yuzhen"   : 150,       // 玉真散
                        "yuling"   : 150,       // 玉灵散
                        "yuqing"   : 200,       // 玉清散
                        "sanhuang" : 250,       // 三黄宝腊丹
                ]));
        }
        setup();
}
