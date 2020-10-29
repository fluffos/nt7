//snowman 28/02/98
#include <ansi.h>
inherit ITEM;
int j=3;
void create()
{
        set_name("清兵人马", ({ "qingbingrenma"}));
        set("unit", "只");
        set_weight(90000000);
        set("long", "
一只远道而来的清兵人马，看来有不少高手。中间插
着一面大旗，似乎写着“大清”二个大字，队伍之中
似乎有一辆囚车。。。\n");
        set("no_get", 1);
        set("no_drop", 1);
         set("no_put",1);
}

void init()
{ remove_call_out("aaa");
  call_out("aaa", 120, this_object());  
  add_action("do_rob", "jieche");
}

int do_rob()
{
   object me, ob;   
   string arg;
   int stage, i;
   me = this_player();
   ob = this_object();
   stage = 0;
   arg = query("arg");

   if(!living(me)) return 0;
   if( !query("kill_yunlong", me) )
       return notify_fail("你胆子不小，竟敢和大清做对？\n");
   if(objectp(present("qingbing", environment(me))))
       return notify_fail("清兵看来武功不弱，你还是先打发了面前这个再说吧！\n");  

   message_vision(HIR"$N对着$n大吼一声："+me->name()+"在此！快把囚车里的义士给放了！\n"NOR, me, ob);
   set_temp("xx_rob", 1, me);
   remove_call_out("make_bs");
   call_out("make_bs", 1, me, ob); 
   return 1;     
}
void make_bs(object me, object ob)
{
   object obj, obj1;
        if (j>0){
          obj = new(__DIR__"xiake");
         obj->move(environment(me));
          obj->do_copy(me);
         obj1 = new(__DIR__"xiake");
         obj1->move(environment(me));
           obj1->do_copy(me);
          j=j-1;     }
else {
       message_vision(HIW"$N见已经无活人，将反清义士救出！！\n"NOR, me);    
       ;    
       obj=new(__DIR__"dashi");
       obj->move(environment(me));
//       obj->move(me);
       set("owner",query("id",  me), obj);
       addn("combat_exp", 30, me);
       addn("potential", 10, me);
       addn("shen", 100, me);
        tell_object(me,"你被奖励了\n二百点经验值。\n");
       delete_temp("rob_start", me);
       delete_temp("xx_rob", me);
       delete_temp("rob_job", me);
       delete_temp("j", me);
       message_vision("$N转过几个小山丘就不见了。\n",ob);
       destruct(ob);
    }
}

void aaa(object me)
{
        if (! me) return;
       message_vision("$N转过几个小山丘就不见了。\n",me);       
       destruct(me);
       return;
}
