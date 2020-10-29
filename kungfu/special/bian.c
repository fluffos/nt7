// bian.c 诡辩奇学
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "诡辩奇学" NOR; }

int perform(object me, string skill, string arg)
{
        int i;
      
        object ob;

        if (time() - me->query("special2/bian") < 600)
                return notify_fail("你刚施展完诡辩奇学，等下再说吧！\n");

        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("这里没有这个人！可能是你的格式有错误！\n"
                                   "格式 ： special bian <对象id> \n");


        if (! playerp(ob))return notify_fail("诡辩奇学只能对同门玩家使用！\n");

        if (ob->query("family/family_name") != me->query("family/family_name"))
                return notify_fail("诡辩奇学只能对同门玩家使用！\n");

        message_vision(HIM "$N" HIM "施展出诡辩奇学，诡辩之声不绝于耳 ……\n" NOR, me);

        if (me->query("gongxian") > 100000000)
        {
                tell_object(me, HIG "你的门派贡已经超过极限！\n");
                return 1;
        }
        
        me->add("gongxian", 1000 + random(101));
        me->start_busy(2);

        tell_object(me, HIG "你的门派贡献提高了！\n");

        me->set("special2/bian", time());

        return 1;
}
