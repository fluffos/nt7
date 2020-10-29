 
// killer.c
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("蒙面人", ({ "figure" }) );
        set("long",
"这个人头上戴著蒙面头罩，八成准备干什麽坏事。\n");
        set("attitude", "heroism");
        set("hired_killer", 1);
        set("age",random(10)+30);
        set("max_qi",1500);
        set_skill("dodge",90);
        set_skill("sword",90);
        set_skill("taiji-jian",90);
        map_skill("sword","taiji-jian");
        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :),
        }));
        set("combat_exp",50000+random(50000));
        setup();
        carry_object("/d/chengdu/npc//obj/brown-cloth");
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
          call_out("move_killer", 900);
          call_out("learn_skill",1);
          add_action("do_arrest","arrest");
}
void learn_skill()
{
        object ob, me;
        mapping skill_status, map_status, hp_status;
        string *sname, *mname;
        int i;

        me = this_object();
        ob = this_player();
        if (me->is_fighting() || wizardp(ob)) return;

        remove_call_out("learn_skill");

        me->map_skill("unarmed");
        me->map_skill("dodge");
        me->map_skill("parry");

        if ( !(skill_status = ob->query_skills()) ) return;
        sname  = keys(skill_status);

        for(i=0; i<sizeof(skill_status); i++) {
                me->set_skill(sname[i], skill_status[sname[i]]);
        }

        if ( !(map_status = ob->query_skill_map()) ) return;
        mname  = keys(map_status);

        for(i=0; i<sizeof(map_status); i++) {
                me->map_skill(mname[i], map_status[mname[i]]);
        }
       hp_status = ob->query_entire_dbase();
       call_out("learn_skill", 3);
}
int do_arrest(string arg)
{
   mapping job;
   object ob = this_player();
   object who;
   job=query("job", ob);
   if( !job || job["job_type"] != "抓")
     return notify_fail("你不是官差，不能抓差办案！\n");
   if(!arg)
   return notify_fail("你想抓谁？\n");
   if(!objectp(who = present(arg, environment(ob))))
   return notify_fail("这里没有你想抓的人。\n");
   message_vision("$N拿起一条铁链子，抖动着...\n",ob); 
   message_vision("对着$N大声喝道：“大胆贼人，看你往哪里逃！拿命来吧！”\n",this_object());
   set_temp("arrest", 1, ob);
   this_object()->kill_ob(ob);
   return 1;
} 

void move_killer()
{
    message_vision("$N匆匆离去了。\n",this_object());
    destruct(this_object());
    return ;
}
void unconcious()
{
     object killer;
     killer = query_temp("last_damage_from");
     if( query_temp("arrest", killer) )
     set("end_job",query("id", killer));
     remove_call_out("learn_skill");
     ::unconcious();
     return ;
}
