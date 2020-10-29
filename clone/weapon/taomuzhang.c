
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("桃木杖", ({ "taomu zhang" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根用桃树根做的杖。\n");
                set("value", 2000);
                set("rigidity", 100);
                set("material", "wood");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
          init_staff(100);
        setup();
}