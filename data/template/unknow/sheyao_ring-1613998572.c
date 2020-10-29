// sheyao_ring.c
// Create by TEMPLATE_D. Sun Apr  7 10:26:06 2019.
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
	set_name("[1;31m蛇妖指环[2;37;0m", ({ "sheyao ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("unit", "个");
	set("long", "[1;31m蛇妖指环是传说中蛇精佩带的指环，拥有神秘的力量！
[2;37;0m");
	set("value", 200000);
	set("material", "gold");
	set("armor_prop", ([ /* sizeof() == 6 */
  "str" : 8,
  "int" : 8,
  "con" : 10,
  "dex" : 10,
  "magic_find" : 20,
  "damage" : 400,
]));






	set("limit", ([ /* sizeof() == 2 */
  "scborn" : 1,
  "exp" : 12000000,
]));




        }
	set("armor_type", "rings");
	set("no_store", 1);
	set("item_owner", "step");
	set("no_sell", 1);
	set("stable", 25);
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

