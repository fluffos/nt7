#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "谢逊" NOR, ({"xie xun", "xie", "xun", }));
        set("title", HIR "发狂的金毛狮王" NOR);
        set("long",
        "他是一位身材魁伟异常的的老者，身穿一件白布长袍。\n"
        "他满头黄发，威风凛凛，真如天神一般，只是两只眼睛并不睁开。\n"
        );

        set("gender", "男性");
        set("attitude", "peaceful");

        set("age", 61);
        set("shen_type", 1);
        set("per", 30);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 2000000000);
        set("max_jing", 1000000000);
        set("max_jingli", 1000000000);
        set("jingli", 1000000000);
        set("neili", 3000000);
        set("max_neili", 3000000);
        set("jiali", 10000);

        set("combat_exp", 2000000000);
        set("score", 800000);
        
        set("no_nuoyi", 1);
        set("scborn/ok", 1);

        set_skill("force", 4000);
        set_skill("dodge", 4000); 
        set_skill("parry", 4000);
        set_skill("hand", 4000);
        set_skill("cuff", 4000);
        set_skill("sword", 4000);
        set_skill("shenghuo-xinfa", 4000);
        set_skill("shenghuo-bu", 4000);
        set_skill("pili-shou", 4000);
        set_skill("pili-quan", 4000);
        set_skill("qishang-quan", 4000);
        set_skill("literate", 4000);
        set_skill("martial-cognize", 4000);
        set_skill("zuoyou-hubo", 2500);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("hand", "pili-shou");
        map_skill("parry", "qishang-quan");
        map_skill("cuff", "qishang-quan");

        prepare_skill("cuff", "qishang-quan");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform cuff.shang twice") :),
                (: command("perform cuff.fei twice") :),
        }) );
        create_family("明教", 36, "弟子");

        set_temp("apply/attack", 500000);
        set_temp("apply/unarmed_damage", 50000); 
        set_temp("apply/damage", 50000); 
        set_temp("apply/armor", 50000);
        set_temp("apply/qy", 80);  // 气运
        set_temp("apply/fy", 80);  // 福缘
        
        setup();
        carry_object("/d/mingjiao/obj/baipao")->wear();
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

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)                                              
                set("neili", query("max_neili"));
        
        // 如果不在帮战期间则消失
        if (! BUNCH_D->is_battle_start() )destruct(this_object());

        ::heart_beat();
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
        object dob;             // 打晕这个NPC的人
        object env;
        object ob;
        
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        // 如果杀我的人属于某帮派则设置该帮派具有抢先进入密道
        if (dob && userp(dob))
        {
                if (! objectp(env = find_object("/maze/binghuodao/jitan")))
                        env = load_object("/maze/binghuodao/jitan");

                if( env && sizeof(query("bunch/bunch_name", dob)) )
                {
                        env->set_flag(query("bunch/bunch_name", dob));
                }
        }

        message_vision(HIY "$N" HIY "大叫道：“贼老天，贼老天啊，为何这样对我！”\n" NOR, 
                       this_object());

        destruct(this_object());
        
        return;
}
