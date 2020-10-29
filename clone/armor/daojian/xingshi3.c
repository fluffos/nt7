#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "天降·醒世环" NOR, ({ "xingshi huan3" }));
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("long", HIY "传说中狐仙所佩带的指环。\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/unarmed", 150);
                set("armor_prop/magic_find", 10);
                set("special/desc", "有效拳法等级提高150级。\n"+
                                    "有效拳脚等级提高150级。\n"+
                                    "有效掌法等级提高150级。\n"+
                                    "有效指法等级提高150级。\n"
                );
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