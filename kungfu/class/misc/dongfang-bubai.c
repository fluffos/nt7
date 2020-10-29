#include <ansi.h>

#define MAX_POINT 100

inherit BOSS;

void damage_all();
void check_weapon();

void create()
{
        set_name(HIR "东方不败" NOR, ({ "dongfang bubai", "dongfang", "bubai" }) );
        set("title", HIG "影魔" NOR);
        set("long", HIR "东方不败一生未真正败过，若非杨莲亭令其分心，令狐冲和\n"
                        "任我行等人，必将死在其手下。乃金庸十四部里出场角色武\n"
                        "功最高者之一，不在独孤求败之下。\n" NOR);

        set("gender", "无性");
        set("age", 39);

        set("str", 800);
        set("int", 800);
        set("con", 800);
        set("dex", 800);

        set("shen", 0);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/reduce_busy", 100);
        set_temp("apply/avoid_forget", 100);

        set("reborn/times", 1);

        set("max_qi", 2100000000);
        set("eff_qi", 2100000000);
        set("qi", 2100000000);

        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000); 
        set("jingli", 1000000000);  

        set("neili", 200000000);
        set("max_neili", 1000000);
        set("jiali", 50000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 5000);
        set_skill("finger", 5000);
        set_skill("claw", 5000);
        set_skill("strike", 5000);
        set_skill("hand", 5000);
        set_skill("cuff", 5000);
        set_skill("parry", 5000);
        set_skill("dodge", 5000);
        set_skill("force", 5000);
        set_skill("sword", 5000);
        set_skill("blade", 5000);
        set_skill("zuoyou-hubo", 2500);

        set_skill("kuihua-mogong", 5000);
        set_skill("qiankun-danuoyi", 5000);
        set_skill("martial-cognize", 5000);
        set_skill("literate", 5000);
        set_skill("huajia-su", 800);

        set_skill("jingluo-xue", 4000);

        set("no_nuoyi", 1); // 不被挪移影响
        
        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("strike", "kuihua-mogong");
        map_skill("hand", "kuihua-mogong");
        map_skill("cuff", "kuihua-mogong");
        map_skill("claw", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");
        
        prepare_skill("unarmed", "kuihua-mogong");
        prepare_skill("finger", "kuihua-mogong");

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: perform_action, "unarmed.fenshen" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),

              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "roar" :), 
              (: exert_function, "recover" :),   
              (: exert_function, "recover" :), 
              (: exert_function, "dispel" :), 
              (: check_weapon :),

        }));

        set("my_life", 1); // 当气血低于10%的时候补满一次，设置该参数为0

        setup();

        // 衣服
        carry_object("/kungfu/class/riyue/dongfang/changpao")->wear();

        // 武器
        carry_object("/kungfu/class/riyue/dongfang/zhen")->wield();

        // 设置地点
        //set("startroom", "/d/shenlong/huodong1");
}

