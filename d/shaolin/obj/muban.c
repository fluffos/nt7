inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_climb", "zou");
}

void create()
{
        set_name("木板", ({"mu ban", "ban"}));
        set_weight(200000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一块旧木板，搁在房梁上。\n");
                set("unit", "块");
                set("material", "wood");
        }
        setup();
}

int do_climb(string arg)
{
        object me = this_player();
        
        if (!id(arg))
                return notify_fail("你要走到哪儿去？\n");
        if( query_temp("marks/跳1", this_player()) )
        {
                write("你怎么没完没了地走？\n");
                return 1;
        }
        else 
        {
                message("vision",this_player()->name() + "小心翼翼地走到木板上,看上去脚有点发软。\n",
                        environment(me), ({me}) );
                write("你小心翼翼地走到了木板上,心想:还好我没有恐高症!。\n");
                set_temp("marks/跳1", 1, this_player());
                return 1;
        }
}
