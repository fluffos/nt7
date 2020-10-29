#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIR "圣灵腰带" NOR, ({ "shengling belt3", "belt", "shengling3" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "一根闪耀着奇异光芒的腰带。\n" NOR) ;
                set("unit", "根");
                set("value", 400000);
                set("armor_prop/armor", 100);
                set("armor_prop/dodge", 12);
                set("armor_prop/parry", 14);
        }
        setup();
}

int query_autoload()
{
        return 1;
}