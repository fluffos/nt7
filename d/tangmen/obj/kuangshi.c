//kuangshi.c


inherit ITEM;

void create()
{
        set_name("铁矿石", ({"kuang shi", "shi", "stone"}));
        set_weight(60000);
        set("unit", "块");
        set("long", "这是一块尚未冶炼的精铁矿。\n");
        set("value", 1000);
        setup();
}