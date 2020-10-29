// nanhai.c

#include <ansi.h>

#define MAX_POINT     100000
#define MEMBER_D      "/adm/daemons/memberd" 

inherit NPC;

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

void unconcious()
{
/*
	    // 防止直接call_die()
		if (query("qi") > 100000 && query("no_call_die"))
		{
			revive();
			return;
		}
*/
        die(query_last_damage_from());
}

void init()
{
        set("env/combatd", 4, this_player());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int exp2, pot2;
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i;
	object *inv;
	
	object gift_ob;
	string s_gift, *key_s_gift;
	int gift_point;

        // 定义奖励物品列表
	mixed oblist;
		
	object env;

	oblist = query("oblist");


        if (0)
	{
		destruct(this_object());
		return;
	} 
/*
	    // 防止直接call_die()
		if (query("qi") > 100000)
		{
			revive();
			return;
		}
*/

	// 通知当前房间，以便计算刷新
	env = environment(this_object());
	env->npc_die(this_object());
	
        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

	if (! dob)
	{
		destruct(this_object());
		return;
	}
	
        t = dob->query_team();
	
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
       		
		n = 0;
                n = sizeof(t);
	/*
		if (n > 1)
		{
			exp /= n;
			pot /= n;
		}
*/
		if (n > 1)
		{
			exp /= 2;
			pot /= 2;
		}	

		if (n)
		{				
			foreach(tob in t)
			{
				if (! objectp(tob))continue;
						
				exp2 = exp;
				pot2 = pot;		
				/*       		
				// 佩带斩妖勋章增加10%
				if( query_temp("apply/zhanyao", tob) )
				{
				       	exp2 = exp2 + exp2 / 10;
				       	pot2 = pot2 + pot2 / 10;
				}
				*/
				if (objectp(tob) && living(tob))
				{
					if (environment(tob) == environment(dob))
						GIFT_D->delay_bonus(tob,
							([ "exp"      : exp2 + ((tob == dob) ? exp2 / 10 : 0),
						   	   "pot"      : pot2 + ((tob == dob) ? pot2 / 10 : 0),
						   	   "prompt"   : "你的队伍打败" + name() + "之后"]));
				}
			}
		}
		else
		{	/*       		
			// 佩带斩妖勋章增加10%
			if( query_temp("apply/zhanyao", dob) )
			{
				exp = exp + exp / 10;
				pot = pot + pot / 10;
			}
			*/
			GIFT_D->delay_bonus(dob,
				([ "exp"      : exp,
				   "pot"      : pot,
				   "prompt"   : "你在打败" + name() + "之后"]));
		}
        }

        // 一定几率掉物品在杀我的人身上dob
	if (objectp(dob) && environment(dob) == environment(this_object()))
	{
		key_s_gift = keys(oblist);
		s_gift = key_s_gift[random(sizeof(key_s_gift))];
		gift_point = oblist[s_gift];

		// 判断几率
		if( (MEMBER_D->is_valid_member(query("id", dob)) || random(4) == 1 )
			&& random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
		{
			// 获得物品--爆出物品
			gift_ob = new(s_gift);
			if (objectp(gift_ob))
			{
				message_vision(HIR "叮~~一声，从$N" HIR "身上掉出一样东西。\n" NOR, this_object(), dob);
set("who_get/id",query("id",  dob), 				gift_ob);
set("who_get/time", time()+60, 				gift_ob);//一分钟内只能自己捡取
				gift_ob->move(environment(this_object()));
			}
			else // 纪录之 
			{
					log_file("killed-gift-none", s_gift + "\n");
			}
		}
	}

	// 掉出金钱及其他物品
	if (1)
	{
		inv = all_inventory(this_object());
		inv -= ({ 0 });
           	i = sizeof(inv);
		while (i--)
            	{
	        	if (objectp(dob))
			{
 set("who_get/id",query("id",  dob), 			inv[i]);
set("who_get/time", time()+60, 			inv[i]);
			}
                 	inv[i]->move(environment(this_object()));
		}
	}

	destruct(this_object());

        return;
}
