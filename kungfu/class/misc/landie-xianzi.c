#include <ansi.h>

inherit NPC;

string lookdesc = "她一身清淡白衣，如风拂玉树，雪裹琼苞，兼之生性清冷，真乃仙子。\n";

void create()
{
        set_name(HIM "蓝蝶仙子" NOR, ({ "landie xianzi", "landie", "xianzi"}));
        set("title", HIC "崆峒仙境" NOR);
        set("gender", "女性");
        set("age", 22);
        set("long", lookdesc); // 初始化时会重新设置lookdesc可以显示那个玩家能够对我造成伤害
        set("attitude", "friendly");
        set("str", 21);
        set("int", 40);
        set("con", 45);
        set("dex", 46);
        set("per", 30);
        set("shen_type", 1);
        set("scborn/ok", 1);
        set("no_nuoyi", 1); // 不被挪移影响
        set("qi", 5000000);
        set("max_qi", 5000000);

        set("jing", 2000000);
        set("max_jing", 2000000);
        set("jingli", 2000000); 
        set("max_jingli", 2000000); 

        set("neili", 30000); 
        set("max_neili", 30000); 
        set("jiali", 600); 
        set("combat_exp", 8000000);

        set_skill("force", 1500);
        set_skill("suxin-jue", 1500);
        set_skill("yunv-xinjing", 1500);
        set_skill("sword", 1500);
        set_skill("yunv-jian", 1500);
        set_skill("suxin-jian", 1500);
        set_skill("quanzhen-jian", 1500);
        set_skill("whip", 1500);
        set_skill("yinsuo-jinling", 1500);
        set_skill("dodge", 1500);
        set_skill("yunv-shenfa", 1500);
        set_skill("parry", 1500);
        set_skill("unarmed", 1500);
        set_skill("meinv-quan", 1500);
        set_skill("strike", 1500);
        set_skill("tianluo-diwang", 1500);
        set_skill("zuoyou-hubo", 1500);
        set_skill("literate", 1500);
        set_skill("throwing", 1500);
        set_skill("yufeng-zhen", 1500);
        set_skill("martial-cognize", 1500);

        map_skill("force", "yunv-xinjing");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "suxin-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        set_temp("apply/attack", 1500);
        set_temp("apply/defense", 1500);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.wang and unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "whip.feng twice" :),
        }) );

        set("jianling-summon",1); // 不会被剑灵DAMAGE_ALL伤害
        
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
}

// 初始化
void init_me(object jianling, object wanjia)
{
        set("jianling", jianling);
        set("mytarget", wanjia);
        set("env", environment(jianling));
        
        set("long", lookdesc + HIR "目前只有" + HIY + wanjia->name() +  HIR "能够对其造成伤害！\n");
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
        ob->start_busy(12 + random(12));
        me->receive_wound("qi", 200000 + random(90000), ob);
        return HIY "$N" HIY "娇喝一声，奋力攻击，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}


int receive_damage(string type, int damage, object who)
{
        // 只有指定目标才能对我造成伤害
        if (! who)return 0;
        
        if ( who != query("mytarget"))
        {
                message_vision(HIG "$N" HIG "看透了$n" HIG "的攻势，竟丝毫无伤！\n" NOR, this_object(), who);
                return 0;
        }
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)                                              
                set("neili", query("max_neili"));

        if (environment(this_object()) != query("env"))
        {
                if (objectp(query("env")))this_object()->move(query("env"));
        }
        
        return ::heart_beat();
}

void unconcious()
{
        // 防止直接call_die()
        if (query("qi") > 60000)
        {
                revive();
                return;
        }
        die(query_last_damage_from());
}

void die(object killer)
{

        message_vision(HIC "只见一道光芒从$N" HIC "体内升起，$N" HIC "竟化作一缕蓝蝶飞走了！\n" NOR, this_object());
                                        
        command("chat* tlbb " + query("id"));                           
        destruct(this_object());
        
        return;
}

void remove()
{
        object dob;
        
        dob = query("jianling");// 获取对应的剑灵OB
        
        if (! objectp(dob))return;
        
        delete("mylandie", dob);//通知剑灵，蓝蝶消失了
        set("last_summon_landie", time(), dob);//通知剑灵，蓝蝶消失时间
        
        return;
}
