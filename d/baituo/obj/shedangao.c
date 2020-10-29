// shedangao.c

inherit ITEM;

void create()
{
        set_name("蛇胆膏", ({"shedan gao", "gao"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", "这是珍贵补品『蛇胆膏』。\n");
                set("value", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_jing", me) >= query("max_jing", me) )
                return notify_fail("你现在吃『蛇胆膏』并无效用！\n");

        me->receive_curing("jing", 30);
        message_vision("$N吃下一块蛇胆膏，顿觉一股浩荡真气直涌上来，"
                       "精神立刻好转！\n", me);
        destruct(this_object());
        return 1;
}