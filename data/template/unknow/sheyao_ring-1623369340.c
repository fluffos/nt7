// sheyao_ring.c
// Create by TEMPLATE_D. Fri Jan 25 22:11:23 2019.
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
	set_name("[1;32m蛇妖指环[2;37;0m", ({ "sheyao ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("unit", "个");
	set("long", "[1;32m蛇妖指环是传说中蛇精佩带的指环，拥有神秘的力量！
[2;37;0m");
	set("value", 200000);
	set("material", "gold");
	set("armor_prop", ([ /* sizeof() == 5 */
  "str" : 4,
  "int" : 4,
  "con" : 6,
  "dex" : 6,
  "damage" : 200,
]));





	set("limit", ([ /* sizeof() == 2 */
  "scborn" : 1,
  "exp" : 1000000,
]));




        }
	set("armor_type", "rings");
	set("no_store", 1);
	set("item_owner", "licz");
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

