#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIR "九幽·神魔" NOR, ({"shen mo", "shen", "mo"}));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY "霎那间天地变色，万物隐匿，乃魔界至高无上的宝物，支配着魔界万物。\n" NOR);
                set("unit", "块");
                set("value", 13000);
                set("can_be_tessera", 1);

                set("magic/type", "magic");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5)); 
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_magic" : 3,
                "add_skill" : 30,     
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_magic" : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload()
{
        return 1;
}

