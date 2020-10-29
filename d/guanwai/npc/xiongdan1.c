// xiongdan1.c

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("熊胆干", ({"xiongdan gan", "xiongdan", "gan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", "这是一副熊胆干。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
        return notify_fail("你要吃什么？\n");
        if (me->is_fighting()) return notify_fail("战斗中不能吃东西！\n");
        if (me->is_busy()) return notify_fail("你正忙着呢！\n");

        set("eff_qi",query("max_qi",  this_player()), this_player());
        message_vision("$N吃下一副熊胆干，觉得精神好多了。\n", this_player());
        destruct(this_object());
        return 1;
}

