#include <ansi.h>
#include <weapon.h>
inherit SWORD;
void create()
{
        set_name("长吟剑", ({ "long sword" ,"sword"}) );
        set_weight(3000);
        set("value", 10000); 
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long",           
"这是一把长吟剑。\n");
                set("value", 10000);
		set("for_bandit",1);
                set("material", "steel");
                set("wield_msg", "$N从剑鞘中抽出一柄剑光闪闪的$n。\n");
                set("unwield_msg", "$N将$n插回剑鞘之中。\n");
             }

        init_sword(50);
        setup();

}