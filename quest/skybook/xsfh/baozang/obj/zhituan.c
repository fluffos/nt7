// by tangfeng 8/2004

#include <ansi.h>
inherit ITEM;

#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"

void create()
{
        set_name(HIW"纸团"NOR, ({ "zhi tuan", "zhituan", "paper"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一个奇怪的纸团，展开之后似乎纪录一些内功的运行方法。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
        }
}
void init()
{
          if(!this_object()->query("owner")) return;
     	  add_action("do_yanjiu", "yanjiu");	
     	  add_action("do_yanjiu", "find");
}

int do_yanjiu(string arg)
{
	object obj,me = this_player();        		       
	if (!(arg=="zhi tuan" || arg == "zhituan" || arg == "paper")) return 0;
	if ( me->is_busy()) 
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() ) 
		return notify_fail("你无法在战斗中做这个事情。\n");
	if (!id(arg))
		return notify_fail("你要翻什么？\n");
        if( !me->query(QUESTDIR5+"shuku")||me->query(QUESTDIR5+"shuku")<3)
		return notify_fail("你哪里来的奇怪纸团啊。\n");
	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("你哪里来的奇怪纸团啊。\n");
	if (me->query(QUESTDIR4+"lengquanshengong"))
		return notify_fail("你已经明了冷泉神功的修炼方法。\n");
  if(!present("tishi ka",me))
  {
  	message_vision(HIY"突然一个人影出现在$N面前，递给$N一张卡片。\n"NOR, me);
  	tell_object(me,YEL"你低头一看，是一张提示卡，回头再一看，人影已经不见——好帅哦~~~~~。\n"NOR);
  	obj=new(__DIR__"tishika");
  	obj->move(me);
	me->start_busy(2);
    tell_object(me,YEL"你还是认真看一下提示卡的内容，不要过于冲动。\n"NOR);
  	return 1;
  }	
  //只能一次机会
  //难度系数与原来的凌波微步难度相同
  //降低难度，以前是random(kar)+random(int)>50,现在修改成1个random(kar+int)>50 by lsxk 2007/9/12
  //增加5点难度,毕竟是调用一个random总合来判断 random (30+30) > 50 这个判断有点过低 by server 2007/9/14
  //改为54, 1/10概率
  if((random((int)me->query("kar")+(int)me->query("int"))) > 50
  //降低难度，以前是random(query_con)+random(query_int)>50,现在修改成1个random(query_con+query_int)>50 by lsxk 2007/9/12
       && (random((int)me->query_con(1)+(int)me->query_int(1))) > 70
	   && me->query("kar")<31)
  {
	  tell_object(me,HIG"你突然发现这线线代表的不是武功秘籍，却是一个藏宝的地点。\n"NOR);
	  tell_object(me,HIG"你仔细研究纸团的内容，地点应该就在刚才经过的书房里。\n"NOR);
	  me->set(QUESTDIR4+"lengquanshengong", 1);
	  me->start_busy(2);
	  log_file("quest/FEIHU", sprintf(HIR"%s(%s) 解开冷泉神功。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }
  else
  {
	  tell_object(me,HIY"\n你按照纸团上的这些线线运行全身经脉，发现全无用处，更别说提高武功了。\n"NOR);
	  log_file("quest/FEIHU", sprintf("%s(%s) 试图解开冷泉神功失败。经验：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"顺手丢掉一个纸团。\n"NOR, ({}));
	  if(me->query(QUESTDIR5+"shuku")==2 && me->query("registered")>=3)
	  {
                  tell_object(me,HIR"\n因为VIP身份，你可以继续使用搜索命令找到另外一张纸团。你有无限次机会。\n"NOR);
		  tell_object(me,HIR"但如果你认为目前属性不好或运气不佳，可以以后再来这里搜索，避免机会浪费。\n"NOR);
	  }
	  me->start_busy(2);
	  destruct(this_object()); 
  }
	return 1;	    
}
