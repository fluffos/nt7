// lugu.c 鹿茸

inherit ITEM;

void create()
{
        set_name("鹿茸", ({"lu rong", "rong"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一味极其珍贵的药材，鹿茸。\n");
                set("unit", "块");
                set("value", 1500);
        }
}