#include <ansi.h>
//inherit NPC;
inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("伙计", ({ "huo ji", "huo", "ji" }) );
        set("title", HIB"药王谷"NOR+YEL"跑堂"NOR);
        set("gender", "男性" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("vendor_goods", ({
//         "/d/bianliang/npc/obj/san",         
//         "/d/bianliang/npc/obj/gao1",         
//         "/d/bianliang/npc/obj/jinlidan",         
           "/clone/fam/pill/water",         
           "/clone/fam/pill/food",      
         }));

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
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

int greeting(object ob)
{
        if( query("family/family_name", ob) == "药王谷"){
                command("say 这位兄弟请了！\n");
                return 1;}
        else {
        switch( random(4) ) 
        {
                case 0:
                        command("bow"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
                        break;
        }
        }
}

