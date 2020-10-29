#include <ansi.h>
inherit NPC;
//inherit F_DEALER;

void create()
{
        set_name("伙计", ({ "huo ji", "huo", "ji" }) );
        set("title", HIB"药王谷"NOR+YEL"跑堂"NOR);
        set("gender", "男性" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");

        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        int i=(query("eff_qi", ob)*100)/query("max_qi", ob);

        if( query("family/family_name", ob) == "药王谷"){
                command("say 这位兄弟辛苦了，快请进！\n");
                return 1;}

        if (i<=30) {
                command("wa"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了重伤啊！快请到里面让药王谷医师给你看看吧！\n");
                return 1;}

        if (i<=60) {
                command("look"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你伤得不轻啊！快请到里面疗伤吧！\n");
                return 1;}

        if (i<=90) {
                command("pat"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了点伤！到里面买包药服下就没事了！\n");
                return 1;}

        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}

