// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include "../cnpc.h"

inherit NPC;

int is_boss() { return 1; }

void create()
{
        object ob; 
     
        set_name(HIR + "努尔海" + NOR, ({ "nuer hai", "nuer", "hai" }));
        set("nickname", HIY + "一品堂统领" + NOR);
        set("long", 
"西夏国有个讲武馆，叫做一品堂，是该国国王所立，堂中招聘武功高强之士，优礼供养。\n"
        );
        
        set("age", 40);
        set("str", 45);
        set("dex", 45);
        set("con", 45);
        set("int", 35);
        set("max_qi", BOSS2_QI_BASE);
        set("eff_qi", BOSS2_QI_BASE);
        set("qi", BOSS2_QI_BASE);
        set("max_jing", to_int(BOSS2_QI_BASE * HP_JING_PERCENT));
        set("eff_jing", to_int(BOSS2_QI_BASE * HP_JING_PERCENT));
        set("jing", to_int(BOSS2_QI_BASE * HP_JING_PERCENT));
        set("max_neili", to_int(BOSS2_QI_BASE * HP_NEILI_PERCENT));
        set("neili", to_int(BOSS2_QI_BASE * HP_NEILI_PERCENT));
        set("max_jingli", to_int(BOSS2_QI_BASE * HP_NEILI_PERCENT));
        set("jingli", to_int(BOSS2_QI_BASE * HP_NEILI_PERCENT));
        
        set("level", BOSS2_LEVEL);
        set("combat_exp", 2000000000);
                set("jiali", 10000);

                //set_temp("apply/add_blind", 100);//    : "致盲",                       // weapon 终极兵器 致盲-让对手失明
                set_temp("apply/add_freeze", 5);//   : "冰冻",                       // weapon 终极兵器 冰冻-迟缓，减缓对方攻击，攻击pfm速度降低，无任何防御，无躲闪，无招架，就是挨打
                set_temp("apply/add_burning", 30);//  : "灼烧",                       // weapon 终极兵器 灼烧-一定时间内目标不停的减少内力和气血condition
                //set_temp("apply/add_dizziness", 100);//: "眩晕",                       // weapon 终极兵器 昏睡-眩晕，不能进行任何行动，但生命通常会加速回复，受到攻击会醒来，否则15秒内一直不动，解除战斗状态，昏睡本来就是一个混战时，先把一个敌人排除出战斗，专心对付其他人的技能
                set_temp("apply/add_forget", 20);//   : "遗忘",                       // weapon 终极防具 遗忘-使对方忘记所有技能的绝招add_oblivion   
                set_temp("apply/add_weak", 10);//     : "虚弱",                       // weapon 终极兵器
                set_temp("apply/add_busy", 25);//     : "忙乱",                       // weapon 终极兵器

                set_temp("apply/avoid_blind", 100);//  : "忽视致盲",                   // armor/rings 终极防具
                set_temp("apply/avoid_freeze", 80);// : "忽视冰冻",                   // armor/rings 终极防具
                set_temp("apply/avoid_burning", 80);//: "忽视灼烧",                   // armor/rings 终极防具
                set_temp("apply/avoid_dizziness", 100);//: "忽视眩晕",                  // armor/rings 终极防具
                set_temp("apply/avoid_forget", 90);// : "忽视遗忘",                   // armor/rings 终极兵器
                set_temp("apply/avoid_weak", 85);//   : "忽视虚弱",                   // armor/rings 终极防具
                set_temp("apply/avoid_busy", 80);//   : "忽视忙乱",                   // armor/rings 终极防具
                set_temp("apply/reduce_busy", 80);//  : "化解忙乱",                   // armor/rings 终极防具
  
                set_temp("apply/reduce_damage", 60);//  : 化解伤害",                   // armor 终极防具 
                set_temp("apply/ap_power", 20);//  : "绝招攻击力",         // weapon/rings
                set_temp("apply/dp_power", 35);//  : "绝招防御力",         // armor
                set_temp("apply/da_power", 10);//  : "绝招伤害力",         // weapon/rings
                set_temp("apply/avoid_defense", 30);//  : "攻击无视目标防御",   // weapon/rings
                set_temp("apply/avoid_parry", 30);//  : "攻击无视目标招架",   // weapon/rings
                set_temp("apply/avoid_dodge", 30);//  : "攻击无视目标躲闪",   // weapon/rings
                set_temp("apply/avoid_force", 30);//  : "攻击无视内功防御",   // weapon/rings
                set_temp("apply/avoid_attack", 60);//  : "无视目标特殊攻击",   // armor

        if (!random(3))
        {
                set_skill("count", to_int(BOSS2_SKILL_LV * 2));
                set_skill("martial-cognize", to_int(BOSS2_SKILL_LV * 3));
        }
        else
        {
                set_skill("count", to_int(BOSS2_SKILL_LV * 0.5));
                set_skill("martial-cognize", to_int(BOSS2_SKILL_LV * 1.2));
        }
        
                        set_skill("force", BOSS2_SKILL_LV);
                                if (random(4) == 0)
                                {
                                        set_skill("xixing-dafa", BOSS2_SKILL_LV);
                                map_skill("force", "xixing-dafa");
                                }
                                else if (random(2))
                                {
                                        set_skill("biyun-xinfa", BOSS2_SKILL_LV);        
                                map_skill("force", "biyun-xinfa");
                                }
                                else
                                {
                                        set_skill("riyue-xinfa", BOSS2_SKILL_LV);        
                                map_skill("force", "riyue-xinfa");
                                }
                        set_skill("dodge", BOSS2_SKILL_LV);
                            switch (random(5))
                        {
                                case 0:
                                        set_skill("chanchu-bufa", BOSS2_SKILL_LV);
                                        map_skill("dodge", "chanchu-bufa");
                                        break;
                                case 1:
                                        set_skill("shuishangpiao", BOSS2_SKILL_LV);
                                        map_skill("dodge", "shuishangpiao");
                                        break;
                                default:
                                        set_skill("kunlun-shenfa", BOSS2_SKILL_LV);
                                        map_skill("dodge", "kunlun-shenfa");
                                        break;
                        }

        switch (random(10))
        {
                case 0:
                        set_skill("whip", BOSS2_SKILL_LV);
                        set_skill("riyue-bian", BOSS2_SKILL_LV);
                        map_skill("whip", "riyue-bian");
                        set_skill("strike", BOSS2_SKILL_LV);
                        set_skill("yinlong-shou", BOSS2_SKILL_LV);
                        map_skill("strike", "yinlong-shou");
                        set_skill("parry", BOSS2_SKILL_LV);
                        map_skill("parry", "yinlong-shou");
                                prepare_skill("strike", "yinlong-shou"); 
                        set("chat_chance_combat", 120);
                        set("chat_msg_combat", ({
                        (: perform_action, "whip.chan" :),
                        (: perform_action, "whip.shang" :),
                        (: perform_action, "strike.duo" :),
                        }) );
                        break;
                default:
                        set_skill("whip", BOSS2_SKILL_LV);
                        set_skill("liushui-bian", BOSS2_SKILL_LV);
                        map_skill("whip", "liushui-bian");
                        set_skill("strike", BOSS2_SKILL_LV);
                        set_skill("yinlong-shou", BOSS2_SKILL_LV);
                        map_skill("strike", "yinlong-shou");
                        set_skill("parry", BOSS2_SKILL_LV);
                        map_skill("parry", "yinlong-shou");
                                prepare_skill("strike", "yinlong-shou"); 
                        set("chat_chance_combat", 120);
                        set("chat_msg_combat", ({
                        (: perform_action, "whip.liuxing" :),
                        (: perform_action, "strike.duo" :),
                        }) );
                        break;
        }
        
        
        set("gift/exp", BOSS2_GIFT_EXP);
        set("gift/pot", to_int(BOSS2_GIFT_EXP / 5));
        setup();
        
                                ob = new("/clone/weapon/whip/tielian");
                                ob->move(this_object()); 
                                ob->wield(); 
                                set("myweapon", ob, this_object());
        call_out("chk_blade", 1, ob);
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

void chk_blade(object blade)
{
        object me; 
        string str;

        me = this_object();
        if (!objectp(me)) return;
        
        if (!query_temp("weapon") || !objectp(query("myweapon",me)))
        {
                if (objectp(query_last_damage_from())) query_last_damage_from()->start_busy(3+random(4));//给点时间我带武器，不论对方有多少pfm busy
                if(objectp(blade)) destruct(blade);
                blade = new("/clone/weapon/whip/tielian");
                set("myweapon", blade, me);
                blade->move(this_object()); 
                str = sprintf("%s" HIY "从屁股后面一摸，又拿出一条%s" HIY "握在手中。\n" NOR,
                                       query("name", me),
                                       query("name", blade));
                        tell_room(environment(me), str, me);
                blade->wield(); 
        }

        call_out("chk_blade", 1, blade);
        return;
}


void init()
{
        if (playerp(this_player())) kill_ob(this_player());
}

void die(object killer)
{
         int showexp;
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
                
                
        object me,ob;
        me = this_object();
        if(random(10) && //90%不能call die?
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                me->full_self();
                return;
        }
                
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
                
                exp = to_int(exp * (random(100)+950) / 1000);
                showexp = exp;                
                                
                                CHANNEL_D->channel_broadcast(CHANL_NAME, 
                                        query("name", dob) + "于无锡杏子林击杀"+HIY+"「一品堂统领」"+HIR+"努尔海"+NOR+"，获得"+chinese_number(get_show_giftexp(dob, showexp))+"点经验奖励。"
                                        );
                                        
                                exp = invert_reborngiftd(dob, exp);
                                pot = exp / 5;
                                
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
                                                                   addn("xingzilin/bossnu",1,tob);addn("xingzilin/exp",exp,tob);GIFT_D->delay_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "你的队伍杀死" + name() + "之后"]));

                                                 }
                                        }
                                }
                                else
                                {
                                                                   addn("xingzilin/bossnu",1,dob);addn("xingzilin/exp",exp,dob);GIFT_D->delay_bonus(dob,
                                                                          ([ "exp"      : exp,
                                                                                 "pot"      : pot,
                                                                                 "prompt"   : "你在杀死" + name() + "之后"]));
                                }

        }

                                ob = query("myweapon",me);
                                if(objectp(ob)) destruct(ob);
                destruct(this_object());

        return;
}




