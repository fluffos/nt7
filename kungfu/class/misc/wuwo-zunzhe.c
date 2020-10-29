// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 100

inherit NPC;

void create()
{
        set_name(HIY "无我尊者" NOR, ({ "wuwo zunzhe"}) );
        set("title", HIG "忘忧谷主人" NOR);
        set("long", HIR "一位面色和善的尊者，似乎看尽一切尘世凡俗！\n" NOR);

        set("gender", "男性");
        set("age", 49);

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              // 
              (: command("perform sword.ben twice") :), 
              (: command("perform sword.ben and sword.tian") :),
              // 阴阳12t
              (: command("perform finger.tian twice") :), 
              (: command("perform finger.zhen and finger.jiu") :), 

              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
        }));

        setup();

        // 衣服
        carry_object("/clone/cloth/bupao")->wear();
        // 武器
        carry_object("/clone/weapon/fengshen-jian")->wield();

        // 设置地点
        //set("startroom", "/d/shenlong/huodong1");
}


void init_npc(object me)
{
        int max_skill, npc_level, npc_qi;
        int arg, exp, pot, mar;
        
        //me = find_player("rcwiz");

        max_skill = WAR_D->max_skills_level(me);

        
        set("me", me);
        set("combat_exp", me->query("combat_exp"));

        if (max_skill <= 100)
        {
                npc_qi = 3000000;
        }
        else
        if (max_skill <= 200)
        {
                npc_qi = 4000000;
        }
        else
        if (max_skill <= 300)
        {
                npc_qi = 5000000;
        }
        else 
        if (max_skill <= 400)
        {
                npc_qi = 6000000;
        }
        else 
        if (max_skill <= 500)
        {
                npc_qi = 8000000;
        }
        else 
        if (max_skill <= 750)
        {
                npc_qi = 10000000;
        }
        else
        if (max_skill <= 1000)
        {
                npc_qi = 15000000;
        }
        else
        if (max_skill <= 1500)
        {
                npc_qi = 20000000;
        }
        else 
        if (max_skill <= 2000)
        {
                npc_qi = 25000000;
        }
        else 
        if (max_skill <= 2500)
        {
                npc_qi = 30000000;
        }
        else 
        if (max_skill <= 3000)
        {
                npc_qi = 40000000;
        }
        else 
        if (max_skill <= 3500)
        {
                npc_qi = 50000000;
        }
        else 
        if (max_skill <= 4000)
        {
                npc_qi = 60000000; 
        }
        else 
        if (max_skill <= 4500)
        {
                npc_qi = 70000000;
        }
        else 
        if (max_skill <= 5000)
        {
                npc_qi = 80000000;
        }
        else 
        if (max_skill <= 5500)
        {
                npc_qi = 100000000;      // 1E
        }
        else 
        if (max_skill <= 6000)
        {
                npc_qi = 120000000;
        }
        else 
        if (max_skill <= 6500)
        {
                npc_qi = 140000000;
        }
        else 
        if (max_skill <= 7000)
        {
                npc_qi = 160000000;
        }
        else 
        if (max_skill <= 7500)
        {
                npc_qi = 180000000;
        }
        else 
        if (max_skill <= 8000)
        {
                npc_qi = 200000000;
        }
        else
        {
                npc_qi = 250000000; // 2.5E
        }
                        
        // 对NPC_qi修正
        npc_qi -= npc_qi / 2; // 降低50%

        reset_eval_cost();

        set("max_qi", npc_qi);
        set("eff_qi", npc_qi);
        set("qi", npc_qi);

        // 固定值
        set("str",50);
        set("int", 200);
        set("con", 200);
        set("dex", 50);
        set("shen", 0);
        set("scborn/ok", 1);
        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000); 
        set("jingli", 1000000000);  
        set("neili", 10000000);
        set("max_neili", 10000000);
        set("jiali", 1000);
        set("no_nuoyi", 1); // 不被挪移影响
        set_temp("apply/qy", 20);  // 气运
        set_temp("apply/fy", 20);  // 福缘

        npc_level = max_skill; 
        
        // 对npc_level修正 
        npc_level -= npc_level / 5; // 降低20%

        set_skill("unarmed", npc_level);
        set_skill("finger", npc_level);
        set_skill("claw", npc_level);
        set_skill("strike", npc_level);
        set_skill("hand", npc_level);
        set_skill("cuff", npc_level);
        set_skill("parry", npc_level);
        set_skill("dodge", npc_level);
        set_skill("force", npc_level);
        set_skill("sword", npc_level);
        set_skill("blade", npc_level);
        set_skill("zuoyou-hubo", 2500);

        set_skill("daojian-guizhen", npc_level);
        set_skill("jiuyang-shengong", npc_level);
        set_skill("yinyang-shiertian", npc_level);
        set_skill("qiankun-danuoyi", npc_level);
        set_skill("martial-cognize", npc_level);
        set_skill("qiankun-danuoyi", npc_level);
        set_skill("lingbo-weibu", npc_level);
        set_skill("literate", 4000);
        set_skill("daojian-xiaotianwai", 500);
        set_skill("jingluo-xue", npc_level);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "yinyang-shiertian");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "daojian-guizhen");
        map_skill("blade", "daojian-guizhen");

        prepare_skill("finger", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");

        // 奖励
        exp = max_skill * 10;
        pot = max_skill * 20;
        mar = max_skill * 5;

        set("exp", exp);
        set("pot", pot);
        set("mar", mar);

        arg = max_skill / 500;
        if (arg > 10)arg = 10;
        set_temp("apply/attack", max_skill * arg);
        set_temp("apply/unarmed_damage", max_skill * arg);
        set_temp("apply/damage", max_skill * arg); 
        set_temp("apply/armor", max_skill * arg);
}

