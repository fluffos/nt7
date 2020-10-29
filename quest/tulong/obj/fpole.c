inherit ITEM;

void create()
{
        set_name("钓鱼杆", ({ "fish pole" , "pole", "钓鱼杆"}) );
        set_weight(150);
        set_max_encumbrance(1);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("prep", "on");
                set("long", "一个用桃枝做成的钓鱼杆，上面还有含苞待放的桃花，显得十分新颖别致。可以用它来钓鱼(fishing)。\n");
                set("value", 150);
        }
}

void init()
{
        add_action("do_use", "fishing");
}

int do_use(string arg)
{
//        if( arg != "fish pole" ) return 0;

        tell_object(this_player(),"你掏出一个" + this_object()->name() + "。\n");
        environment(this_player())->fish_notify(this_object(), 0);

        return 1;
}

int is_container() { return 1; }
