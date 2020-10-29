#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"王叔和脉经"NOR, ({ "jingmai book", "book", "shu" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set_weight(10);
                set("no_drop", 1);
                set("material", "paper");
                set("no_get", 1);
                set("skill", ([
                        "name": "jingmai-xue",
                        "jing_cost":    20,
                        "difficulty":   25,
                        "min_skill":    160,
                        "max_skill":    170
                ]) );
        }
        setup();
}