// shoutao.c  手套

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "铁手套" NOR, ({ "tie shoutao", "tie", "shoutao" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIW "这是一双钢铁铸造的手套，上面似乎有硬物刻过的痕迹。\n" NOR);
                set("value", 350000);
                set("material", "tie");
                set("armor_prop/armor", 200);
                set("armor_prop/unarmed_damage", 300);
        }
        setup();
}

int query_autoload()
{
        return 1;
}