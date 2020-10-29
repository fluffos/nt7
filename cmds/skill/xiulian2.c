
inherit F_CLEAN_UP;

#include <ansi.h>

#define SK_ID           "yinyang-shiertian"
#define SK_NAME         "阴阳九转十二重天"

int outing(object me, string FLAG_ID, string FLAG_NAME, int DIFF);
int halt_outing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object where;
	string FLAG_ID, FLAG_NAME;
	int DIFF, SK_LV;

	seteuid(getuid());
	where = environment(me);

	if (! arg)return notify_fail("指令格式：xiulian <境界>，请参见相关help文件。\n");

	if (arg != "yinyang" && arg != "qiankun" && arg != "shier")
			return notify_fail("指令格式：xiulian <境界>，请参见相关help文件。\n");	
	
	if (arg == "yinyang")
	{
			FLAG_ID = "yinyang-shiertian/yinyang";
			FLAG_NAME = "阴阳境界";
			if (me->query(FLAG_ID))
				return notify_fail("你已经修炼过" + FLAG_NAME + "了，没有必要再来一遍吧！\n");
			SK_LV = 380;
			DIFF = 100 + 3 * me->query(FLAG_ID);
	}
	else
	if (arg == "qiankun")
	{			
			if (! me->query("yinyang-shiertian/yinyang"))
					return notify_fail("必须修炼成功阴阳境界后方能修炼乾坤境界。\n");
			
			FLAG_ID = "yinyang-shiertian/qiankun";
			if (me->query(FLAG_ID) >= 9)
					return notify_fail("你已经修炼成乾坤境界了，没必要再来一遍吧！\n");

			// 九十六小时内不得再次修炼
			if (time() - me->query("last_xiulian_end") < 96 * 3600)
					return notify_fail("离上次修炼完成还不到九十六小时，不能再次修炼乾坤境界，否则你将走
火入魔。\n");
			
			FLAG_NAME = "乾坤境界第" + chinese_number(me->query(FLAG_ID) + 1) + "层";
			SK_LV = 480;
			DIFF = 100 + 5 * me->query(FLAG_ID);
	}
	else // 12重天境界	
	{
			if (me->query("yinyang-shiertian/qiankun") < 9)
					return notify_fail("必须修炼成功乾坤境界后方能修炼十二重天境界。\n");
			
			FLAG_ID = "yinyang-shiertian/shier";
			if (me->query(FLAG_ID) >= 12)
					return notify_fail("你已经修炼成十二重天境界了，没必要再来一遍吧！\n");

			// 一百二十小时内不得再次修炼
			if (time() - me->query("last_xiulian_end") < 120 * 3600)
					return notify_fail("离上次修炼完成还不到一百二十小时，不能再次修炼十二重天境界，否则
你将走火入魔。\n");
			
			FLAG_NAME = "十二重天境界第" + chinese_number(me->query(FLAG_ID) + 1) + "层";
			SK_LV = 600;
			DIFF = 100 + 6 * me->query(FLAG_ID);			
	}
	if (me->query_skill(SK_ID, 1) < SK_LV)
			    return notify_fail("你" SK_NAME "等级不够，无法修炼！\n");

    if (! where->query("no_fight"))
                return notify_fail("在这里修炼？不太安全吧？\n");

    if (! where->query("sleep_room"))
                return notify_fail("你得找一个能够休息的地方闭关修炼修行。\n");

	if (me->is_busy())
				return notify_fail("你现在正忙着呢。\n");

    if (me->query("potential") - me->query("learned_points") < 10000)
                return notify_fail("你的潜能不够，没法闭关修行。\n");

	if ((int)me->query("qi") * 100 / me->query("max_qi") < 99)
				return notify_fail("你现在的气太少了，无法静心闭关。\n");

	if ((int)me->query("jing") * 100 / me->query("max_jing") < 99)
				return notify_fail("你现在的精太少了，无法静心闭关。\n");

    if ((int)me->query("max_jingli") < 2000)
                return notify_fail("你觉得精力修为颇有不足，看来目前还难以修炼。\n");

	if ((int)me->query("jingli") * 100 / me->query("max_jingli") < 99)
				return notify_fail("你现在的精力太少了，无法静心闭关修炼。\n");

	message_vision("$N盘膝坐下，开始冥神运功，闭关修行。\n", me);
    me->set("startroom", base_name(where));
    me->set("doing", "xiulian");
    CLOSE_D->user_closed(me);
	me->start_busy(bind((:call_other, __FILE__, "outing", me, FLAG_ID, FLAG_NAME, DIFF :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));

	tell_object(me, HIC "你开始闭关苦修，试图修炼" + FLAG_NAME + "。\n" NOR);
	 
	/*
    CHANNEL_D->do_channel(this_object(), "rumor",
                          sprintf("%s%s(%s)开始闭关苦修，试图修炼" + FLAG_NAME + "。",
                          ultrap(me) ? "大宗师" : "",
     			          me->name(1), me->query("id")));
	*/
	return 1;
}


int continue_outing(object me)
{
		me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CLOSE_D->user_closed(me);
		tell_object(me, HIR "\n你继续闭关苦修，试图突破新的境界...\n" NOR);
        return 1;
}

private void stop_outing(object me)
{
        CLOSE_D->user_opened(me);
		if (! interactive(me))
		{
			me->force_me("chat* sigh");
			call_out("user_quit", 0, me);
		}
}

int outing(object me, string FLAG_ID, string FLAG_NAME, int DIFF)
{
        string msg;
		int cost_lunhui_point;

        if (me->query("potential") <= me->query("learned_points"))
        {
                tell_object(me, "你潜能耗尽，没有办法继续下去了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                CLOSE_D->user_opened(me);
				/*
        		CHANNEL_D->do_channel(this_object(), "rumor",
                                  sprintf("听说%s(%s)闭关修炼结束，似乎没有什么成果。",
								  me->name(1), me->query("id")));
				*/
				if (! interactive(me))
				{
					me->force_me("chat* sigh");
					call_out("user_quit", 0, me);
				}

                return 0;
        }

        me->add("learned_points", 1);

        // if (random(DIFF) && ! wizardp(me))return 1;

        if ((random(3) == 1 && random(DIFF * 100) < me->query_con()) || wizardp(me) && FLAG_ID != "yinyang-shiertian/shier")
        {
        		// 重启后FLAG_ID = 0
        		if (! FLAG_ID)
        		{
				if (! interactive(me))
				{
					me->force_me("chat* sigh");
					call_out("user_quit", 0, me);
				}        
				return 0;
        		}

				// 消耗轮回点
				if (FLAG_ID == "yinyang-shiertian/yinyang" && me->query("scborn/cur_lunhui_point") < 2 && ! me->query("thborn/ok"))
				{
					tell_object(HIR "你的轮回点不足。\n" NOR);
                			CLOSE_D->user_opened(me);
					if (! interactive(me))
					{
						me->force_me("chat* sigh");
						call_out("user_quit", 0, me);
					}
					return 0;
				}
				if (FLAG_ID == "yinyang-shiertian/qiankun" && me->query("scborn/cur_lunhui_point") < 3 && ! me->query("thborn/ok"))
				{
					tell_object(HIR "你的轮回点不足。\n" NOR);
                			CLOSE_D->user_opened(me);
					if (! interactive(me))
					{
						me->force_me("chat* sigh");
						call_out("user_quit", 0, me);
					}
					return 0;
				}
				if (FLAG_ID == "yinyang-shiertian/shier" && me->query("scborn/cur_lunhui_point") < 4 && ! me->query("thborn/ok"))
				{
					tell_object(HIR "你的轮回点不足。\n" NOR);
                			CLOSE_D->user_opened(me);
					if (! interactive(me))
					{
						me->force_me("chat* sigh");
						call_out("user_quit", 0, me);
					}
					return 0;
				}

                message_vision(HIY "只见$N" HIY "头上现出万朵金莲，光"
                               "华四射，一时间麝香扑鼻、氤氲遍地！\n" NOR, me);
                tell_object(me, HIW "你觉得精力源源而生，忽然心如止水，如身出"
                            "天际，无源无尽、登时大彻大悟。\n" NOR);
				tell_object(me, HIG "恭喜你，修炼成 " + FLAG_NAME + " 。\n" NOR);

                me->add(FLAG_ID, 1);
				if (! me->query("thborn/ok"))
				{
					// 消耗轮回点
					if (FLAG_ID == "yinyang-shiertian/yinyang")
					{
						
						me->add("scborn/cur_lunhui_point", -2);
						me->save();
					}
					if (FLAG_ID == "yinyang-shiertian/qiankun" && me->query("yinyang-shiertian/qiankun") == 9)
					{
						me->add("scborn/cur_lunhui_point", -3);
						me->save();
					}
					if (FLAG_ID == "yinyang-shiertian/shier" && me->query("yinyang-shiertian/shier") == 12)
					{
						me->add("scborn/cur_lunhui_point", -4);
						me->save();
					}
				}
				/*
        		CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)经过闭关苦修，终"
                                      "于参悟出其中奥妙，修炼出" + FLAG_NAME + "。",
									  me->name(1), me->query("id")));
				*/
                CHAR_D->setup_char(me);
                stop_outing(me);
                return 0;
        }

        switch (random(4))
        {
        case 0:
                msg = "你闭目凝神，试图进入无我境界。\n";
                break;

        case 1:
                msg = "你试图将元神与肢体分离，融入" + SK_NAME + "无上境界。\n";
                break;

        case 2:
                msg = "你试图将元神逼出七窍，然后周游四处复又收回。\n";
                break;

        default:
                msg = "你缓缓呼吸吐纳，将空气中水露皆收为己用。\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_outing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了闭关修炼。\n");
        message_vision(HIY "$N" HIY "轻轻叹了一口气，缓缓的睁开眼。\n\n" NOR, me);
        me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
		/*
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "闭关修炼中途突然复出。");
		*/
		return 1;
}

private void user_quit(object me)
{
	if (! me || interactive(me))
		return;

	me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : xiulian [境界]

该指令可使你修炼某些特殊境界。

HELP );
        return 1;
}

