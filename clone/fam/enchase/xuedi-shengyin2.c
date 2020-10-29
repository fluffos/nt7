#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIW "雪地圣音" NOR, ({"xuedi shengyin", "xuedi", "shengyin"}));
        set_weight(2000);
        set("long", HIW "人间罕有的宝石，据说在极寒雪地形成。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "雪地圣音");
                set("enchase/point", 1);
                set("enchase/type", "cloth");
                set("can_be_qiling", 1); 
        }
        setup();
}

int query_autoload()
{
        return 1;
}
