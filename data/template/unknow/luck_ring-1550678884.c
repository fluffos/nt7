// luck_ring.c
// Create by TEMPLATE_D. Mon Feb 11 23:28:10 2019.
// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit RINGS;
 
void create()
{
	set_name("[45m幸运女神戒指[2;37;0m", ({ "luck ring" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("unit", "个");
	set("long", "[1;33m这便是幸运女神戴过的戒指，神光浮现。
[2;37;0m");
	set("value", 3000);
	set("no_sell", 1);
	set("rigidity", 8000);
	set("material", "tian jing");
	set("no_pawn", 1);
	set("armor_prop", ([ /* sizeof() == 1 */
  "armor" : 10,
]));
        }
        
	set("mod_mark", "A3022");
	set("mod_level", "M3002");
	set("mod_name", "[41;1m幸运女神之眷念[2;37;0m");
	set("quality_level", 4);

	set("armor_type", "rings");
	set("no_store", 1);
	set("item_owner", "kimi");
	set("stable", 50);
	set("consistence", 100);
        setup();
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

