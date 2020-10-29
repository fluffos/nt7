 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("蛇胆", ({"she dan","dan"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一个蛇胆，可以食用，也可以用来炼药。\n");
                set("unit", "个");
                set("value", 100);
                set("food_remaining", 20);
                set("food_supply", 50);
                                set("heal",([
                                        "heals":60,
                                        ]));
        }
}