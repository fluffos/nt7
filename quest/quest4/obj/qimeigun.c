// qimeigun.c 齐眉棍
// modified by xingyun 22/5/2001
#include <weapon.h>
inherit CLUB; 

void create()
{
        set_name("齐眉棍" , ({ "qimeigun" }));
        set_weight(20000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根齐眉棍，少林弟子多携带此行走江湖。\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
        init_club(40);
        setup();
}
