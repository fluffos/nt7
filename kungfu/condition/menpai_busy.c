int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        me->apply_condition("menpai_busy", duration - 1);
        return 1;
}