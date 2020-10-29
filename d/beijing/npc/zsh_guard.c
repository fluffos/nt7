//zsh_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_zsh(object me, object ob); 
void create() 
{ 
     set_name("守卫",({"shou wei","guard"}) ); 
     set("long","这是一位长的英姿勃勃的年轻人。\n"); 
     set("title","紫衫会会众"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100); 
     set("inquiry",([ 
          "紫衫会" : (: ask_zsh :), 
     ]) ); 
     setup(); 
     carry_object("/clone/cloth/cloth")->wear();  
     carry_object("/clone/weapon/changjian")->wield();  
} 

int ask_zsh(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "紫衫会" && query("shen", me) >= 0 )
     { 
           tell_object(me,"守卫上上下下看了看你，嗯了一声。\n"); 
           tell_object(me,"守卫对你说道：“想加入紫衫会？当家的在里面，你自己进去吧。”\n"); 
           set_temp("good_zsh", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           command("say 哼！还不快滚？我紫衫会对你这种人是不留情面的！"); 
           return 1; 
     } 

     tell_object(me,"守卫奇怪道：“大家都是会内兄弟，你何出此言啊？”\n"); 
     return 1; 
} 
