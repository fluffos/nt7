// guanyuntai.c 观云台
// Modified by haiyan

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "观云台");
        set("long", @LONG
这里是武当山天柱峰的观云台。放眼望去，只见云海涌动，气势
磅礴。你心中微微一动，凝神静思，感觉在这里进行参悟(canwu)，静
观云的变化，于太极拳理似乎极有帮助。
LONG );
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room","1");
        set("exits", ([
                "westdown" : __DIR__"jinding",
        ]));
        set("coor/x", -340);
        set("coor/y", -420);
        set("coor/z", 190);
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}

int do_canwu(string arg)
{
        object me;
        int cost, quanli, lvl;

        me = this_player();
        quanli=query("taiji_quanli", me);
        lvl = me->query_skill("taiji-quan", 1);
        if (me->is_busy())
                return notify_fail("你现在还忙着，静不下心来参悟太极拳理。\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("你现在的精气不够，无法进行参悟。\n");

        if (lvl < 200)
                return notify_fail("你的太极功夫还不到家，不必在这里浪费时间了。\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("你要花多少潜能来参悟太极拳理？\n");

        if( cost >= query("potential", me)-query("learned_points", me) )
                return notify_fail("你现在没有这么多的潜能！\n");

        if (lvl >= 200 && lvl < 300 && quanli == 1)
                return notify_fail("你上次参悟出的太极拳理还未理解透彻，不要急于求成。\n");

        if (lvl >= 300 && lvl < 400 && quanli == 2)
                return notify_fail("你上次参悟出的太极拳理还未理解透彻，不要急于求成。\n");

        if (lvl >= 400 && lvl < 500 && quanli == 3)
                return notify_fail("你上次参悟出的太极拳理还未理解透彻，不要急于求成。\n");

        if (lvl >= 500 && quanli >= 4)
                return notify_fail("你已经彻底领悟了太极拳理，不必再参悟了。\n");

        if (cost < 100)
                return notify_fail("参悟太极拳理至少需要一百点潜能才能有所进步。\n");

        message_vision("$N盘膝而坐，静静地凝视着千变万化的流云，开始潜心钻研"
                       "太极拳理。\n", me);

        set_temp("potential_cost", cost, me);
        me->set_short_desc("正坐在地下凝神静思。");
        me->start_busy((:call_other, __FILE__, "canwu" :),
                       (:call_other, __FILE__, "halt_canwu" :));
        return 1;
}

int canwu(object me)
{
        int cost, hint;

        cost=query_temp("potential_cost", me);
        if (cost > 0)
             cost = random(2) + 1;
        else
             cost = 0;

        addn("learned_points", cost, me);
        switch (random(30))
        {
            case 0:
                    write("你怔怔地望着不断滚动的流云，似乎想到了些什么。\n");
                    break;

            case 1:
                    write("你默默思索，对太极以柔克刚的道理似乎又想通了点什么。\n");
                    break;

            case 2:
                    write("你看到脚下不住翻滚的白云，似乎想到了些“绵劲”的道理。\n");
                    break;

            case 3:
                    write("你双手圈动，似乎又想通了太极拳理的一些奥秘。\n");
                    break;
        }

        if( me->addn_temp("potential_cost",-cost) <= 0 )
        {
            message_vision(HIM "$N参悟完毕，觉得对更深一层的太极拳理好像似懂非懂。\n"NOR, me);
            me->set_short_desc(0);
            return 0;
        }

        if( !query("taiji_quanli", me) || query("taiji_quanli", me)<2 )
               hint = 10000;
        else if( query("taiji_quanli", me)<3)hint=20000;
              else  hint = 30000;

        if ((random(hint)) < me->query_int())
        {
             addn("taiji_quanli", 1, me);
             if( query("taiji_quanli", me)<4 )
                 message_vision(HIY "$N" HIY "参悟完毕，似乎从流云的变化中悟出了更"
                                "深的太极拳理，不禁面露微笑。\n" NOR, me);
             else
             {
                 message_vision(HIY "$N" HIY "参悟完毕，心中登时豁然，对太极拳理的诸般变化"
                                "已了然于胸，禁不住纵声长笑……\n\n" NOR, me);
                 write(HIC "你已经彻底参悟出了太极拳理！\n\n" NOR);
             }
             if (me->can_improve_skill("taiji-quan"))
                  me->improve_skill("taiji-quan", 200000);
             me->set_short_desc(0);
             return 0;
        }
        return 1;
}

int halt_canwu(object me)
{
        tell_object(me, "你中止了参悟。\n");
        message_vision("$N长叹一声，缓缓站了起来。\n", me);
        addn("potential", (query("learned_points", me)-query("potential", me))/5, me);
        delete_temp("potential_cost", me);
        me->set_short_desc(0);
        return 1;
}
