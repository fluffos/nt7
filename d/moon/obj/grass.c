//ken 1999.12.11
inherit ITEM;
void create()
{
        set_name("花草", ({ "花草", "grass"}) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", "一片茂密的花草丛。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
