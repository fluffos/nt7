#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "白虎皮革" NOR, ({ "baihu pige", "pige" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一张巨大的白虎皮革，乃世间珍品。\n" NOR);
                set("unit", "张");
                set("value", 1000000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}