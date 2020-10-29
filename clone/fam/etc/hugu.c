#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "白虎骨" NOR, ({ "tiger bone", "bone" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一副白虎骨，乃制衣极品，世间罕有。\n" NOR);
                set("unit", "副");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}