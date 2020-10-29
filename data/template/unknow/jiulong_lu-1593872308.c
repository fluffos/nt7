// jiulong_lu.c
// Create by TEMPLATE_D. Sun Feb 17 09:29:19 2019.
// jlding.c 九龙鼎

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("[1;33m九龙[2;37;0m[31m神火[2;37;0m[33m炉[2;37;0m", ({ "jiulong lu" }));
        set_weight(1200);
        set_max_encumbrance(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("unit", "个");
	set("long", "一个周边镶嵌九条龙的炉，颇为沉重，特殊质地，乃炼丹神器。
");
	set("value", 20000);
	set("auto_load", 1);
	set("can_summon", 1);
	set("item_prop", ([ /* sizeof() == 2 */
  "liandan-shu" : 300,
  "medical" : 900,
]));

        }
	set("no_store", 1);
	set("item_owner", "kimi");
	set("no_sell", 1);
        setup();
}

int is_container() { return 1; }

int can_make_medicine() { return 1; }
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

