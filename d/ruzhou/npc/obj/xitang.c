// Obj:/d/npc/obj/xitang.c
// llm 99/07
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("喜糖", ({"xitang", "tang"}));
        set_weight(80);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一包五颜六色的的喜糖。\n");
                set("unit", "包");
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}