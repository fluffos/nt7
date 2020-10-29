// recover.c

int exert(object me, object target)
{
        int n, q;

        if (me != target)
                return notify_fail("你只能用内功调匀自己的气息。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的内力不够。\n");

        q=query("eff_qi", me)-query("qi", me);
        if (q < 10)
                return notify_fail("你现在气力充沛。\n");
             if (me->query_skill("force")) n = 100 * q / me->query_skill("force"); //redl repaired
        if( query("special_skill/self", me) )
                n = n * 7 / 10;
        if( query("breakup", me) )
                n = n * 7 / 10;
        if (n < 20)
                n = 20;
        if( query("neili", me)<n )
        {
                if (q > 1000000)
                        q=q/n*query("neili", me);
                else
                        q=q*query("neili", me)/n;

                n=query("neili", me);
        }

        addn("neili", -n, me);
        if (q < 1) q = 1;
        me->receive_heal("qi", q);
        
        message_vision("$N深深吸了几口气，脸色看起来好多了。\n", me);

        if( me->is_fighting() && !query("special_skill/self", me))me->start_busy(1);
        
        return 1;
}
