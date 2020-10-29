//add by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>

int do_action(string arg);
int do_leave(string arg);
int do_stop(string arg);
int do_start(string arg);
int do_full(string arg);
void start(object me);
void rule(object me);
void copy_person(object me);
void destruct_person(object ob);
void destruct_book(object ob);
int do_eat(string arg);

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

string* anhao = ({"维","经","摩","法","华","严","无","量","寿","大","般","涅","磐","阿","含","金","刚","波","罗","蜜","多","心","佛",
                  "须","提","若","菩","萨","以","满","恒","河","沙","等","世","界","七","宝","佛","说","是","经","已","长","老","所",
                  "菩","提","及","诸","比","丘","尼","优","婆","塞","优","婆","夷","一","切","世","间","天","人","阿","修","罗","闻",});

void create()
{
	set("short",HIW "少林阵" NOR);
	set("long", @LONG
这是一片空场地，四角分别站着四个少林弟子。一角放着个兵器架。
LONG);
  set("no_get_from", 1); 
  set("quest", 1);
  set("no_sleep_room", 1);
	setup();
}
void init()
{
  object me;
  me = this_player();
  if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎气血有些不顺，跟着一个趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引着你，瞬间你失去知觉。\n"NOR);
   tell_room(environment(me),HIR"\n只见，地上突然出现一个裂洞，"+ me->name()+ "一头扎了下去，瞬间消失。\n"NOR, ({ me }));
   if(me->query(QUESTDIR3+"bad"))  me->move("/d/shaolin/smdian");
   else if(me->query(QUESTDIR3+"good"))  me->move("/d/shaolin/fzjs2");
   else me->move("/d/xiangyang/damen"); 
   tell_room(environment(me), HIR"\n半空中，似乎一个人掉了下来，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({ me }));
   message_vision(HIC"$N揉了揉眼睛，看才似乎像一场梦，好像什么都没发生。\n"NOR,me); 
   return;
  }
	add_action("do_full", ({"full"}));
  add_action("do_eat",({"eat","drink"}) );
	add_action("do_leave", ({"leave"}));
	add_action("do_start", ({"start"}));
	add_action("do_stop", ({"stop"}));
  add_action("do_action", ({"lian", "learn", "tu", "steal","kill", "guard","beg", "hit", "steal", "fight", "throw", "ansuan"}));   
//remove_call_out("rule")
	call_out("rule",2,me);
}
int do_eat(string arg)
{
     object me = this_player();
     if (me->query("food") < me->query("str")*3+50){
          message_vision(HIC"$N正觉得有些肚子饥，外面走来一个僧人，送给$N一些饭菜。\n"NOR, me);
          message_vision(HIC"$N爽快地大吃一顿，随手把剩余的饭菜丢了出去。\n"NOR, me);
          me->add("food", me->query("str")*10+100, me);
          return 1;
     }
     else
     if (me->query("water") < me->query("str")*3+50)
     {
          message_vision(HIC"$N正觉得有些喉咙渴，外面走来一个僧人，送给$N一个水袋。\n"NOR, me);
          message_vision(HIC"$N咕咚咕咚喝了一大口，随手把水袋丢了出去。\n"NOR, me);
          me->add("water", me->query("str")*10+100, me);
          return 1;
     }
     else  return notify_fail("你喝太多了，吃太多了，不怕撑死？\n");
}

