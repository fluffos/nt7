#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "圣龙之泉" NOR, ({ "shenglong ring", "shenglong", "ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIY "圣龙之泉乃古老神兽圣龙之化身，象征着「能量」！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 20);
                set("armor_prop/damage", 200);
        }
        setup();
}

int query_autoload()
{
        return 1;
}