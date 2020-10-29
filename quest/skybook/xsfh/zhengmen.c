//by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"

void create()
{
	set("short", GRN "苗家庄门口" NOR);
	set("long",@long
这里是苗家庄的大门，两扇黑漆漆的大门敞开着，门口正中央高悬着一块
金色横匾“苗家庄”，台阶两旁立着两个石狮，只是门街冷清，颇为凄凉。
long);
  set("outdoors", "兰州");
	set("exits",([
		"east" : __DIR__"sroad1",
		"west" : __DIR__"qianting",
]));
            set("quest",1);
	set("no_fight", 1);
	setup();
}
int valid_leave(object me, string dir)
{
    if (dir == "west" && !me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
          return notify_fail(RED"苗家庄早已经封闭，无法进去。\n"NOR);
        if(dir == "west" &&me->query_condition("killer"))
   		          return notify_fail(RED"苗家庄早已经封闭，无法进去。\n"NOR);
    return ::valid_leave(me, dir);
}

void init()
{
  object me;
  me = this_player();
  if (me->query(QUESTDIR2+"start"))
       me->start_busy(1);
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"answer")
	 &&!me->query(QUESTDIR2+"over")
     &&!me->query_temp(QUESTDIR2+"kill")
     &&!me->query_temp(QUESTDIR2+"huyidao"))
  {
     tell_object(me,YEL"突然你听到苗家庄内好像有他人，只听一个声音朗声道：“金面佛苗大侠在家么？有朋友远道来访。”\n"NOR);
     tell_object(me,YEL"只听屋中一人说道：“是哪一位朋友？恕苗人凤眼生，素不相识。”这话声只觉又是苍凉，又是醇厚。\n"NOR);
     remove_call_out("goqianting");
     call_out("goqianting", 3, me);
     write(CYN"\n你不由感到十分好奇，你停了下来，静静倾听。\n"NOR);
  }
  else
  {
  remove_call_out("greeting");
  call_out("greeting", 4, me);
  }
	add_action("do_save", "save");
	add_action("do_quit", "quit");
}
void greeting(object me)
{
    int shen;
  if(!me) return;
   if(!present(me,this_object())) return;
   if(me->query(QUESTDIR2+"start")) return;
   shen = me->query("shen");
  if(shen <0) tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：看你一身邪气，还请离开！\n"NOR);
     else tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：这位少侠，还请离开！\n"NOR);
}
void goqianting(object me)
{
  if(!me) return;
  if(!present(me,this_object()))
  {
      tell_object(me,HIY"你擅自离开苗家庄，错过了精彩的一幕。\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s)初进苗家庄，却擅自离开，失败。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
     me->delete_temp(QUESTDIR2+"answer");
    return;
}

     tell_object(me,YEL"\n你听到“锺氏兄弟”、“书信”，好像是旧识，又好像是讨债来的，却听不清楚具体在说什么，你不由好奇心起。\n"NOR);
	   tell_room(environment(me), YEL+me->name()+"紧了紧随身物品，紧跟着长袖飘飘，飞身跃过高墙！\n" NOR, ({me}));
           tell_object(me,RED"你一提内息，使出「一苇渡江」轻功，一翻身，越过高墙，这一手轻功当真落地无声，确实了得。\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s)初进苗家庄。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	   me->move(__DIR__"qianting");
}
int do_save()
{
	write("这里不准存盘！\n");
	return 1;
}
int do_quit()
{
	write("这里不准退出！\n");
	return 1;
}

