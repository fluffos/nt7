//ken 1999.12.11
inherit ITEM;
void create()
{
        set_name("兵器架", ({ "兵器架","jia"}) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "座");
                set("long", "一个插满了各式各样的武器的架子。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
