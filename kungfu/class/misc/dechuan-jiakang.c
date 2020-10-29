#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// X小时后更新
#define UPDATE_TIME          60 * 3600
// 出现地点
#define UPDATE_PLACE         "/d/suzhou/baodaiqiao"
// BOSS文件
#define BOSS_FILE            "/kungfu/class/misc/dechuan-jiakang"

// 经验过高后无任何奖励
#define MAX_EXP              300000000

inherit NPC;

void create()
{
        set_name(HIR "德川家康" NOR, ({ "dechuan jiakang boss",}));
        set("title", HIR "德川幕府大将军" NOR);
        set("gender", "男性");
        set("age", 42);
        set("long", @LONG
扶桑国德川幕府大将军，乃一流的武士。
LONG);
        set("attitude", "friendly");
        set("str", 60);
        set("int", 60);
        set("con", 60);
        set("dex", 60);
        set("per", 20);
        set("shen_type", 0);

	set("no_nuoyi", 1); // 不被挪移影响
	
        set("qi", 72000000);
        set("max_qi", 72000000);

        set("jing", 4000000);
        set("max_jing", 4000000);
        set("jingli", 4000000); 
        set("max_jingli", 4000000); 

        set("neili", 80000); 
        set("max_neili", 80000); 
        set("jiali", 4000); 
        set("combat_exp", 120000000);

	set("reborn/times", 1);
	set("special_skill/guimai", 1);
	
        set_skill("force", 1600);
        set_skill("pixie-jian", 1600);
        set_skill("surge-force", 1600);
        set_skill("liumai-shenjian", 1600);
        set_skill("sword", 1600);
        set_skill("finger", 1600);
        set_skill("whip", 1600);
        set_skill("dodge", 1600);
        set_skill("parry", 1600);
        set_skill("unarmed", 1600);
        set_skill("strike", 1600);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1600);
        set_skill("throwing", 1600);
        set_skill("jueqing-quyu", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 1600);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",20000);
        set_temp("apply/defense", 20000);
        set_temp("apply/damage", 16000);
        set_temp("apply/unarmed_damage", 16000);
        set_temp("apply/armor", 30000);
        set_temp("apply/fy", 10);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.duo and sword.gui") :),
                (: command("perform sword.pi and sword.po") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.jian twice" :),
                (: perform_action, "finger.tian twice" :),
        }) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
}

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
        kill_ob(ob);
        return -1;	
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(5 + random(6));
	me->receive_wound("qi", 8500 + random(5600), ob);
        return HIY "$N" HIY "怒喝一声，奋力反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)						
		set("neili", query("max_neili"));

	return ::heart_beat();
}

void unconcious()
{
	// 防止直接call_die()
	if (query("qi") > 600000)
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
        int gongxian;           // 贡献
        int tihui;              // 体会
        int score;              // 需要瓜分的阅历
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int ysg;
        int i;

        // 定义奖励物品列表
	// 几率  MAX_POINT 分之 X
	mixed oblist = ([
			"/clone/misc/boss_item/yinghua-zan"          :         240,			
			"/clone/armor/fudai"                         :         100,
			"/clone/fam/enchase/xuanbing-shi2"           :          80,
			"/clone/armor/fusang/jiakang-toudai"         :         200,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;

	        // 防止直接call_die()
		if (query("qi") > 600000)
		{
			revive();
			return;
		}

                // 找到杀了我(NPC)或是打晕我的人
                if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
			//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
			destruct(this_object());
			return;
		}

                t = dob->query_team();

	        if (objectp(dob) && environment(dob) == environment(this_object()))
	        {
	                exp = 300000 + random(390000);
	                pot = 500000 + random(600000);
	                gongxian = 4400 + random(8200);
	                tihui = 50000 + random(65000);
			n = 0;
	                n = sizeof(t);

	                if (! n || n < 3)
	                {
	                       exp /= 3;
	                       pot /= 3;
	                       weiwang /= 3;
	                       score /= 3;
	                       tihui = 0;	                       
	                }

			if (n >= 3)
			{
				exp /= n;
				pot /= n;			
			}
	
			if (n)
			{				
				foreach(tob in t)
				{
					
					if (objectp(tob) && living(tob))
					{
						if (tob->query("combat_exp") >= MAX_EXP)continue;
						if (environment(tob) == environment(dob))
							GIFT_D->delay_bonus(tob,
								([ "exp"      : exp + ((tob == dob) ? 30000 : 0),
								   "pot"      : pot + ((tob == dob) ? 30000 : 0),
								   "mar"      : tihui + ((tob == dob) ? 3000 : 0),
								   //"gongxian" : tob->query("family/family_name") == "昆仑派" ? gongxian : 0,
								   "prompt"   : "你的队伍打败" + name() + "之后"]), 999);
	
					}
				}
			}
			else
			{
				if (dob->query("combat_exp") < MAX_EXP)
					GIFT_D->delay_bonus(dob,
						 ([ "exp"      : exp,
					    	    "pot"      : pot,
					    	    "prompt"   : "你在打败" + name() + "之后"]), 999);
			}
	
	        }
		
	        // 一定几率掉物品在杀我的人身上dob
		if (objectp(dob) && environment(dob) == environment(this_object()) && 
		    dob->query("combat_exp") < MAX_EXP)
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
	        if (0)
	        {
	        	command("chat 中原果然是能人辈出 ……");
		}/*
		else
		{
			message_vision(HIG "猛然间，$N " HIG " 向后一跳，随手仍出一颗黑色小丸，顿时腾起一片烟雾 ...\n" NOR, 
			               this_object());
			command("chat 哼，雕虫小技，不陪你们玩了，告辞！");
			CHANNEL_D->do_channel(this_object(), "rumor", "听说" + name() + HIM "从古墓中盗得珍宝后，夺路而逃。" NOR);
		}
*/
		// 设置更新
		//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
		// 1/200几率掉出无名铜人
		if (random(200) < 1)
		{
			object ob_tongren;
			ob_tongren = new("/clone/fam/item/wuming-tongren");			
			message_vision(HIR "当~~一声，从$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
			ob_tongren->set("who_get/id", "NONE");
			ob_tongren->set("who_get/time", time() + 30); // 30秒内都不能捡取		
			ob_tongren->move(environment(this_object()));
		}
		
		// 特殊活动爆物品，统一调用giftd接口
		GIFT_D->fuben_boss_gift(this_object());								
		
		destruct(this_object());
	
	        return;
}

void remove()
{
	MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
	return;
}
