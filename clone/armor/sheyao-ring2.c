#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "蛇妖指环" NOR, ({ "sheyao ring", "sheyao", "ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIY "蛇妖指环是传说中蛇精佩带的指环，拥有神秘的力量！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/dex", 8);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);
                set("armor_prop/con", 8);
                set("armor_prop/damage", 300);

                set("limit", ([ 
                         "exp" : 5000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}