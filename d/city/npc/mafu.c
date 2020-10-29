// mafu.c 马夫

inherit NPC;
#include <ansi.h>
int do_ride();

void create()
{
        set_name("马夫", ({ "ma fu", "mafu", "ma" }));
        set("age", 32);
        set("gender", "男性");
        set("long","驯马和租马的小贩，给他租金就可以雇到马。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 50000);
        set("shen_type", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/armor", 30);
        set("chat_chance",2);
        setup();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
               remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_ridebj", "ridebj");
        add_action("do_ridesz", "ridesz");
        add_action("do_ridehz", "ridehz");
        add_action("do_ridefz", "ridefz");
        add_action("do_ridedl", "ridedl");
        add_action("do_rideyd", "rideyd");
        add_action("do_rideyl", "rideyl");
        add_action("do_ridefs", "ridefs");
        add_action("do_rideem", "rideem");
        add_action("do_ridexy", "ridexy");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say( "马夫点头哈腰地说道：这位客官，是想到这里挑一匹好马吧？\n");
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( query("money_id", ob) && ob->value() >= 100 )
        {
        message_vision("马夫对$N说：好！这位"+RANK_D->query_respect(who) +
                "现在就出发马? 那就上马吧。\n", who);
                set_temp("marks/horserent", 1, this_player());
                       return 1;
        }
        else  
                message_vision("马夫皱眉对$N说：您给的也太少了吧？\n", who);
        return 1;
}

#include "mafubj.h"
#include "mafusz.h"
#include "mafuhz.h"
#include "mafufz.h"
#include "mafufs.h"
#include "mafudl.h"
#include "mafuyd.h"
#include "mafuyl.h"
#include "mafuem.h"
#include "mafuxy.h"