#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"鸳鸯五珍脍"NOR, ({"dish"}));
        set_weight(80);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是传说中的御膳，一鸡一鸭经精心烤炙，再配以各种珍膳，不易吃到哦。\n");
                set("unit", "碟");
                set("value", 120);
                set("food_remaining", 30);
                set("food_supply", 30);
        }
}