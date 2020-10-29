int update_condition(object me, int duration)
{
        me->clear_condition("wei_pk");
        return 1;
        if (duration < 1) return 0;
        me->apply_condition("wei_pk", duration - 1);
        return 1;
}