#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW "冰" HIR "火" HIC"守护神" NOR, ({ "binghuo shouhushen", "binghuo", "shouhushen" }));
        set("title", HIB "暗夜流星" NOR); 
        set("long", HIC "传说他就是冰火岛的守护神，在这里已经守护了千万年。\n" NOR);

        set("gender", "男性");
        set("age", 9999);

        set("str", 9999);
        set("int", 9999);
        set("con", 9999);
        set("dex", 9999);

        set("shen", 8000000);

        set_temp("apply/attack", 5000000);
        set_temp("apply/unarmed_damage", 5000000); 
        set_temp("apply/damage", 5000000); 
        set_temp("apply/armor", 200000);
        set_temp("apply/qy", 80);  // 气运
        set_temp("apply/fy", 80);  // 福缘      

        set("scborn/ok", 1);

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
        set("jiali", 20000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 9999);
        set_skill("finger", 9999);
        set_skill("claw", 9999);
        set_skill("strike", 9999);
        set_skill("hand", 9999);
        set_skill("cuff", 9999);
        set_skill("parry", 9999);
        set_skill("dodge", 9999);
        set_skill("force", 9999);
        set_skill("sword", 9999);
        set_skill("blade", 9999);
        set_skill("zuoyou-hubo", 9999);

        set_skill("daojian-guizhen", 9999);
        set_skill("jiuyang-shengong", 9999);
        set_skill("yinyang-shiertian", 9999);
        set_skill("qiankun-danuoyi", 9999);
        set_skill("martial-cognize", 9999);
        set_skill("qiankun-danuoyi", 9999);
        set_skill("lingbo-weibu", 9999);
        set_skill("literate", 9999);
        set_skill("huajia-su", 1000);

        set_skill("jingluo-xue", 9999);

        set("no_nuoyi", 1); // 不被挪移影响

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

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              // 
              (: command("perform sword.ben twice") :), 
              (: command("perform sword.ben and sword.tian") :),
              // 阴阳12t
              (: command("perform finger.tian twice") :), 
              (: command("perform finger.zhen and finger.jiu") :), 

              //(: exert_function, "roar" :),
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :), 

        }));

        set("my_life", 1); // 当气血低于10%的时候补满一次，设置该参数为0

        setup();

        // 衣服
        carry_object("/clone/cloth/bupao")->wear();

        // 武器
        carry_object("/clone/weapon/huoyun-dao")->wield();
}

void heart_beat()
{
        object ob;
        
        keep_heart_beat();
        if( !environment(this_object()) ) return;

        // 解除不能perform yun的限制
        if (random(10) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }

        return ::heart_beat();
}

void init()
{
        object me;

        me = this_player();
        
        set("env/combatd", 4, me);
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

        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000); 
        set_temp("apply/damage", 150000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/qy", 70);  // 气运
        set_temp("apply/fy", 70);  // 福缘      
        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "大喝一声，目光顿时充满杀意！\n\n" NOR, me);
        
        return; 
}

void unconcious()
{
        object ob;
        
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        die(query_last_damage_from());
}

void die(object killer)
{                                                                                                   
        object ob;
        
        if( objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        // 如果还未重生，则重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }


        // 不给予奖励
        ::die(killer);
        return;
}  
