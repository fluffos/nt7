// beg.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object ob, victim;
        int sp, dp;

        object where = environment(me);

        seteuid(getuid());

        if( query("family/family_name", me) != "丐帮" )
                  return notify_fail("只有乞丐才能乞讨！\n");

        if( query("no_beg", environment(me)) || 
            query("no_fight", environment(me)) )
                return notify_fail("这里不是你叫化子能来讨饭的地方！\n");

        if( query_temp("begging", me) )
                return notify_fail("你已经在向人家乞讨了！\n");

        if (! arg || sscanf(arg, "%s from %s", what, who) != 2)
                return notify_fail("指令格式：beg <物品> from <人物>\n");

        victim = present(who, environment(me));
        if (what != "gold" && what != "silver" && what != "coin")
                return notify_fail("你只能乞讨硬通货 :)\n");

        if (! victim || victim == me)
                return notify_fail("你想乞讨的对象不在这里。\n");

        if (! living(victim) || ! objectp(victim))
                return notify_fail("你要向谁乞讨？\n");

        if( query("family/family_name", victim) == "丐帮" )
                return notify_fail("你不能向乞丐乞讨！\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("玩家不能向巫师乞讨。\n");

        if( query("env/no_beg", me) )
                return notify_fail(victim->name() + "对你的乞讨理都不理！。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("一边打架一边要饭？你真是活腻了！\n");

        if (victim->is_fighting())
                return notify_fail(victim->name() + "正在打架，没空理你！\n");

        ob = present(what, victim);
        if (! ob) ob = present("gold", victim);
        if (! ob) ob = present("silver", victim);
        if (! ob) ob = present("coin", victim);

        if (! ob)
                return notify_fail( victim->name() + "身上看起来没有什麽让你感兴趣的东西。\n");

        if( query("equipped", ob) || query("no_drop", ob) )
                return notify_fail("这是那人的随身家伙，肯定不会给你。\n");

        sp = (int)me->query_skill("begging");
        sp = sp * sp * sp / 10;

        if (sp < 1) sp = 1;
        dp=query("jing", victim)+ob->value()/5;

        tell_object(me, "你装出可怜巴巴的样子，慢慢地向" + victim->name() + "走过去，伸出双手，想要"
                        +query("unit", ob)+ob->name()+"...\n\n");
        tell_object(victim, me->name() + "可怜巴巴地向你慢慢走过来，伸出手，说道：" + RANK_D->query_respect(victim) + "行行好，给我"
                        +query("unit", ob)+ob->name()+"吧...！\n\n");
        message("vision", "只见" + me->name() + "装出可怜巴巴的样子，慢慢地向"
                + victim->name() + "走过去，\n伸出双手，说道："
                + RANK_D->query_respect(victim) + "，行行好吧 ...\n\n", environment(me), ({ me, victim}) );

        set_temp("begging", 1, me);
        call_out( "compelete_beg", 3, me, victim, ob, sp, dp);
        return 1;
}

protected void compelete_beg(object me, object victim, object ob, int sp, int dp)
{
        int amount;
        int bcount;
        object ob1;
        object where;

        if (! objectp(me)) return;
        delete_temp("begging", me);

        where = environment(me);
        if (! objectp(ob) || ! living(me) || me->is_fighting())
                return;

        if (! victim || environment(victim) != environment(me))
        {
                tell_object(me, "太可惜了，你要乞讨的人已经走了。\n");
                return;
        }

        if (environment(ob) != victim)
        {
                tell_object(me, "太可惜了，人家好像已经没有" + ob->name() + "了。\n");
                return;
        }

        if (living(victim) && (random(sp + dp) > dp))
        {
                if( !query("money_id", ob) || !(amount=ob->query_amount()) )
                {
                        tell_object(me, "看来还是走吧，这家"
                                    "伙身上已经没有多少油水可榨了。\n");
                        return;
                }

                bcount = amount / 5;
                if (! bcount) bcount = 1;
                ob->set_amount(amount - bcount);

                ob1=new("/clone/money/"+query("money_id", ob));
                ob1->set_amount(bcount);
                ob1->move(me);

                tell_object(me, victim->name() + "低头想了一会，又看了看你，摇摇头，叹了口气，丢给你一" +
                                query("unit", ob1)+ob1->name()+"。\n");
                tell_object(victim, "你看着" +  me->name() +"的可怜样，叹了口气，丢给他一" +
                                query("unit", ob1)+ob1->name()+"。\n");

                      if (me->can_improve_skill("begging"))
                          me->improve_skill("begging",random(query("int", me)));

                      if( query("potential", me)<me->query_potential_limit() )
                        addn("potential", 1, me);

                addn("combat_exp", 1, me);
                if (! me->is_busy())
                        me->start_busy(3 + random(4));
        } else
        {
                if (random(sp) > dp / 2)
                {
                        message_vision(victim->name() + "狠狠"
                                       "地瞪了$N一眼，喝道：滚！"
                                       "$N吓了一跳，急忙扭头灰溜"
                                       "溜地走开了。\n", me);
                        if (! me->is_busy())
                                me->start_busy(3);
                        return;
                }

                tell_object(me, victim->name() + "扭过头去，对你理都不理。\n");
                tell_object(victim, "你扭过头去，对" + me->name() +
                            "理都不理。\n");
                message("vision", victim->name() + "扭过头去，对" +
                        me->name() +  "理都不理。\n",
                        environment(me), ({ me, victim }) );

                if (! me->is_busy())
                        me->start_busy(3);
        }
}

int help(object me)
{
        write(@HELP
指令格式 : beg <某物> from <某人>

HELP );
        return 1;
}
