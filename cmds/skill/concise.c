
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob, stone;
        string type;
        int p, mp;

        if( !str )
                return notify_fail("你要凝练什么物品？\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做这件事情吧。\n");

        if( me->is_fighting() )
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if( !objectp(ob = present(str, me)) )
                return notify_fail("你身上没有这件物品。\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("你的内功修为不够，难以凝练物品。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为不够，难以凝练物品。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你现在的内力不足，难以凝练物品。\n");

        if( !query("can_sign", ob) || !(p=query("quality_level", ob)) )
                return notify_fail("这东西似乎凝练不出什么。\n");

              if( sscanf(base_name(ob), "/data/%*s") || query("item_owner", ob) ) 
                      return notify_fail("你先解除该物品的被绑定状态。\n"); 

        /*
        if( !query("require/level", ob) || query("require/level", ob) < 20 )
                return notify_fail("必须是20级以上的装备才能凝练。\n");
        */

        message_vision(HIM "$N" HIM "将" + ob->name() +
                       HIM "握于掌中，默默运转内力，开始凝炼。\n" NOR, me);

        if (random(100)<50 )
        {
                message_vision(HIR "突然却见" + ob->name() +
                               HIR "嗤的化作一股青烟，什么都"
                               "没有留下。\n" NOR, me);
                destruct(ob);
                return 1;
        }

        if( query("skill_type", ob) )
                stone = new("/clone/enchase/weapon_soul"+p);
        else 
        {
                type = query("armor_type", ob);
                stone = new("/clone/enchase/"+type+"_soul"+p);
        }

        message_vision(HIM "霎时只见$N" HIM "掌心白雾蒸腾，似乎发"
                       "生了什么不同寻常的事情。\n" NOR, me);

        if( query("value", stone) )
        {
                mp=query("value", stone)/300;
                mp = 5 + random(mp);
                if (mp < 5) mp = 5;
                if (mp > 100) mp = 100;

                addn("magic_points", mp, me);
                tell_object(me, HIC "你通过凝练"+ stone->name() +
                                HIC "的过程，从而获得了" +
                                chinese_number(mp) + "点灵慧。\n" NOR);
        }
        addn("max_neili", -1, me);
        addn("neili", -3000, me);
        me->start_busy(5);

        stone->move(me, 1);
        destruct(ob);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式：concise <物品ID>

此指令可让你将某些物品凝炼。一般来说所有怪外掉落的装备都可以
被凝练，不过凝练物品需要比较高的内功等级和内力修为，每次成功
的凝练都会增加一定数量的灵慧，但是会消耗一点最大内力。
HELP);
        return 1;
}


