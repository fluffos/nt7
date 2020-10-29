// lupi.c 野鹿皮

inherit ITEM;

void create()
{
        set_name("野鹿皮", ({"lu pi", "pi"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一张完整的野鹿皮，摸上去柔软光滑。\n");
                set("unit", "张");
                set("value", 200);
        }
}