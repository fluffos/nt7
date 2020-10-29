// robber.c
#include <ansi.h>

inherit NPC;
void init();
void create()
{
        set_name(HIR "劫匪" NOR, ({ "biao robber", "robber" }) );
        set("long","这些强盗啸聚山林，专以打劫镖银为生。\n");

        set("attitude", "heroism");

        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                "劫镖强盗喝道：快快跑吧，不然死了都不知道怎么回事！\n",
                "劫镖强盗喝道：老子看你是要钱还是要命！\n"
        }) );

        setup();

        carry_object(__DIR__"obj/gangjian")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

int accept_hit(object ob)
{
        command("say 既然你要下黄泉那我就成全你吧！");
        command("yun powerup");
        kill_ob(ob);
        return 1;
}
int accept_kill(object ob)
{
        command("say 既然你要下黄泉那我就成全你吧！");
        command("yun powerup");
        return 1;
}
void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("checking");
                call_out("checking", 0, ob);
        }
}

void checking()
{
         if (present("biao tou", environment(this_object())))
                 command("kill tou");
         call_out("leave",30);
}
 
void die()
{
        message_vision("$N突然惨叫一声，夺路而逃，转眼就消失了。\n", this_object() );
        destruct(this_object());
}
int leave()
{
        if(!is_fighting() ) {
                message_vision(HIB + "劫匪急急忙忙地走开了。\n" NOR, this_object() );
                destruct(this_object());
        }
        else call_out("leave",30);
}
void invocation(object who)
{
        object ob;
        mapping hp_status, skill_status, map_status;
        string *sname, *mname;
        int i, hp, hp2, temp;
        ob = this_object();

        if ( mapp(skill_status = who->query_skills()) ) {
                skill_status = who->query_skills();
                sname  = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++) 
                        ob->set_skill(sname[i], skill_status[sname[i]]);
        }

        if ( mapp(map_status = who->query_skill_map()) ) {
                mname  = keys(map_status);
                for(i=0; i<sizeof(map_status); i++) 
                        ob->map_skill(mname[i], map_status[mname[i]]);
        }

        hp_status = who->query_entire_dbase();
        hp = who->query("max_qi");
        hp2 = who->query("max_jing");

                ob->set("str", hp_status["str"]);
                ob->set("int", hp_status["int"]);
                ob->set("con", hp_status["con"]);
                ob->set("dex", hp_status["dex"]);
                ob->set("per", hp_status["per"]);

                ob->set("max_qi",hp);
                ob->set("eff_qi",hp);
                ob->set("qi",hp);
                ob->set("max_jing", hp2);
                ob->set("eff_jing",hp2);
                ob->set("jing",hp2);
                ob->set("max_neili", hp_status["max_neili"]);
                ob->set("neili",     hp_status["neili"]);
                ob->set("max_jingli",hp_status["jingli"]);
                ob->set("jingli",    hp_status["jingli"]);
                ob->set("jiali",hp_status["jiali"]);
                ob->set("force_factor",    random(hp_status["force_factor"]));
                ob->set("combat_exp",hp_status["combat_exp"]);
}

