// /clone/quest/bwdhnpc.c
// Modified by sir 2004-01-20

#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;

void create()
{        
        set_name("弟子",({ "di zi" }) );
        set("gender", random(2)>0 ? "女性" : "男性" );
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );                     
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
        carry_object("/clone/food/jiudai");
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        if( query("no_fight", find_object(dest)))return 0;
        if( this_object()->is_fighting() ) return 0;
        command("go " + dir);
        return 1;
}

void init()
{        
        object ob;
        if ( interactive(ob=this_player())) {
                        remove_call_out("killing");
                        call_out("killing", 0, ob);
                }
         add_action("do_hit","hit");
         add_action("do_hit","kill");         
         add_action("do_hit","touxi");
         add_action("do_hit","ansuan");
         add_action("do_hit","steal");                  
}

void killing(object ob)
{        
        message_vision("$N对著$n喝道：「"+RANK_D->query_rude(ob)+"！今天不是你死就是我亡！」\n",this_object(),ob);
        this_object()->kill_ob(ob);        
        return;
}

int do_hit(string arg)
{
        object ob = this_object(), me = this_player();
        mapping map_status;
        string*        mname;
        int i,j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});
        if( !arg || (arg != query("id", ob)) )
                return 0;
        if ( mapp(map_status = ob->query_skill_map()) ) 
           {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) 
                        {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set("chat_chance_combat", 40, ob);
                set("chat_msg_combat", combat_actions, ob);
               if( query("combat_exp", me)>query("combat_exp", ob) )
                
               set("combat_exp",query("combat_exp",  me), ob);
               ob->fight_ob(me); 

}
void die()
{
        object ob = this_object();
        object me,fme;
        int pot,exp,level,score;
        me=query_temp("last_damage_from", ob);
        fme=query_temp("last_opponent", ob);
        if( fme && query("id", me) == query("id", fme) )
        {         
         pot = 300 + random(100);
         exp = 800 + random(300);
         score = 300 + random(100);
         addn("combat_exp", exp, me);
         addn("potential", pot, me);
         addn("score", score, me);
         addn_temp("bwdh_nknum", 1, me);
        message_vision("$N对着你恨恨的说：“明年此时再来领教阁下高招！”\n",ob);
        tell_object(me,HIW"你在论剑中战胜对手，得到如下奖励：\n");
        tell_object(me,chinese_number(exp) +"点实战经验\n" +
        chinese_number(pot) + "点潜能。\n"NOR);
       } 
       destruct ( ob );
//        ::die();    
}