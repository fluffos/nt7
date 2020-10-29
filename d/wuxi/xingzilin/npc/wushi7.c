// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include "../cnpc.h"

inherit NPC;

void create()
{
        object ob; 
        
        set_name(HIR "七品武士" NOR, ({ "wu shi", "wu"}));
        set("nickname", HIY "西夏一品堂" NOR);
        set("long", 
"西夏国有个讲武馆，叫做一品堂，是该国国王所立，堂中招聘武功高强之士，优礼供养。\n"
"这是一品堂中的普通七品武士，据说受赫连大将军带领，此来不知道对中原有什么图谋......\n"
        );
        
        set("age", 28);
        set("str", 35);
        set("dex", 22);
        set("con", 22);
        set("max_qi", 1800000);
        set("eff_qi", 1800000);
        set("qi", 1800000);
        set("max_jing", 2000000);
        set("eff_jing", 2000000);
        set("jing", 2000000);
        set("max_neili", 500000);
        set("neili", 500000);
        set("max_jingli", 500000);
        set("jingli", 500000);
        set("level", WU7_LEVEL);
        set("combat_exp", 80000000);
                set("jiali", 200);

        set_temp("apply/parry", 50);
        set_temp("apply/dodge", 50);
        set_temp("apply/dex", 20);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 10);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 10);

                set_skill("whip", 850);
                set_skill("jiujie-whip", 850);
        set_skill("dodge", 850);
        set_skill("kunlun-shenfa", 850);
        set_skill("parry", 850);
        set_skill("force", 850);
        set_skill("riyue-xinfa", 850);
        set_skill("cuff", 850);
        set_skill("huhe-quan", 850);

        map_skill("whip", "jiujie-whip");
        map_skill("parry", "jiujie-whip");
        map_skill("dodge", "kunlun-shenfa");
        map_skill("force", "riyue-xinfa");
        map_skill("cuff", "huhe-quan");
                prepare_skill("cuff", "huhe-quan"); 
 
        set("gift/exp", WU7_GIFT_EXP);
        set("gift/pot", WU7_GIFT_EXP / 5);
        setup();
        
                ob = new("/clone/weapon/changbian"); 
                ob->move(this_object()); 
                ob->wield(); 
       
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
        return 1;
}

void unconcious()
{
        die(query_last_damage_from());
}

void init()
{
        if (playerp(this_player())) kill_ob(this_player());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
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

                //移动惩罚消弱
                if (query_temp("xzz/ntrip", dob)>-1) addn_temp("xzz/ntrip", -1, dob);
                addn_temp("xzz/nkill", 1, dob);


        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
       
                                if( query("level", dob) <= query("level") ) 
                                {
                                }
                                else if( query("level", dob) <= query("level")*1.5 )
                                {
                                        exp /= 2;
                                        pot /= 2;
                                }
                                else if( query("level", dob) <= query("level")*2 )
                                {
                                        exp /= 4;
                                        pot /= 4;
                                }
                                else 
                                {
                                        exp = 100;
                                        pot = 100;
                                }

                                exp = invert_reborngiftd(dob, exp);
                                pot = exp / 4;

                n = 0;
                n = sizeof(t);

                                if (n > 1)
                                {
                                        exp /= n;
                                        pot /= n;
                                }

                                if (n)
                                {                                
                                        foreach(tob in t)
                                        {
                                                   if (objectp(tob) && living(tob) && environment(tob) == environment(this_object()))
                                                {
                                                                   addn("xingzilin/wushi7",1,tob);addn("xingzilin/exp",exp,tob);GIFT_D->delay_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "你的队伍杀死" + name() + "之后"]));

                                                 }
                                        }
                                }
                                else
                                {
                                                                   addn("xingzilin/wushi7",1,dob);addn("xingzilin/exp",exp,dob);GIFT_D->delay_bonus(dob,
                                                                          ([ "exp"      : exp,
                                                                                 "pot"      : pot,
                                                                                 "prompt"   : "你在杀死" + name() + "之后"]));
                                }

        }

                destruct(this_object());

        return;
}
