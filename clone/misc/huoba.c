// /clone/misc/fire.c
// Last Modified by Lonely on May. 15 2001

inherit ITEM;

void create()
{
        set_name("火把", ({"huo ba"}));
        set_weight(80);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一根火把，到了黑暗的地方就用(fire)得着了。\n");
                set("unit", "根");
                set("value", 100);
        }
}