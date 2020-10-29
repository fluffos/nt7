int dispel() { return 0; }

int update_condition(object me, int duration)
{
	if (duration < 1)
        {
		tell_object(me, "你禁闭完毕，可以离开了！\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "因为" + me->name(1) + "诚心悔过，被解除禁闭了。");
		return 0;
	}
	me->apply_condition("pk_punish", duration - 1);
	return 1;
}