#include <ansi.h>
#include <weapon.h>
inherit BLADE;
void create()
{
        set_name( YEL "钝刀" NOR, ({ "badblade" }) );
        set_weight(48000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
                        
"一把钝刃的破刀。看来毫不起眼，但听说这把刀曾附有过无上的杀气。\n"
);
                set("value", 500);
		set("for_bandit",1);
                set("material", "steel");
                set("wield_msg", "$N不声不响地抽出一把$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n放下。\n");
        }

        init_blade(150);
        setup();

}