// 全屏伤害 毁灭一击
/*
东方不败具备毁灭一击，随机发动，全场100%命中，伤血及上限80%
-- 套装对其具备克制作用，如下：$HIG$
   -= 通玄套装: 50%几率抵御毁灭一击，同时毁灭一击若抵御失败，伤血及上限50%$HIM$
   -= 鸿钧套装: 具备通玄套装的特性。同时，命中东方不败后对其追加一次伤害和
                忙乱效果。
                例如本次命中东方不败伤害为10万，则再追加10万伤害，同时令其
                忙乱5至10秒。$HIR$
   -= 造化套装:90%几率抵御毁灭一击，同时毁灭一击若抵御失败，伤血及上限30%
               命中东方不败后对其追加二次伤害和忙乱效果。例如本次命中东方不
               败伤害为10万，则再追加20万伤害，同时令其忙乱5至10秒。
               命中东方不败后70%追加封招10秒。$NOR$
*/
void damage_all()
{
        string msg;
        object *obs;
        int i, tzlv;
        
        if( !environment() )
        {
                set_heart_beat(0);
                return;
        }
        
        msg = HIG "$N" HIG "一声尖啸，化作两道残影，伴随着此起彼伏的尖啸，两道残影化作四道，四道"
                  "化作八道，十六道，三十二道，六十四道……万千鬼影弥漫四周，快捷无比，鬼魅怪异。"
                  "忽然间，金光一闪，无数银针从四面八方激射而来，令所有人都窒息！\n" NOR;
        
        message_vision(sort_msg(msg), this_object());
        
        obs = all_inventory(environment(this_object()));
        for (i = 0; i < sizeof(obs); i++)
        {
                reset_eval_cost();
                
                if (! obs[i]->is_character() || obs[i] == this_object())
                        continue;

                tzlv = to_int(query_temp("modequip_itemmake_level", obs[i])); 
                // 套装等级在2以下的100%收到80%的气血上限伤害
                // 非玩家生物肯定没有套装，也是100%受伤
                if ( tzlv < 2 || ! playerp(obs[i]))
                {
                        set("last_damage_from", this_object(), obs[i]);
                        obs[i]->receive_wound("qi",query("max_qi", obs[i])/5*4,this_object());
                        message_vision("$N" HIY "惊恐万分，已经毫无招架之力，数道银针穿胸而过，"
                                           "猛然喷出一口鲜血，倒退几步，经脉尽伤，无法动弹！\n" NOR, obs[i]);
                        obs[i]->start_busy(10);
                }
                else if (tzlv == 2)
                {
                        // 50%抵御，若未成功，则伤害为50%
                        if (random(2))
                        {
                                message_vision("$N" HIG "惊恐万分，已经毫无招架之力，突然全身一道绿光笼罩，其"
                                                   "身穿的【通玄套装】将所有伤害全部抵御！\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "惊恐万分，已经毫无招架之力，数道银针穿胸而过，"
                                                   "猛然喷出一口鲜血！\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }
                }
                else if (tzlv == 3)
                {
                        if (random(2))
                        {
                                message_vision("$N" HIC "惊恐万分，已经毫无招架之力，突然全身一道青光笼罩，其"
                                                   "身穿的【鸿钧套装】将所有伤害全部抵御！\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "惊恐万分，已经毫无招架之力，数道银针穿胸而过，"
                                                   "猛然喷出一口鲜血！\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }                       
                }
                else if (tzlv == 4)
                {
                        
                        if (1)
                        {
                                message_vision(HIM "$N" HIM "凝神抵御，一道紫色的光芒缠绕在其周围，【造化套装】"
                                                    "叮叮作响，竟将所有伤害化解于无形！\n" NOR, obs[i]);
                        }
                        else
                        {
                                //obs[i]->set("last_damage_from", this_object());
                                //obs[i]->receive_wound("qi", obs[i]->query("max_qi")/10*3, this_object());
                                message_vision("$N" HIY "拼死抵抗，却仍然有一道银光穿身而过，造化套装的紫色光芒大"
                                               "现，竟化解了银针的伤害。\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }
                }
        }
}

void heart_beat()
{
        object ob;
        
        keep_heart_beat();

        // 解除不能perform yun的限制
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }
/*
        // 检查武器
        if (! query_temp("weapon"))
        {
                ob = new("/clone/weapon/xuantie-jian");
                ob->move(this_object());
                "/cmds/std/wield"->main(this_object(), "xuantie-jian");
        }
        */
        if (random(5) == 1)check_weapon();
        
        // 5%的机会全屏攻击，100%命中，伤血及上限80%
        if (random(100) < 5)
        {
                damage_all();
        }
        
        return ::heart_beat();
}

// 检查武器
void check_weapon()
{
        object me, ob;
        
        me = this_object();

        // 同时补充内力
        set("neili", query("max_neili"));

        if (me->is_busy())me->interrupt_busy(me, 1000); 

        if (me->is_busy())me->interrupt_me(me);

        if( !query_temp("weapon", me) )
        {
                ob = new("/kungfu/class/riyue/dongfang/zhen");
                ob->move(me);
                "/cmds/std/wield"->main(me, "zhen");
        }
/*
        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);
                
                addn_temp("apply/damage", 50000, me);
                if (random(10) == 1)
                        command("perform sword.tian twice");
                else            
                        command("perform sword.po and finger.tian");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }
*/
        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢复气血
        if (random(800) == 1)
        {
                //log_file("qilin", ctime(time()) + " 成功恢复气血。\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        if (me->is_busy())me->interrupt_busy(me); 

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun roar");
        }

        return;
}

void init()
{
        object me;

        me = this_player();
        
        set("env/combatd", 4, me);
        //if (! wizardp(me))this_object()->kill_ob(me);
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void new_life()
{
        object me = this_object();
        
        // 补满气血
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);

        me->clear_condition();

        me->interrupt_me(this_object());

        delete_temp("no_perform", me);
        delete_temp("no_exert", me);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/qy", 70);  // 气运
        set_temp("apply/fy", 70);  // 福缘              
        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "尖叫一声，目光顿时充满杀意！\n\n" NOR, me);
        
        return; 
}

int receive_damage(string type, int damage, object who)
{
        object ob;
        int tzlv;
        
        object me = this_object();
        
        
        // 套装的追加伤害
        if (objectp(who))
        {
                tzlv = 1;
                
                if (tzlv == 3)// 
                {
                        damage *= 2;
                        this_object()->start_busy(5+random(6));
                        tell_object(HIM "「鸿钧套装」追加伤害及附加忙乱！\n" NOR);
                }
                else if (tzlv == 4)
                {
                        damage *= 3;
                        start_busy(5+random(6));
                        tell_object(HIM "「造化套装」追加伤害及附加忙乱！\n" NOR);
                        if (random(10) < 7)
                        {
                                set_temp("no_perform", 1);
                                call_out("remove_no_perform", 10);
                                tell_object(HIC "「造化套装」追加封招10秒！\n" NOR);
                        }
                }
        }
        
        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}


void remove_no_perform()
{
        delete_temp("no_perform");
}

// 检查生命
void check_life()
{
        object env;
        
        // 如果life<=1则死亡
        if (1)
        {
                message_vision(HIR "\n$N" HIR "悲凉尖啸：莲亭，我去也 ……\n" NOR, this_object());
                // 记录
                log_file("dongfang_die", "东方不败于 " + ctime(time()) + " 被杀死！\n");

                destruct(this_object());
        }
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
        object ob;
        int mar;                //  需要瓜分的体会
        int i;

        // 定义奖励物品列表
        // 几率  X / 百分之
        mixed oblist = ([
                "/clone/fam/super/dugu/bldan"        : 1,
                "/clone/fam/super/dugu/bhxdan"        : 1,
                "/clone/fam/super/dugu/bjxcao"        : 1,
                "/clone/fam/super/dugu/hlzhi"        : 1,
                "/clone/fam/super/dugu/jzdan"        : 1,
                "/clone/fam/super/dugu/qhcao"        : 1,
                "/clone/fam/super/dugu/qhdan"        : 1,
                "/clone/fam/super/dugu/sxguo"        : 1,
                "/clone/fam/super/dugu/tldan"        : 1,
                "/clone/fam/super/dugu/xhcao"        : 1,
                "/clone/fam/super/dugu/xmgu"        : 1,
                "/clone/fam/super/dugu/qlndan"        : 1,
        ]);

        object gift_ob, gift_ob2, gift_ob3, gift_ob4;
        string s_gift, *key_s_gift;
        int gift_point, ran;
                              
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) { 
                full_self(); 
                return; 
        }

        // 如果还未重生，则重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        // 打败我的
        if (! objectp(dob))dob = query_defeated_by();

        if (! objectp(dob))
        {
                // 调用生命检查函数
                check_life();
                return;
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))                                                              
        {
                exp = 40000 + random(40000);
                pot = 40000 + random(40000);
                weiwang = 6000 + random(9000);
                score = 6000 + random(6000);
                mar = 12000 + random(12000);
                n = 0;
                
                n = sizeof(t);
                if (! n || n < 3)                                                                                                        
                {
                       exp /= 5;                                                                                                         
                       pot /= 5;                                                                                                         
                       weiwang /= 3;
                       score /= 3;
                       mar /= 5;
                }

                if (n >= 3)
                {
                        exp /= n;
                        pot /= n;
                        weiwang /= n;
                        score /= n;
                        mar /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {       
                                        // 会员奖励再提高10%
                                        if( MEMBER_D->is_valib_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + exp * 1 / 10 + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + pot * 1 / 10 / 10 + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + weiwang * 1 / 10 + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + score * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的队伍杀死" + name() + HIG "之后"]), 100);          
                                        }
                                        else
                                        {                  
                                                if (environment(tob) == environment(dob))                                  
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的队伍杀死" + name() + HIG "之后"]), 100);  
                                        }
                                }
                        }
                }
                else
                {
                        if( MEMBER_D->is_valib_member(query("id", dob)) )
                        {
                                GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,                                           
                                           "pot"      : pot + pot * 3 / 10,                                       
                                           "weiwang"  : weiwang + weiwang * 3 / 10,                               
                                           "score"    : score + score * 3 / 10,  
                                           "mar"      : mar + mar * 3 / 10,                           
                                           "prompt"   : "你在战胜" + name() + HIG "之后"]), 100);                                    
                        }                                                                                          

                        else
                        {
                                GIFT_D->delay_bonus(dob,                                              
                                        ([ "exp"      : exp,                                           
                                           "pot"      : pot,                                       
                                           "weiwang"  : weiwang,                               
                                           "score"    : score,  
                                           "mar"      : mar,                           
                                           "prompt"   : "你在战胜" + name() + HIG "之后"]), 100); 
                       }     
                }                                                                                                                                                                                                                                                 
        }

        // 100%掉物品
        if (1)
        {
                /*
                key_s_gift = keys(oblist);

                // 100%至少爆一件
                if (1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob);
                                set("who_get/time", time()+30, gift_ob);//30秒内都不能捡取
                                gift_ob->move(environment(this_object()));                                                                           
                        }
                        else // 纪录之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
                
                // 30%几率再追加一件物品
                if (random(10) < 3)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob2 = new(s_gift);
                        if (objectp(gift_ob2))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob2->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob2);
                                set("who_get/time", time()+10, gift_ob2);//30秒内都不能捡取
                                gift_ob2->move(environment(this_object()));                                                                           
                        }
                        else // 纪录之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }                       
                }
                // 10%几率再追加一件
                if (random(10) == 1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob3 = new(s_gift);
                        if (objectp(gift_ob3))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob3->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                //gift_ob3->set("who_get/id", "NONE");
                                //gift_ob3->set("who_get/time", time() + 30); // 30秒内都不能捡取
                                gift_ob3->move(environment(this_object()));                                                                           
                        }
                        else // 纪录之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
*/
                // 40%的几率掉东西
                if (random(100) < 40) 
                {
                        ran = random(100);

                        if (random(10) == 1)// 10%蝉翼披风
                        {
                                gift_ob = new("/clone/armor/dongfang/chanyi");
                                
                                if (objectp(gift_ob))
                                {
                                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob);
                                        set("who_get/time", time()+30, gift_ob);//30秒内都不能捡取
                                        gift_ob->move(environment(this_object()));                                                                           
                                }
                        }
                        
                        if (random(100) < 3)// 黑玉指环 3%
                        {
                                gift_ob2 = new("/clone/armor/dongfang/heiyu");
                                
                                if (objectp(gift_ob2))
                                {
                                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob2->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob2);
                                        set("who_get/time", time()+30, gift_ob2);//30秒内都不能捡取
                                        gift_ob2->move(environment(this_object()));                                                                           
                                }
                        }                       

                        if (random(100) < 3)// 紫血环
                        {
                                gift_ob3 = new("/clone/armor/dongfang/zixue");
                                
                                if (objectp(gift_ob3))
                                {
                                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob3->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob3);
                                        set("who_get/time", time()+30, gift_ob3);//30秒内都不能捡取
                                        gift_ob3->move(environment(this_object()));                                                                           
                                }
                        }

                        if (random(100) < 5)// 魅影剑法或天擎秘气 5% 随机一件
                        {
                                switch(random(3))
                                {
                                        case 0:
                                                gift_ob4 = new("/clone/book/meiying-jian1");
                                        break;
                                        
                                        case 1:
                                                gift_ob4 = new("/clone/book/meiying-jian2");
                                        break;
                                        
                                        default:
                                                gift_ob4 = new("/clone/book/tianqing-miqi");
                                        break;
                                }

                                if (objectp(gift_ob4))
                                {
                                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob4->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob4);
                                        set("who_get/time", time()+30, gift_ob4);//30秒内都不能捡取
                                        gift_ob4->move(environment(this_object()));                                                                           
                                }
                        }
                }
        }
        
        // 5/100几率掉出无名铜人
        if (random(100) < (5+5*query_temp("apply/magic_find", dob)/100))
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren"+(1+random(2)));                     
                message_vision(HIR "当~~一声，从$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time()+30, ob_tongren);//30秒内都不能捡取
                ob_tongren->move(environment(this_object()));
        }
                
        // 特殊活动爆物品，统一调用giftd接口
        GIFT_D->fuben_boss_gift(this_object()); 
                                
/*
        // 20%几率掉出特殊物品
        // 同时有50%几率掉出2件
        if (random(10) < 2)
        {       
                gift_huoyan = new(huoyan);
                set("who_get/id", "NONE", gift_huoyan);
                set("who_get/time", time()+30, gift_huoyan);//30秒内都不能捡取
                gift_huoyan->move(environment(this_object()));  
                message_vision(HIW "叮~~一声，从$N" HIW "身上掉出" + gift_huoyan->name() + 
                               HIW "，落在地上。\n" NOR, this_object());

                //log_file("qilin_gift", "火麒麟于 " + ctime(time()) + " 掉出火眼之戒。\n");
        }
*/
        // 检查生命
        check_life();

        return ;
}  
