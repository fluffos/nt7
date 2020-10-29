#include <ansi.h>
inherit F_SSERVER; 

mapping exits_name=([
"east":            "东方",
"south":           "南方",
"west":            "西方",
"north":           "北方",
"eastup":          "东上方",
"southup":         "南上方",
"westup":          "西上方",
"northup":         "北上方",
"eastdown":        "东下方",
"southdown":       "南下方",
"westdown":        "西下方",
"northdown":       "北下方",
"northeast":       "东北方",
"northwest":       "西北方",
"southeast":       "东南方",
"southwest":       "西南方",
"up":              "上方",
"southeast":       "东南方",
"southwest":       "西南方",
"up":              "上方",
"down":            "下方",
"enter":           "里边",
"out":             "外边",
]);
int do_she(string arg,object me,object bow,int num);
int do_shoot(string id,object me,object room,string what,int m,object bow,int num);

string exits_reverse(string dir);

string exits_reverse(string dir)
{
 if( dir=="east" ) return "west";
 if( dir=="west" ) return "east";
 if( dir=="south" ) return "north";
 if( dir=="north" ) return "south";
 if( dir=="eastup" ) return "westdown";
 if( dir=="westup" ) return "eastdown";
 if( dir=="southup" ) return "northdown";
 if( dir=="northup" ) return "southdown";
 if( dir=="eastdown" ) return "westup";
 if( dir=="westdown" ) return "eastup";
 if( dir=="southdown" ) return "northup";
 if( dir=="northdown" ) return "southup";
 if( dir=="northeast" ) return "southwest";
 if( dir=="northwest" ) return "southeast";
 if( dir=="southwest" ) return "northeast";
 if( dir=="southeast" ) return "northwest";
 if( dir=="up" ) return "down";
 if( dir=="down" ) return "up";
 if( dir=="enter" ) return "out";
 if( dir=="out" ) return "enter";

 return "";
}

int perform(object me,object target)
{
  object bow;
  int num;

  if( !objectp(bow=query_temp("weapon", me) )
       || !query("is_bow", bow) )
  return notify_fail("弓还没上手呢，还想用连珠箭法？！\n");

  num=me->query_skill("lianzhu-arrow",1)/100+1;

  if( num < 2 || me->query_skill("arrow",1) < 100 )
  return notify_fail("还是好好练练你的箭法吧！\n");

  message_vision(HIY"$N从箭囊内抽出"HIW+CHINESE_D->chinese_number(num)+HIY"支"HIW"羽箭"HIY"，搭在"
       +query("name", bow)+HIY"上，准备施展生平绝技——"
       +HIR"连珠箭法"+HIY"！！\n"NOR,me);
  input_to("do_she",me,bow,num);
  return 1;
}


int do_she(string arg,object me,object bow,int num)
{
   object ob,room;
   int i,n,m;
   string what;
   mapping exits;

   room=environment(me);
   if( query("no_fight", environment(me)) )
   {
    tell_object(me,"这里不许战斗！\n");
    return 1;
   }

   if( query("duration", bow)<0 )
   {
    message_vision("$N手中的"+query("name", bow)+"“嘣”地一声断了！\n",me);
    destruct(bow);
    return 1;
   }

   if( me->query_str()<query("dam", bow)/20 )
   {
    tell_object(me,"你使尽吃奶的力气也拉不开弓来，看来力气不够！\n");  
    return 1;
   }

   if( me->is_busy() )
   {
    tell_object(me,"你现在正忙着呢！\n");
    return 1;
   }

   if( query("qi", me)<400*num || query("jing", me)<100*num )
   {
    tell_object(me,"你现在精气不够充盈，连珠箭法恐怕施展不出来！\n"); 
    return 1;
   }

   if( sscanf(arg,"she %s %d",what,n)==2 )
   {
    if( n>query("dam", bow)/200)n=query("dam", bow)/200;
    for(i=0;i<n;i++)
    {
      if( room && mapp(exits=query("exits", room)) && stringp(exits[what]) )
      {
       m=i+1;
       room=find_object(exits[what]);
      }
    }

    if( room==environment(me) )
    {
     tell_object(me,"看清楚点，朝哪里射呀你？\n");
     return 1;
    }

    if( room)
     {
      if( query("have_quest", room) )
      { 
       tell_object(me,"那里有神明佐佑，不容你胡来也！\n"); 
       return 1;
      }

      "/cmds/std/look.c"->look_room(me,room);  
      message_vision(HIY"随后只见$N立了一个霸王上弓式，朝"HIR
       +exits_name[what]+HIY"把弓拉满.......\n"NOR,me);
      tell_object(all_inventory(room),HIB"你觉得一股猛烈的杀机从"HIR
       +exits_name[exits_reverse(what)]+HIB"传来！！\n"NOR);

      tell_object(me,HIR+exits_name[what]+HIW"的情景你一目了然，"
                                      +"你把利箭渐渐瞄准了——>\n"NOR);   
      me->start_busy(3+random(3));  
      input_to("do_shoot",me,room,what,m,bow,num);
     } else
      tell_object(me,"看清楚点，朝哪里射呀你？\n");  

    } else
      tell_object(me,"不会射箭？找人家教教你吧！\n");
    return 1;
}

int do_shoot(string arg,object me,object room,string what,int m,object bow,int num)
{
  int k;

  for(k=0;k<num;k++)
  bow->do_shoot(arg,me,bow,room,what,m);
  if( num>3 ) num=3;
  me->start_busy(num*2);
  return 1;
} 