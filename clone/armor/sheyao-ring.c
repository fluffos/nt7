#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIG "蛇妖指环" NOR, ({ "sheyao ring", "sheyao", "ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIG "蛇妖指环是传说中蛇精佩带的指环，拥有神秘的力量！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/dex", 6);
                set("armor_prop/str", 4);
                set("armor_prop/int", 4);
                set("armor_prop/con", 6);
                set("armor_prop/damage", 200);

                set("limit", ([ 
                         "exp" : 1000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}