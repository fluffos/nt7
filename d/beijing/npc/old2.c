//keeper.c
//updated by rama

inherit BUNCHER;
#include <ansi.h>

int ask_hbd(object me, object ob);

void create()
{
        set_name("老汉", ({ "old man", "old", "man" }) );
        set("gender", "男性" );
        set("age", 63);
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");
        set("inquiry",([  
                "黑白道" : (: ask_hbd :),  
                               ]) );  
        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
}

int ask_hbd(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "黑白道" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱们黑白道的吧！随我来吧！");
           tell_object(me,HIB"老汉带你到了后院，移开一块石板，你顺着石阶走了下去。\n"NOR);
           message("vision", me->name() + "带着老汉急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/beijing/hbd_bjzb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 客官，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"老汉说道：“既然是本帮兄弟，就随我来吧！”\n");
     me->move("/d/beijing/hbd_bjzb"); 
     return 1; 
} 
