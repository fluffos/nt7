#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIY "流星赶月" NOR, ({"liuxing ganyue", "liuxing", "ganyue"}));
        set_weight(2000);
        set("long", HIY "人间罕有的宝石，据说乃天上流星坠落后形成。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "流星赶月");
                set("enchase/point", 1);
                set("enchase/type", "boots");
                set("can_be_qiling", 1); 
        }
        setup();
}

int query_autoload()
{
        return 1;
}
