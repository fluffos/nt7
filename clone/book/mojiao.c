// mojiao.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "魔教医术" NOR, ({ "mojiao medical", "medical" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", "这是一本泛黄的书籍，上面用古篆书"
                            "写着“魔教医术”几个字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "mojiao-medical",
						"family_name" : "魔教",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 160,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "tianmo" : 280,           // 天魔圣血膏
                ]));
        }
        setup();
}