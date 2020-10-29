
inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(YEL "魔幻兽兑换券" NOR, ({"duihuan juan", "duihuan", "juan"}));
        set_weight(40);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "这是一张魔幻兽兑换券，可以拿它去狂风那里选一个" HIM "魔幻兽。\n" NOR);
                set("unit", "张");
                set("material_attrib", "paper");
                set("value", 10000000);
                set("no_sell", 1);
        }
}

int query_autoload() { return 1; } 
