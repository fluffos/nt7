#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"进阶经脉学"NOR, ({ "jingmai book", "book", "shu" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("value", 8000);
                set_weight(10);
                set("material", "paper");
                set("skill", ([
                        "name": "jingmai-xue",
                        "jing_cost":    15,
                        "difficulty":   25,
                        "min_skill":    40,
                        "max_skill":    80
                ]) );
        }
        setup();
}