int do_leave(string arg)
{
		object ob,obj,me;
		ob=this_object();
		me = this_player();
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
		{
			message_vision(HIC"$N决定离开这里，却听见一个声音道：我弥陀佛，施主留步。\n"NOR, this_player());
			return 1;
	  }
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && me->query_temp(QUESTDIR5+"shaolinzhen"))
         message_vision(HIC"$N轻蔑地看了看四角的僧人，哼了一声，决定离开"+environment(me)->query("short")+"。\n"NOR, this_player());
    else message_vision(HIC"$N匆匆离开"+environment(me)->query("short")+"。\n"NOR, this_player());
    destruct_book(ob);
    destruct_person(ob);
    tell_room(environment(me),HIR"\n只见，地上突然出现一个裂洞，"+ me->name()+ "一头扎了下去，瞬间消失。\n"NOR, ({me}));
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && me->query_temp(QUESTDIR5+"shaolinzhen"))
        me->move("/d/shaolin/smdian");
    else if(me->query(QUESTDIR3+"good"))  me->move("/d/shaolin/fzjs2");
    else me->move("/d/xiangyang/damen"); 
    tell_room(environment(me),HIR"\n只见，地上突然出现一个裂洞，"+ me->name()+ "出现在房间之中。\n"NOR, ({me}));
	message_vision(HIC"$N匆匆地来到"+environment(me)->query("short")+"。\n"NOR, me);
    if(me->query(QUESTDIR3+"good") && me->query_temp(QUESTDIR4+"shaolinzhen") && me->query_temp(QUESTDIR4+"dagouzhen"))
		{
      if(!(obj=present("xuanci dashi", environment(me)))) 
	    {
        obj=new("/kungfu/class/shaolin/xuan-ci");
        obj->move(environment(me));
        message_vision(HIC"$N匆匆地走了过来，神色有些慌张。\n"NOR, obj);
      }
      me->set_temp(QUESTDIR4+"anhao",anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]+
                                     anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]);
       message_vision(HIC"$N对$n点了点头，恭喜$n闯过少林阵法。\n"NOR, obj,me);
       tell_object(me,obj->name()+"在你的耳边悄声说道：恩，果然是"+me->query("family/master_name")+"座下"+me->query("family/family_name")+"高手，确实武功了得。\n"NOR);
       tell_object(me,obj->name()+"在你的耳边悄声说道：如此说来，还是尽快营救萧大侠为是。半夜三更，在颂摩崖届时会有丐帮弟子接应。\n"NOR);
       tell_object(me,obj->name()+"在你的耳边悄声说道：注意一定是半夜时刻，另外，可能需要暗号接应，暗号是【"+me->query_temp(QUESTDIR4+"anhao")+"】。\n"NOR);
       message_vision(HIC"$N对$n冲着$n大声叫到：壮士，加油！\n"NOR, obj,me);
       me->set(QUESTDIR+"time",time());
	  }
	  return 1;
}
int do_stop(string arg)
{
		object me = this_player();
		if(!me->is_fighting()) return 0;
	  if(!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query_temp(QUESTDIR5+"shaolinzhen"))  message_vision(HIC"\n$N感到自己有些力不从心，决定暂时中止阵法。\n"NOR, this_player());
    else   message_vision(HIC"\n$N有些玩够了，你决定停止战斗。\n"NOR, this_player());
    tell_object(me,HIR"\n突然你感到一股神力充斥在房间之中，双方不由自主停止战斗。\n"NOR);
    tell_room(environment(me),HIR"\n突然你感觉一股神力充斥在房间之中，双方不由自主停止战斗。\n"NOR, ({ me }));
    me->remove_all_killer();   
    destruct_person(this_object());
    return 1;
}
int do_start(string arg)
{
		object me = this_player();
    if(me->is_fighting()) return 0;
	  if((present("shaolin dizi", this_object()))) 
	  {
	  	tell_object(me,HIR"阵法已经启动！\n"NOR);
	    return 1;
	  }
    if(this_object()->query("busy")) 
    {
      tell_object(me,HIR"稍微休息一下，阵法马上重新启动！\n"NOR);
      return 1;
    }
    destruct_book(this_object());
	  if(!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query_temp(QUESTDIR5+"shaolinzhen"))  message_vision(HIC"$N决定尝试闯一闯这少林阵法，尽快离开这里。\n"NOR, this_player());
    else   message_vision(HIC"$N决定再次闯一闯这少林阵法。\n"NOR, this_player());
    tell_object(me,HIR"突然你感到一股神力充斥在房间之中，你精神不由一阵。\n"NOR);
    me->remove_all_killer();   
    destruct_person(this_object());
	  remove_call_out("start");
    remove_call_out("busy");
    call_out("busy",120);
    this_object()->set("busy",1);
	  call_out("start",4,me);
    return 1;
}
void busy()
{
  this_object()->delete("busy");
  return;
}
int do_full(string arg)
{
		object me = this_player();
    if(me->is_fighting()) return 0;
    if(me->is_busy()) return 0;
    if(me->query("eff_qi")>=me->query("max_qi") && me->query("eff_jing")>=me->query("max_jing")) return 0;
    
    //疗伤
    if(me->query("eff_qi")<me->query("max_qi"))
    {
      me->set("eff_qi",me->query("max_qi"));
      tell_object(me,HIR"突然你感到一股神力充斥在房间之中，你的伤势竟然康复大半。\n"NOR);
    }
    //疗精
    if(me->query("eff_jing")<me->query("max_jing"))
    {
      me->set("eff_jing",me->query("max_jing"));
      tell_object(me,HIR"突然你感到一股神力充斥在房间之中，你的精血完全恢复。\n"NOR);
    }
    me->remove_all_killer();   
    destruct_person(this_object());
    tell_room(environment(me),HIR"突然你感觉一股神力充斥在房间之中，原来"+me->name()+"正在招呼异力疗伤！\n"NOR, ({ me }));
    return 1;
}
void start(object me)
{
  if(!me) return;
  if(!present(me,this_object())) 
  {
  	tell_object(me,HIR"身体不舒服？还没两秒钟就走开？好像也跑得太快了点。\n"NOR);
  	return;
  }	
  message_vision(HIC"$N决定闯阵。\n"NOR, me);
  message_vision(HIC"一会，从角落里缓缓地走出四个僧人，身着锦斓袈裟，估计都在五十开外！\n"NOR, me);
  copy_person(me);
  return;
}
void rule(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) 
  {
  	tell_object(me,HIR"身体不舒服？还没两秒钟就走开？好像也跑得太快了点。\n"NOR);
  	return;
  }	
  if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
  {
    if(!(present("shu", this_object())))
    {
       obj=new("/d/shaolin/obj/fojing1");
       obj->move(environment(me)); 
       message_vision(YEL"\n“啪”地一声，一本"+obj->query("name")+"掉在$N面前。\n"NOR,me);
         obj=new("/d/shaolin/obj/fojing2");
       obj->move(environment(me)); 
       message_vision(YEL"“啪”地一声，又一本"+obj->query("name")+"掉在$N面前。\n"NOR,me);
    }
   message_vision(HIC"\n只听一个声音对道：施主杀性太重，行走江湖只怕到处是一片腥风血雨，还是呆在这里潜心修我佛法为上！\n"NOR,me);
   message_vision(HIC"这两本佛经可以修炼佛性，消灭厉气，其实如果施主能够领悟其中，对你的武功修为其实也是大有帮助的！\n"NOR, me);
  }
    tell_object(me,HIY"\n要离开这里只有硬闯少林阵。你可以使用：\n"
                       +"启动阵法（start）、中止阵法（stop）、离开房间（leave）、恢复自己（full）。\n"
                  +HIR"\n阵法之中，有死亡的可能，请及时中止阵法！\n\n"NOR);
  return;
}
int do_action(string arg)
{
	 if(wizardp(this_player())) return 0;
   tell_object(this_player(),HIR"你正要有所动作，只听一个声音道：别乱动！\n");
   return 1;
}
void copy_person(object me)
{
	object obj1,obj2;
	int i;
  //teamleader
  if(!me) return;
  obj1=new(__DIR__"npc/dizi");
  obj1->set("teamleader",1);
  obj1->set("party","sl");
  obj1->set("fight_id",me->query("id"));
  obj1->move(environment(me)); 
  for( i = 0; i <3;i++)
  {
    obj2=new(__DIR__"npc/dizi");
    obj2->set("party","sl");
    obj2->set("fight_id",me->query("id"));
    obj2->move(environment(me)); 
  }
}
void destruct_person(object ob)
{
	object obj;
	int i;
  for( i = 0; i <4;i++)
  {
	  if(!(present("shaolin dizi", ob))) return;
    obj=present("shaolin dizi", ob);
    if(!random(3)) message_vision(HIR"$N点了点头，缓缓消失在角落里。\n" NOR, obj);
    else message_vision(HIR"$N道了声佛号，慢慢地退了出去。\n" NOR, obj);
		destruct(obj);
  }
}
void destruct_book(object ob)
{
	object obj;
	int i;
  for( i = 0; i <2;i++)
  {
	  if(!(present("shu", ob))) return;
    obj=present("shu", ob);
    if(random(2)) message_vision(HIR"一阵风过，$N飘在风里，消去了。\n" NOR, obj);
    else message_vision(HIR"一晃，$N竟然也跟着消失了。\n" NOR, obj);
		destruct(obj);
  }
}
