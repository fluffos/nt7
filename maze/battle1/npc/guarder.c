
#include <ansi.h>

#define MAX_SKILL 700

inherit NPC;

void create()
{
        set_name(HIY "守护者" NOR, ({ "guarder",}));
        set("title", HIR "" NOR);
        set("gender", "男性");
        set("age", 22+random(23));
        set("long", @LONG
他带着一副冰冷的面具，无法辨识模样。
LONG);
        set("attitude", "friendly");
        set("str", 80);
        set("int", 80);
        set("con", 80);
        set("dex", 80);
        set("per", 1);
        set("shen_type", 0);

        set("qi", 50000000);
        set("max_qi", 50000000);

        set("jing", 920000000);
        set("max_jing", 920000000);
        set("jingli", 92000000); 
        set("max_jingli", 92000000); 

        set("neili", 400000); 
        set("max_neili", 400000); 
        set("jiali", 4000); 
        set("combat_exp", 2000000000);

        set("scborn/ok", 1);
        set("special_skill/guimai", 1);
        
        set_skill("force", MAX_SKILL);
        set_skill("pixie-jian", MAX_SKILL);
        set_skill("surge-force", MAX_SKILL);
        set_skill("six-finger", MAX_SKILL);
        set_skill("sword", MAX_SKILL);
        set_skill("finger", MAX_SKILL);
        set_skill("whip", MAX_SKILL);
        set_skill("dodge", MAX_SKILL);
        set_skill("parry", MAX_SKILL);
        set_skill("unarmed", MAX_SKILL);
        set_skill("strike", MAX_SKILL);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", MAX_SKILL);
        set_skill("throwing", MAX_SKILL);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", MAX_SKILL);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "six-finger");

        set_temp("apply/attack",100000);
        set_temp("apply/defense", MAX_SKILL * 10);
        set_temp("apply/damage", MAX_SKILL * 5);
        set_temp("apply/unarmed_damage", MAX_SKILL * 5);
        set_temp("apply/armor", MAX_SKILL * 10);
        set_temp("apply/fy", 80);
        set_temp("apply/qy", 80);

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
}

void heart_beat()
{
        object env;
        if (query("neili") < 1 && random(50) == 1)                                              
                set("neili", query("max_neili"));

        // 守护房间出口
        env = environment(this_object());
        if (objectp(env))
        {
                if (query_temp("guardfor") != env->query("guard_dir"))
                        command("guard " + env->query("guard_dir"));
        }
        
        return ::heart_beat();
}

varargs void die(object killer)
{
        object me;
        int i;

        me = this_object();

        if( !killer ) killer = me->query_last_damage_from();
        if( objectp(killer) &&
            userp(killer) &&
            query_temp("battle/team_name", killer) != query_temp("battle/team_name", me) )
        {
                BATTLEFIELD_D->add_killnpc_score(killer, 1);
        }

        ::die(killer);
}

void unconcious()
{
        die(query_last_damage_from());
}
