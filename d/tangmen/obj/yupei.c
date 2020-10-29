// yupei.c
inherit ITEM;

void create()
{
        set_name("玉佩", ({"yu pei", "yu","pei"}));
        set_weight(500);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long",
"这是一块精美的蓝田玉，入手温润无比。\n");
        set("value", 80000);
                set("material", "stone");
        }
}