// shanshen.c 老山参

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("老山参", ({"laoshan shen", "shen"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "株");
                set("long", "这是一株沾满山泥的长白老山参。\n");
                set("value", 10000);
                set_weight(100);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
        return notify_fail("你要吃什么？\n");

        addn("eff_qi", 20, this_player());

        message_vision("$N吃下一株老山参，只觉得浑身一股热气兜底冒了上来 !\n", this_player());
        destruct(this_object());
        return 1;
}