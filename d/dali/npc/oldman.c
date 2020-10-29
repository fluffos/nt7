//updated by rama

inherit NPC;
#include <ansi.h>

int ask_xdh(object me, object ob);

void create()
{
        set_name("摆夷老叟",({ "old man", "old", "man" }) ); 
        set("gender", "男性" );
        set("age", 72);
        set("long", 
"一个摆夷老叟大大咧咧地坐在竹篱板舍门口，甩着三四个巴掌大的棕吕树叶，瞧着道
上来来往往的人们，倒也快活自在。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 700);
        set("shen_type", 1);
        set("per", 13);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        set("inquiry",([  
                "小刀会" : (: ask_xdh :),  
                               ]) );  
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_xdh(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "小刀会" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱们小刀会的吧！随我来吧！");
           tell_object(me,HIB"摆夷老叟带你到了后院，移开一块石板，你顺着石阶走了下去。\n"NOR);
           message("vision", me->name() + "带着摆夷老叟急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/dali/xdh_dlfb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 客官，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"摆夷老叟说道：“既然是本帮兄弟，就随我来吧！”\n");
     me->move("/d/dali/xdh_dlfb"); 
     return 1; 
} 
