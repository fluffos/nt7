// ride.c

#include <ansi.h>

#define MEMBER_D        "/adm/daemons/memberd"

void create() { seteuid(getuid()); }

int no_clean_up() { return 1; }

int main(object me, string arg)
{
        object ob, env;

	if (! arg)
                return notify_fail("指令格式： lured <诱饵> \n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");

	if( !query("lure", ob) )
		return notify_fail("这东西好象不是诱饵吧！\n");

	if (me->is_busy())
		return notify_fail("等你忙完了再说吧！\n");

	if( query_temp("hunting", me) )
		return notify_fail("别着急，再等等！\n");

	message_vision(HIG "$N将" + ob->name() + "放在地上，躲在一旁静静守侯着 ……\n" NOR, me);

	me->start_busy(3 + random(5));
set_temp("hunting", 1, 	me);

	env = environment(me);

        call_out("do_hunt", 5 + random(5), me, env, ob);

	return 1;
}

void do_hunt(object me, object env, object ob)
{
	object obq;
	string* temp;
	string str;
	mapping quarry;
	int i, point;

	if (! objectp(me))return;
	if (! objectp(env))return;
	if (! objectp(ob))return;

	if( !query("can_hunting", env) )
		return;

	quarry=query("quarry", env);
	temp = keys(quarry);
	i = random(sizeof(temp));

delete_temp("hunting", 	me);

        // 获得几率判断是否动物出现
	point = quarry[temp[i]];
	if( MEMBER_D->is_valid_member(query("id", me)) )
		point += 3;

	if( query("level", ob)>1 )
		point=query("level", ob);

        if (random(100) >= point)
	{
		if (base_name(environment(me)) == base_name(env))
		{
			write(HIY "等了半天却不见猎物出现，你只好把" + ob->name() + HIY "收了起来。\n");
		}
		else
		{
			destruct(ob);
		}
		return;
	}	
	
	obq = new("/clone/quarry/" + temp[i]);
	obq->move(env);
set("owner",query("id",  me), 	obq);
        set("name", HIR+me->name()+"("+query("id", me)+")猎出的"+obq->name()+NOR, obq);
  
	if (environment(me) == env)
	{
		switch(random(4))
		{
			case 0:
			message_vision(HIG "不一会儿，一只" + obq->name() + HIG "窜了出来，将" + 
                                       ob->name() + HIG "一口咬在嘴里。\n" NOR, me);
			break;

			case 1:
			message_vision(HIM "转眼间，一只" + obq->name() + HIG "突然出现，将" + 
                                       ob->name() + HIG "吞进嘴里。\n" NOR, me);
			break;

			case 2:
			message_vision(HIW "良久，一只" + obq->name() + HIG "大摇大摆地走了出来，仔细地打量着" + 
                                       ob->name() + HIG "。\n" NOR, me);
			break;

			default:
			message_vision(HIC "少时，一只" + obq->name() + HIG "窜了过来，一口将" + 
                                       ob->name() + HIG "叼在了嘴上，相貌贪婪之极。\n" NOR, me);
			break;
		}
	}
	destruct(ob);
	return;
	
}


int help(object me)
{
	write(@HELP
指令格式 :

        lured <诱饵>：在当前地点放置诱饵等待猎物出现。
                     注：一次只能放一个诱饵。
                     
HELP
    );
    return 1;
}
