// wudang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "玉女心经" NOR, ({ "yunv xinjing", "xinjing" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", "这是一本泛黄的书籍，上面用小篆书"
                            "写着“玉女心经”几个字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "yunv-xinjing",
					    "family_name" : "古墓派",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 60,
                ]));

                set("can_make", ([
                        "jinmisan" : 80,        // 金蜜散
                ]));
        }
        setup();
}

