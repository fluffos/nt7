// 粘糕。高丽特产。:-)

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("粘糕", ({"nian gao", "gao"}));
        set_weight(80);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是高丽的特产粘糕。\n");
                set("unit", "个");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}