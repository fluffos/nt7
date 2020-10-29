#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(HIR "元神经验果" NOR, ({"yuanshen guo", "yuanshen", "guo"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "\n这是一颗火红色的仙果，据说服用后能增强元神经验。\n"
                                      "*服用(eatysg yuanshen guo)后，元神可获得20万经验。\n" NOR);
                set("unit", "颗");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "eatysg");       
}

int do_use(string arg)
{
        int exp;
        object me = this_player();
        
        exp = 200000;
        
        if (environment(this_object()) != me)
                return notify_fail("你身上没有这个物品！\n");

        if (! me->query("thborn") ||
            ! me->query("yuanshen/status"))
                return notify_fail("你还没有获得元神！\n");
        
        if (me->query("yuanshen/exp4") >= 1600000000)
                return notify_fail("你的元神经验过高，不能再使用经验果了！\n");

        if (me->query("yuanshen/exp") >= 2000000000)
        {
                if (me->query("yuanshen/exp2") >= 2000000000)
                {
                        if (me->query("yuanshen/exp3") >= 1800000000)
                        {
                                if (me->query("yuanshen/exp4") >= 1600000000)
                                {
                                        // 不做处理
                                }
                                else
                                {
                                        me->add("yuanshen/exp4", exp);
                                }
                        }
                        else
                        {
                                me->add("yuanshen/exp3", exp);
                        }
                }
                else
                {
                        me->add("yuanshen/exp2", exp);
                }
        }
        else
        {
                me->add("yuanshen/exp", exp);
        }

        me->save();

        tell_object(me, HIG "你服下元神经验果，元身经验增加：" + sprintf("%d", exp) + "点。\n");
        
        log_file("yuanshen-guo", me->query("id") + " at " + ctime(time()) + " use yuanshen guo.\n");
        
        destruct(this_object());
        
        return 1;
}