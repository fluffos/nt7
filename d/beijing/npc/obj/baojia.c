#include <ansi.h>
#include <armor.h>
inherit ARMOR;
void create()
{
        set_name( CYN"真丝"NOR+HIY"宝甲"NOR,  ({ "bao jia", "jia", "armor" }));
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", "一见黑黝黝的甲，毫不起眼。\n");
                /*
                set("no_drop", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_put", "这样东西不能放在那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                */
                set("no_sell", "这样东西不能卖。\n");
                set("value", 100000);
                set("material", "cloth");
                set("armor_prop/armor", 200);
        }
        setup();
}
