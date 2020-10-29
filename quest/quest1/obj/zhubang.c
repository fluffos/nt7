#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name(HIG"玉竹杖"NOR, ({ "yuzhu zhang" }));
        set_weight(6000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根发黄的竹棒，入手沉甸甸的，似乎相当结实。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }

        init_staff(100, TWO_HANDED);
        setup();
}