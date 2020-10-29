#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIG"岁寒三友"NOR, ({"dish"}));
        set_weight(80);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "松仁加上酸梅、竹笋做成，一碟别出心裁的小菜。\n");
                set("unit", "碟");
                set("value", 120);
                set("food_remaining", 10);
                set("food_supply", 30);
        }
}