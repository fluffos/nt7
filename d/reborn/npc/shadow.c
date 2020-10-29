// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIM "幻象" NOR, ({ "shadow" }));
        set("gender", "男性" );
        set("age", 30 + random(30));
        set("long", "如梦如幻无法让人看的清楚的一个人。");
        set("attitude", "friendly");
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 20);

        setup();
}

void init() 
{ 
        object ob, me;
        
        me = this_player();  
        ob = this_object();
         
        ::init(); 
        if (interactive(me) && visible(me) &&  
            ! is_fighting())  
        { 
                ob->set_name((query("name", me)+"--幻"),({(query("id", me)+"-shadow")}));
                NPC_D->copy_from_me(ob, me, 120); 
                kill_ob(me); 
        } 
} 
