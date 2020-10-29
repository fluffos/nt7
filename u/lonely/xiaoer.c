#include <ansi.h>
#include <command.h>

inherit NPC;

void greeting(object ob);
void remove_ct(object ob);

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "这位店小二正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        setup();
        if (clonep()) keep_heart_beat();
}

string accept_ask(object me, string topic)
{
        switch (random(5))
        {
        case 0:
                return "嗨！我忙着呢，你和我那醉仙楼做活的兄弟聊聊吧！";

        case 1:
                return "你干啥？没看我忙着呢么？";

        case 2:
                return "哎呀呀，你没看我忙着呢么，要打听消息你去找我醉仙楼做活的兄弟吧？";

        case 3:
                return "春来茶馆的老板娘阿庆嫂消息也灵通，那些爷们什么都告诉她，要不你问她去？";

        default:
               return "我那醉仙楼做活的兄弟消息才叫灵通，你去和他聊吧。";
        }
}

void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 5, ob);
                call_out("remove_ct", 3, ob);
        }
}

void remove_ct(object ob)
{
        remove_call_out("greeting");
}

void greeting(object ob)
{
        if ( ! ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
        case 0:
                say( CYN "店小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                   + CYN + "，进来喝杯茶，歇歇腿吧。\n" NOR);
                break;
        case 1:
                say( CYN "店小二用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                   + CYN + "，请进请进。\n" NOR);
                break;
        }
}


