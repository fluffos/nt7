// regenerate.c

//inherit SSERVER;

int exert(object me, object target)
{
        int neili_cost;
        int lvl;
        int heal;

        if (target != me)
                return notify_fail("你只能用内功恢复自己的精力。\n");
        
        heal=query("eff_jing", me)-query("jing", me);
        if (heal < 10)
                return notify_fail("你现在精气旺盛。\n");

        lvl = me->query_skill("force");
        if (lvl <= 0) lvl = 1;
        neili_cost = heal * 60 / lvl;
        if( query("breakup", me) )
                neili_cost = neili_cost * 7 / 10;
        if (neili_cost < 20) neili_cost = 20;
        if( neili_cost>query("neili", me) )
        {
                neili_cost=query("neili", me);
                heal = neili_cost * lvl / 60;
        }
        if (neili_cost < 20) neili_cost = 20;

        if( query("neili", me)<neili_cost )
                return notify_fail("你的内力不够。\n");

        addn("neili", -neili_cost, me);
        me->receive_heal("jing", heal);
        
        message_vision("$N深深吸了几口气，精神看起来好多了。\n", me);

        if (me->is_fighting()) me->start_busy(1);
        
        return 1;
}