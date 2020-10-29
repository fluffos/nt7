// This program is a part of NT MudLIB

inherit ITEM;

void create()
{
        set_weight(30000);
        set_name("弹头", ({"dan tou"}));
        set("long", "这是一枚炮弹弹头。\n");
        set("unit", "枚");
              
        set("value",100);
        setup();
}