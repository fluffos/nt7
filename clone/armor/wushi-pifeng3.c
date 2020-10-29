#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIR "圣武士披风" NOR, ({ "wushi pifeng3", "wushi", "pifeng3" }) );
        set_weight(200);
        set("long", HIR "传说中圣洁的武士才能穿戴此披风，乃神圣的象征。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIR "圣武士所穿戴的披风，蕴藏着神奇的力量！\n" NOR);
                set("material", "steel");
                set("value", 3000000);
                set("armor_prop/armor", 400);
                set("armor_prop/con", 4); // 后天根骨+1
                set("armor_prop/str", 4); // 后天臂力+1
        }
        setup();
}

int query_autoload()
{
        return 1;
}