void init()
{
        object me;

        me = this_player();

        me->set("env/combatd", 4);
        command("bow");
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

void unconcious()
{
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int mar;                //  需要瓜分的体会
        int i;
        object gift_ob, gift_ob2, gift_ob3, ob_tys;
        string s_gift, *key_s_gift;
        int gift_point, ran;

        // 定义奖励物品列表
        // 几率  X / 百分之
        mixed oblist = ([
                "/clone/fam/max/naobaijin"               : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,           
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,           
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,   
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,
                "/clone/fam/pill/sheli4"                 : 1,
                "/clone/fam/pill/puti4"                  : 1,                                                                         
        ]);


        // dob 设置在我身上 init_npc(me)的时候已经设置
        dob = query("me");

        if (! dob)destruct(this_object());
        
        // 防止直接call_die()
        if (query("qi") > 500000)
        {
                revive();
                return;
        }

        if (1)
        {
                exp = query("exp");
                pot = query("pot");
                mar = query("mar");

                if (MEMBER_D->is_valib_member(dob->query("id")))
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp + exp / 10,
                                           "pot"      : pot + pot  / 10,
                                           "mar"      : mar + mar/ 10, 
                                           "prompt"   : "你在战胜" + name() + HIG "之后"]), 999);
                }

                else
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp,
                                           "pot"      : pot,
                                           "mar"      : mar,
                                           "prompt"   : "你在战胜" + name() + HIG "之后"]), 999); 
                }
        }

        // 50%掉物品
        if (random(100) < 25)
        {
                key_s_gift = keys(oblist);

                // 100%至少爆一件
                if (1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + 
                                               gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());
                                gift_ob->set("who_get/id", "NONE");
                                gift_ob->set("who_get/time", time() + 30); // 30秒内都不能捡取
                                gift_ob->move(environment(this_object()));
                        }
                        else // 纪录之
                        {
                                //log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
                
                // 20%几率再追加一件物品
                if (random(10) < 2)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob2 = new(s_gift);
                        if (objectp(gift_ob2))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + 
                                               gift_ob2->name() + HIC "，落在地上。\n" NOR, this_object());
                                gift_ob2->move(environment(this_object()));
                        }
                        else // 纪录之
                        {
                                //log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
        }
        
        // 50%几率掉出铁英石头
        if (random(100) < 25)
        {
                ob_tys = new("/clone/fam/item/tieying-shi");
                ob_tys->set_amount(1 + random(5));
                if (objectp(ob_tys))
                {
                        message_vision(HIG "当~~一声，从$N" HIG "身上掉出" + HIY + 
                                       sprintf("%d", ob_tys->query_amount()) + HIG "块" + 
                                       ob_tys->name() + HIG "，落在地上。\n" NOR, this_object());
                        ob_tys->move(environment(this_object()));
                }
                else // 纪录之
                {
                        log_file("gift-none", "铁英石 from " + __FILE__ + "\n");
                }               
                
        }
        
/*      
        // 5/100几率掉出无名铜人
        if (random(100) < 5)
        {
                object ob_tongren;
                ob_tongren = new("/clone/fam/item/wuming-tongren");
                message_vision(HIR "当~~一声，从$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                ob_tongren->set("who_get/id", "NONE");
== 未完继续 95% == (ENTER 继续下一页，q 离开，b 前一页)
                ob_tongren->set("who_get/time", time() + 30); // 30秒内都不能捡取
                ob_tongren->move(environment(this_object()));
        }
   */
   
        // 为玩家所在帮派累积积分
        BUNCH_D->add_points(dob);
        
        destruct(this_object());
        return ;
}  
