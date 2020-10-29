//cool980727
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "诵经堂");
        set("long", @LONG
这里是寺内僧人诵经的地方。一眼望去，大堂内坐满了人，诵经
声起伏不绝，有的低沉缓慢，有的尖声急促，中间杂着摇动法器的金
属声。你悄悄找个地方，盘腿坐下来，开始念经。你前面放了许多薄
薄的小册经书(book),以供你读用。
LONG);
        set("exits", ([
                "east" : __DIR__"yz6",
                "north" : __DIR__"gmd",
        ]));
 
         set("no_fight", 1);
 
        set("coor/x",-360);
  set("coor/y",-300);
   set("coor/z",20);
   setup();
}
#include "book.h";

void init()
{
       add_action("do_song", "songjing");
       add_action("do_song", "dujing");
       add_action("do_look", "look");
       add_action("do_halt", "ting");
	   add_action("do_zuo", "sit");
       add_action("do_zuo", "zuo");
}
int do_look(string arg)
{
	object me = this_player();
    if (!arg) return 0;
	if (arg == "book") {
	        if (me->query_skill("buddhism",1)<120)
			{
            write("这些都是经书对你而言太过深奥了。\n");
			} else {
			write("这些都是经书，分成小册子，你可以读(songjing)它们来提高自己\n"
			+"的佛学知识 \n"
            +"《金刚经-卷1》(jingang-jing1)    《金刚经-卷2》(jingang-jing2)\n"
			+"《金刚经-卷3》(jingang-jing3)    《金刚经-卷4》(jingang-jing4)\n"
			+"《金刚经-卷5》(jingang-jing5)    《金刚经-卷6》(jingang-jing6)\n"
			+"《金刚经-卷7》(jingang-jing7)    《金刚经-卷8》(jingang-jing8)\n"
			+"《金刚经-卷9》(jingang-jing9)    《金刚经-卷10》(jingang-jing10)\n"
			+"《金刚经-卷11》(jingang-jing11)  《金刚经-卷12》(jingang-jing12)\n"
            +"《金刚经-卷13》(jingang-jing13)  《金刚经-卷14》(jingang-jing14)\n"
			+"《金刚经-卷15》(jingang-jing15)  《金刚经-卷16》(jingang-jing16)\n"
			+"《般若波罗蜜心经》(xin-jing)\n"
             +"你如果累了，可以停(ting)下，休息下，再重头读起。\n");
			me->set_temp("book_list", 1);
		    }
			return 1;
	       		   }		
}
int do_zuo(string arg)
{

	if (arg) return notify_fail("这里没什么可坐的，坐地上吧\n");	
	
	if (this_player()->query("class")!="bonze")
		return notify_fail("你不是出家人，不可以在这里诵经。\n");	
	
	if (this_player()->query_temp("book_sit"))
		return notify_fail("你已经坐在地上了。\n");	
			
	this_player()->set_temp("book_sit", 1);
	return notify_fail("你找了个空地盘腿坐下。\n");	
}

int do_halt()
{    
    object me = this_player();
    if (find_call_out("sing_stage") < 0) return 0;
	me->receive_damage("jingli",(int)me->query_skill("buddhism",1)/3);
	me->receive_damage("jing", (int)me->query_skill("buddhism",1)/4);
    message_vision(HIR"\n$N你觉的有些累了，停下来休息下。\n"NOR,me);
    remove_call_out("sing_stage");
    return 1;
}

int do_song(string arg)
{
       object me, ob; 
       int i = sizeof(book);
       int stage;

       stage = 0;
       me = this_player();
       ob = this_object();
	   if (me->query("class")!="bonze") return notify_fail("你不是出家人，不可以在这里诵经。\n");
       if(me->query_skill("buddhism", 1) >= 200) return notify_fail("你的禅宗心法已经无法通过诵经来提高了。\n");
       if (!me->query_temp("book_list")) return notify_fail("厉害，书名都不看，就开始读？\n"); 
	   if(!arg) return notify_fail("你想读什么经？\n");
	   if (!me->query_temp("book_sit")) return notify_fail("有个性！站着读？\n"); 
	   if (find_call_out("sing_stage") >= 0) return notify_fail("你能同时读两本经书吗？\n");
       if(!arg) return notify_fail("你想读什么经？\n");
	   if (me->query("jing")<100 ||me->query("jingli")<200)
             return notify_fail("你现在精力不够，还是休息休息再读吧？\n");
        while (i--) if (arg == book[i]["name"]) break;
        if (i<0) return notify_fail("这里没有你想读的经。\n");
        if(me->is_busy())
           return notify_fail("你正忙着呢。\n");
		tell_object(me,HIC"你端正身子，轻轻诵道：\n"
                      +"无上甚深微妙法 百千万劫难遭遇 \n"
                      +"我今见闻得受持 愿解如来真实义 \n"NOR);   
        message_vision(HIW "$N“咚”的敲了下木鱼，翻开经书，开始唧唧呱呱读起来。。\n\n"NOR, me);
              
      call_out("sing_stage", 2, me, stage, i, sizeof(book[i]["context"]));
      return 1;
}

void sing_stage(object me, int stage, int i, int size)
{
   if(stage < size) {
// message_vision(book[i]["context"][stage], me);
   tell_object(me,book[i]["context"][stage]);
   me->start_busy(1);
   call_out("sing_stage", 1, me, ++stage, i, size);
   }
else {
      message_vision(HIW"\n过了一会，$N声音渐渐小了下来，接着“锵”的一声法铃清响，随即寂然无声。\n"NOR,me);
      if (me->query_skill("buddhism",1)<180){
        tell_object(me,"你觉得这些经文非常深奥，诵经并不能提高你的佛学修为。\n");
       } else {
	    me->receive_damage("jingli",(int)me->query_skill("buddhism",1)/2);
		me->receive_damage("jing", (int)me->query_skill("buddhism",1)/3);
        me->improve_skill("buddhism", (int)me->query_int()*2+random((int)me->query_int())); 
		tell_object(me,"你有些疲累，不过在诵经中，对佛法有所领悟。\n");  
    if ((int)me->query("shen")<-((int)me->query_skill("buddhism",1)*2))
   me->add("shen",(int)me->query_skill("buddhism",1)*2);
	   }
      }
}
int valid_leave(object me, string dir)
{

	me->delete_temp("book_sit");
	me->delete_temp("book_list");
	return ::valid_leave(me, dir);
}
