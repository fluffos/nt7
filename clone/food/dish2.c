// dish.c 菜肴

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("菜肴", ({ "dish" }));
        set_weight(40);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "份");
                set("remaining", 5);
                set("drink_supply", 15);
        }
             set("liquid", ([ 
                     "type": "soup", 
                     "name": "汤", 
                     "remaining": 15, 
                     "drunk_apply": 3, 
             ])); 
}
