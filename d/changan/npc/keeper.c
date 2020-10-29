//keeper.c
//updated by rama

inherit NPC;
#include <ansi.h>

int ask_hbd(object me, object ob);
void create()
{
        set_name("庙祝", ({ "keeper" }) );
        set("gender", "男性" );
        set("age", 60);
        set("long", "这个老人看起来六十多岁了，精神却很好。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("inquiry",([ 
                      "黑白道" : (: ask_hbd :), 
                 ]) ); 


        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || ! present(ob, environment(this_object()))) 
                return;

        say("庙祝说道：这位" + RANK_D->query_respect(ob) +
            "，捐点香火钱吧。\n");
}
int ask_hbd(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 

     if( query("bunch/bunch_name", me) != "黑白道" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱们黑白道的吧！随我来吧！");
           tell_object(me,HIB"庙祝带你绕到佛像后面，开了一扇小门，你顺着小门走了下去。\n"NOR);
           message("vision", me->name() + "带着庙祝急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/changan/hbd_cafb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 施主，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"庙祝说道：“既然是本帮兄弟，就随我来吧！”\n");
     me->move("/d/changan/hbd_cafb"); 
     return 1; 
} 
