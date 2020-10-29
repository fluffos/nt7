#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIR "麒麟圣火" NOR, ({"qilin shenghuo", "qilin", "shenghuo" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("long", HIR "据说麒麟火麒麟神兽骸骨所化，拿在手中有种炽热的感觉。\n" NOR);
                set("enchase/name", "麒麟圣火");
                set("enchase/point", 5);
                set("enchase/type", "wrists");
                set("can_be_qiling", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
