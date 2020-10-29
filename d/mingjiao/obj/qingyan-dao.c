#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name(HIC"青焰刀"NOR, ({ "qingyan dao", "dao", "blade" }) );
          set_weight(20000);
        /*if( clonep() )
              set_default_object(__FILE__);
        else*/ {
           set("value", 1000);
           set("rigidity", 3);
        set("long",HIC"这柄刀重约四十余斤，但见青光闪烁，背厚刃薄，刃锋上刻有古朴花纹，显是一件历时已久的珍品。\n"NOR);
           set("sharpness", 3);
           set("unique", 1);
           set("treasure",1);
           set("weapon_prop/parry", 2);
           set("wield_neili", 500);
           set("wield_maxneili", 900);
           set("wield_str", 22);
           set("unit", "把");
        set("wield_msg", HIB"$N由背后取下宝刀，双手一分，将青焰刀抽出刀鞘，四周顿时布满凌厉的杀气。\n"NOR);
        set("unwield_msg",HIB" 只听见仓啷一声响，$N将沉重的青焰刀插进刀鞘，背在背上。\n"NOR);
        }
        init_blade(80);
        setup();
}