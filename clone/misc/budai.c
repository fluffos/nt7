inherit ITEM;
void create()
{
     set_name("布袋", ({ "budai", "dai", "bag" }));
        set_weight(100);
        set_max_encumbrance(1000000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
         set("long", "一只用麻布织成的袋子，好像将东西放在里面。\n");
                set("value", 100);
                set("no_give", 1);
                         }
}

int is_container() { return 1; }

int no_limit_amount() { return 1; }