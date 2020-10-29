// wushi_pifeng.c
// Create by TEMPLATE_D. Fri Jan 25 21:59:34 2019.
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
	set_name("[1;31m圣武士披风[2;37;0m", ({ "wushi pifeng" }));
        set_weight(200);
	set("long", "[1;31m圣武士所穿戴的披风，蕴藏着神奇的力量！
[2;37;0m");
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("unit", "件");

	set("material", "steel");
	set("value", 3000000);
	set("armor_prop", ([ /* sizeof() == 3 */
  "str" : 1,
  "con" : 1,
  "armor" : 400,
]));


        }
	set("armor_type", "surcoat");
	set("no_store", 1);
	set("item_owner", "licz");
	set("no_sell", 1);
	set("stable", 37);
	set("consistence", 100);
        setup();
}

int query_autoload()
{
        return 1;
}
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// 隐藏物品
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}


int is_no_clone() { return 1; }

