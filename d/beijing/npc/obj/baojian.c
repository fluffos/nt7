#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( WHT"玄铁"NOR+HIW"匕首"NOR,  ({ "bi shou", "sword", "jian" }));
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "一柄玄铁铸造的匕首，锋利无比。\n");
                set("no_drop", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_put", "这样东西不能放在那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("no_sell", "凡人哪里知道这神剑的厉害。\n");
                set("value", 100000);
                set("material", "gold");
                set("wield_msg", HIR"$N抽出一柄寒气逼人的"NOR+WHT"玄铁"NOR+HIW"匕首"NOR+HIR"拿在手中，只感到一阵"NOR+HIW"寒气"NOR+HIR"扑面而来。\n"NOR);
                set("unwield_msg", HIR"$N将手中的"NOR+WHT"玄铁"NOR+HIW"匕首"NOR+HIR"插回靴中。\n"NOR);
        }
        init_sword(200);
        setup();
}