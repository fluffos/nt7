// lugu.c 野鹿骨

inherit ITEM;

void create()
{
        set_name("鹿骨", ({"lu gu", "gu", "bone"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一根刚刚剔出来的野鹿骨头。\n");
                set("unit", "根");
                set("value", 300);
        }
}