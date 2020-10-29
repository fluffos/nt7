// dulong-bian.c 毒龙鞭 

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit WHIP;

void create()
{
        set_name("毒龙鞭",({ "dulong bian", "bian", "whip", "dulong" }) );
        set_weight(700);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 7000000);
                set("rigidity", 100000);
                set("replica_ob","/clone/weapon/whip");
                set("poison_applied", 300);
                set("material", "leather");
                set("long", 
                "这是一条烂银也似的银色软鞭，长达四丈有余，鞭头装着十多只明晃晃的尖利倒钩。\n");
                set("wield_msg", "$N「唰」的一声从腰后抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n别回腰后。\n");
        }
        init_whip(50);
        setup();
}