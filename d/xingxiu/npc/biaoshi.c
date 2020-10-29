// Last Modified by Lonely on Apr. 25 2001

#include <ansi.h>
inherit NPC;

int do_copy(object me);
int do_back(object me);

void create()
{
        string weapon;
        set_name("护镖镖师", ({ "hubiao biaoshi", "biaoshi"}));
        set("gender", "男性");
        set("age", random(10) + 25);
        set("no_quest", 1);
        seteuid(getuid());
        set("str", 33);
        set("con", 26);
        set("int", 20);
        set("dex", 23);
        set("long", "镖局的镖师。\n");
        set("combat_exp", 80000 + random(40000)); 
        set("attitude", "friendly");
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("cuff", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("taiji-jian", 50);
        set_skill("changquan", 50); 
        set_skill("tiyunzong", 50);
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");       
        map_skill("cuff", "changquan"); 
        prepare_skill("cuff", "changquan"); 
        prepare_skill("cuff", "taizu-quan");         
        set("max_qi", 450); 
        set("eff_jingli", 400); 
        set("neili", 700); 
        set("max_neili", 700);
        set("jiali", 30);
        setup();
        carry_object("clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/junfu")->wear();
}

int do_back(object me)
{                       
        tell_room(environment(me),query("name", me)+"跳出战圈，转身几个起落就不见了。\n",({me}));
        destruct(me); 
        return 1;
}
void unconcious()
{            
        do_back(this_object());       
}
void die(){ do_back(this_object()); }

int checking(object ob, object me)
{
        if(!me || !present(me, environment())) do_back(ob);
        else call_out("checking", 2, ob, me);
        return 1;
}

int do_copy(object me)
{
        int i;
        object ob;
        ob = this_object();

        if( !query_temp("xx_rob", me) )
        {
                do_back(me);
                return 0;
        }
        i = me->query_skill("dodge",1);
        i = (i + random(i))/2;
        if( i < 60) i = 60;
        
        message_vision(HIR"突然从商队后窜出$N，二话不说就扑向了$n！\n"NOR, ob, me);
        addn_temp("biaoshi", 1, me);
        set("combat_exp", query("combat_exp",me)/2+random(query("combat_exp",me))/2,ob); 
        ob->set_skill("force", i);
        ob->set_skill("sword", i);
        ob->set_skill("cuff", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
        ob->set_skill("taiji-jian", i);
        ob->set_skill("changquan", i); 
        ob->set_skill("tiyunzong", i);
        ob->map_skill("dodge", "tiyunzong");
        ob->map_skill("parry", "taiji-jian");
        ob->map_skill("sword", "taiji-jian");       
        ob->map_skill("cuff", "changquan"); 
        ob->prepare_skill("cuff", "changquan"); 
        set("max_qi", 1000+query("max_qi", me)/2, ob);
        set("eff_jing", 1000+query("eff_jing", me)/2, ob);
        set("max_neili", 1000+query("max_neili", me)/2, ob);
        set("jiali",query("jiali",  me)+20, ob);
        ob->reincarnate(); 
        set("target", me, ob);
        ob->kill_ob(me);
        checking(ob, me);    
        call_out("do_back", 350,  ob);  
        return 1;
}
