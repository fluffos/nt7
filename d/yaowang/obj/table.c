// wood_table.c

inherit ITEM;

void create()
{
        set_name("大木桌", ({ "wood table" }) );
        set_weight(500);
        set_max_encumbrance(8000);
        set("no_get", 1);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("position", "on");
                set("prep", "on");
                set("unit", "张");
                set("long", "一张大木桌，足够几十个人同时吃饭。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }