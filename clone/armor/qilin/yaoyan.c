#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIR "火麒麟·妖焰" NOR, ({ "yaoyan erhuan", "yaoyan", "erhuan" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "副");
                set("long", HIR "你定睛一看，却无法辩识清楚，妖焰的火光闪耀刺眼，令人敬畏。\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 40);
                set("armor_prop/magic_find", 10);
                set("limit", ([
                        "exp" : 10000000,
                        "sex" : 1, // 1 为女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}