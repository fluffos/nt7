#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
	if (duration < 1)
        {
		tell_object(me, HIR "执法精灵告诉你：“你已被禁闭二"
                                "十四小时，现在你自由了！”\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + me->name(1) + HIM + "刑满释放了。");
                set("combat/WPK", 0, me);
                set("combat/PKS", 0, me);
		return 0;
	}
	// 计划中不减少惩罚时间
	if( !query("doing", me))me->apply_condition("pk",duration-1);
	return 1;
}