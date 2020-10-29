#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIR "火麒麟·湮灭" NOR, ({ "yanmie ring", "yanmie", "ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("long", HIR "火麒麟乃上古神兽，拥有无穷神力，直到有一天，被更强大的力量消灭后，\n"
                                "临死之前的怒怨，在一瞬间凝聚成的湮灭之戒，蕴涵了巨大的威力。\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 4000);
                set("armor_prop/magic_find", 20);

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