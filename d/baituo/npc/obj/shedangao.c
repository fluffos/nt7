//
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("蛇胆膏", ({"shedan gao", "gao"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", "这是珍贵补品『蛇胆膏』。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if( (query("max_jing", me) >= 200) || (query("max_qi", me) >= 200) )
                return notify_fail("你吃『蛇胆膏』已无效用！\n");
        if( query("max_jing", me)<180 )
           {
            addn("max_jing", 10, me);
            addn("jing", 10, me);
            addn("max_qi", 10, me);
            addn("qi", 10, me);
           }
        else
           {
            addn("max_jing", 2, me);
            addn("jing", 2, me);
            addn("max_qi", 2, me);
            addn("qi", 2, me);
            }
        message_vision( "$N吃下一块蛇胆膏，顿觉一股浩荡真气直涌上来，
精，气大增...\n" , me);
        destruct(this_object());
        return 1;
}