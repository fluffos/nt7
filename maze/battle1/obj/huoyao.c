// This program is a part of NT MudLIB

inherit ITEM;

void create()
{
        set_weight(80000);
        set_name("火药", ({"huo yao", "powder"}));
        set("long", "这是一桶火药。\n");
        set("unit", "桶");
        set("value",100);
        set("load",15);
        setup();
}