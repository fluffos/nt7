#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(MAG "炼狱" HIR "血环" NOR, ({ "lianyu xuehuan", "lianyu", "xuehuan" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("long", MAG "紫黑色的指环，血色的暗纹，散发着阵阵阴寒之气，令人心神颤抖。 \n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 4000);
                set("armor_prop/int", 20);
                set("armor_prop/add_tihui_gift", 5); // 增加体会奖励5% giftd.c中处理
                set("armor_prop/add_tihui_xiaolv", 5); // 增加体会汲取效率5% jiqu.c中处理
                set("special/desc", HIR "杀怪、杀BOSS所得体会奖励额外增加5%，" 
                                        "提升实战体会汲取效率5%"NOR);
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));

        }
        setup();
}

int query_autoload()
{
        return 1;
}
