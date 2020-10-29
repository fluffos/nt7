// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <weapon.h>
#include <ansi.h>

inherit BLADE;


void create()
{
        set_name(HIB "斩魂刀" NOR, ({ "zhanhun dao", "blade", "zhanhun", "dao" }));
        set_weight(1500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "此刀乃一品堂将军赫连铁树征战武林所用，刀下亡魂无数。\n" NOR );
                set("unit", "把");
                set("value", 500000);
                set("material", "steel");
                set("wield_msg", "$N抽出一把$n倒提在手，四周空气顿时快凝结了。\n");
                set("unwield_msg", "$N将手中的$n插回腰间的刀鞘里。\n");
        }
        
        init_blade(200);
        
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        if (!playerp(me)) return to_int(damage_bonus * 1.5);
        return damage_bonus;
}



