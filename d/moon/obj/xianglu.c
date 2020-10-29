//ken 1999.12.11
inherit ITEM;
void create()
{
        set_name("缕金香炉", ({ "香炉", "缕金香炉"}) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "一个缕金的香炉。似乎有左(left)右(right)转动过的痕迹。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
