// nanhai.c

#include <ansi.h>

#define MAX_POINT     100
#define MEMBER_D      "/adm/daemons/memberd"

inherit NPC;

void create()
{
	set_name(HIW "千年蟾蜍" NOR, ({ "qiannian chanchu", "qiannian", "chanchu" }) );
	set("gender", "男性");
	set("age", 1000);
	set("long", @LONG
这是一只巨大的蟾蜍，口中吐着绿色毒气，甚是可怕。
LONG );
	set("combat_exp", 2000000000);
	set("shen_type", 0);
	set("attitude", "heroism");
        set("max_neili", 2000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 10000000);
	set("eff_qi", 10000000);
        set("qi", 10000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

        set("no_nuoyi", 1); // 不被挪移影响

        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 200);

		set_skill("unarmed", 1500);
		set_skill("sword", 1500);
		set_skill("parry", 1500);
		set_skill("dodge", 1500);
		set_skill("force", 1500);

        set("jiali", 1000);

        set_temp("apply/attack", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/damage", 1000);
        set_temp("apply/armor", 1500);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

		setup();
}

int accept_fight(object ob)
{
        message_vision("$N一声怪叫，扑了过来。\n",
                       this_object(), ob);
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

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(5 + random(5));
	me->receive_wound("qi", 3000 + random(3000), ob);
        return HIY "$N" HIY "周围毒气氤氲，直逼得$n" HIY "头晕目眩。\n" NOR;
}

void heart_beat()
{
		if (query("neili") < 1)						
			set("neili", query("max_neili"));

		::heart_beat();
}

void unconcious()
{
	    // 防止直接call_die()
		if (query("qi") > 100000)
		{
			revive();
			return;
		}
	
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的阅历
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i;

        // 定义奖励物品列表
		// 几率  X / 万分之一
		mixed oblist = ([
			"/clone/armor/fenghuang-chai2"           :        	1,
			"/clone/armor/haizhi-xin2"               :        	1,
			"/clone/armor/shengling-yaodai3"         :          1,
			"/clone/armor/shangu-zhixing3"           :          1,
			"/clone/fam/enchase/shenglong-zhihun"    :          1,
			"/clone/fam/enchase/shenglong-zhiyan"    :          1,

		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;
		
	    // 防止直接call_die()
		if (query("qi") > 100000)
		{
			revive();
			return;
		}

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
				message_vision("shit\n", this_object());
				destruct(this_object());
				return;
		}

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 2000 + random(5000);
                pot = 4500 + random(3000);
                weiwang = 1000 + random(3000);
                score = 2000 + random(2000);
				n = 0;
                n = sizeof(t);
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       weiwang /= 3;
                       score /= 3;
                }

				if (n >= 3)
				{
					exp /= n;
					pot /= n;
					weiwang /= n;
					score /= n;
				}

				if (n)
				{				
					foreach(tob in t)
					{
						  if (objectp(tob) && living(tob))
						 {
								   GIFT_D->delay_bonus(tob,
								          ([ "exp"      : exp + ((tob == dob) ? 1000 : 0),
									         "pot"      : pot + ((tob == dob) ? 1000 : 0),
										     "weiwang"  : weiwang + ((tob == dob) ? 1000 : 0),
											 "score"    : score + ((tob == dob) ? 1000 : 0),
									         "prompt"   : "你的队伍杀死" + name() + "之后"]), 999);

						 }
					}
				}
				else
				{
								   GIFT_D->delay_bonus(dob,
								          ([ "exp"      : exp,
									         "pot"      : pot,
										     "weiwang"  : weiwang,
											 "score"    : score,
									         "prompt"   : "你在杀死" + name() + "之后"]), 999);
				}

        }

        // 一定几率掉物品在杀我的人身上dob
		if (objectp(dob) && environment(dob) == environment(this_object()))
		{
			key_s_gift = keys(oblist);
			s_gift = key_s_gift[random(sizeof(key_s_gift))];
			gift_point = oblist[s_gift];

			// 判断几率
			if (MEMBER_D->is_valib_member(dob->query("id")) 
				&& random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
			{
				// 获得物品--爆出物品直接放在dob身上
				gift_ob = new(s_gift);
				if (objectp(gift_ob))
				{
					message_vision(HIR "叮~~一声，从$N" HIR "掉出一样东西，$n" HIR 
						           "赶紧拣了起来。\n" NOR, this_object(), dob);
					tell_object(dob, BLINK + HIG "你得到了" + gift_ob->name() + BLINK + HIG "。\n" NOR);
					gift_ob->move(dob, 1);
				}
				else // 纪录之 
				{
					log_file("killed-gift-none", s_gift + "\n");
				}
			}
		}

        // 消失
	message_vision("$N长啸一声，然后化为一滩血水，渗入地下。\n", this_object());

        // 判断是否可以学会perform tuitian
        if (dob->query_skill("jiuyin-hamagong", 1) && ! dob->query("can_perform/jiuyin-hamagong/puji"))
        {
        	dob->set("can_perform/jiuyin-hamagong/puji", 1);
        	dob->save();
        	
        	tell_object(dob, HIG "恭喜你，你通过杀死千年蟾蜍，领悟出了九阴蛤蟆功的绝招[推天式]!\n");
        }
        
        destruct(this_object());

        return;
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N长啸一声，化做一滩血水，渗入地下。\n", this_object());
       
		destruct(this_object());
		return;
	}
}
