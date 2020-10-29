// trunk.c
// Modified by haiyan

inherit ITEM;

void create()
{
        set_name("桃树枝", ({ "trunk" }));
        set_weight(1200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根从桃树上砍下来的树枝，可以把它削成桃木剑。\n");
                set("value", 0);
                set("material", "bamboo");
        }
}

void init()
{
        if (this_player() == environment())
        {
            add_action("do_make", "zao");
            add_action("do_make", "zuo");
            add_action("do_make", "xiao");
        }
}

int do_make(string arg)
{
        object me, weapon;
        object where, sword;
        me = this_player();
        weapon=query_temp("weapon", me);
        if (! arg || ! id(arg))
             return notify_fail("你要用什么做剑？\n");

        if (! objectp(weapon))
             return notify_fail("你不用工具就能做剑？\n");

        if( query("skill_type", weapon) != "dagger" )
             return notify_fail(weapon->name()+"用起来好像不太顺手。\n");

        where = environment(me);
        message_vision("$N举起手中的" + weapon->name() +
                       "，几下就把桃树枝削成了一把剑，并刻上了一些驱鬼的符号。\n", me);
        sword = new("/d/wudang/quest/obj/ghost_sword");
        sword->move(me);
        destruct(this_object()); 
        return 1;
}