// blade.c
// Last Modified by winder on May. 25 2001
#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
         set_name(HIG"小楼一夜听春雨"NOR, ({ "springrain blade", "blade" }) );
         set_weight(4000);
         /*if( clonep() )
                 set_default_object(__FILE__);
         else*/ {
                 set("unit", "柄");
                 set("value", 500);
                 set("material", "iron");
                 set("long",
                        "＂小楼一夜听春雨＂又名＂小楼听雨＂。是西方神教两大掌门信物之一。\n"
                        "此刀极邪，又削铁如泥。\n");
                 set("wield_msg", "$N抽出一把明晃晃的$n握在手中。\n");
                 set("unequip_msg", "$N将手中的$n插入腰间的刀鞘。\n");
         }
         init_blade(300);
         setup();
}