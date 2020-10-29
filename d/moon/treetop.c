// ken 1999.12.9
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{    set("short", "枯树顶");
        set("long", @LONG
这棵树还算高大，可惜已枯死多年。这里四下漆黑，只是远方隐隐
似有灯光闪耀。你看着脚下的白雾，举棋不定，踌躇不前....
LONG
        );
       	set("coor/x",-10);
	set("coor/y",1010);
	set("coor/z",10);
        set("no_magic",1);
        set("item_desc", ([
         "白雾": "看来想越过这团白雾，只能靠施展轻功了。(jump)\n",
	 "灯光" : "想靠近这隐约的灯光，只好凭运气闯一闯了。(jump)\n",
		        ]) );
	setup();
}

void init()
{
        add_action("do_jump", "jump");
}
int jumpbusy(object me)
{  object room;
  message_vision("\n只听一阵衣衫撕裂和树枝折断的声音，然后$N重重地摔到了地上...\n\n",me);  
         me->unconcious();
         room = find_object("/d/yuanyue/zz7");
         if(!objectp(room)) room=load_object("/u/moon/zz7");   
         me->move(room);    
         return 1;
}

int jumpbusya(object me)
{  object room;
 message_vision("\n$N突然发觉内力不济，心中暗叫不妙,身形已向下急坠!\n\n",me);
         room = find_object("/d/yuanyue/zz2");
         if(!objectp(room)) room=load_object("/u/moon/zz2");
         me->move(room);
         me->start_busy(5);
         return 1;
}

int jumpbusyb(object me)
{  object room;
   write("\n你顺利地飞越了脚下的浓浓白雾,轻轻的落在一大片草地上...\n\n" );
         room = find_object("/n/moon/caodi");
         if(!objectp(room)) room=load_object("/u/moon/caodi");
         me->move(room);
//       me->set("force",random(200));
         return 1;
}

int do_jump(string arg)
{
	object me;
        int aa,bb;
   	me = this_player();
        aa = me->query_skill("move",1);
        bb = me->query("force");
        if( !arg || arg=="" ) 
        return notify_fail("你想向哪个地方跳？\n");
        if( arg=="out" || arg=="灯光") 
 {    
         if(aa < 30)
     {  message_vision("\n$N横下心来，闭上眼睛，猛地向外跳了出去....\n",me); 
        me->start_busy(1);
        call_out("jumpbusy",1,me);
        me->stop_busy();
        return 1;
      }
         else 
message_vision("\n$N展开身形，御风而起，勇敢地向无边的黑暗掠去......\n",me);
        
	if( bb < 200 )
      {  me->start_busy(1);
          call_out("jumpbusya",1,me);
          me->stop_busy(); 
	 return 1;						
      }
else    
      {  me->start_busy(1); 
         call_out("jumpbusyb",1,me); 
         me->stop_busy(); 
 	 return 1;						
      }
 }
	write("你想向哪个地方跳？\n");
}

