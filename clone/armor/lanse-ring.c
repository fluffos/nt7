#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIC "蓝色妖姬" NOR, ({ "lanyao ring", "lanyao", "ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIC "蓝色妖姬乃神秘的化身，象征着「智慧」！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/int", 10);
                set("armor_prop/damage", 200);        
        }
        setup();
}

int query_autoload()
{
        return 1;
}