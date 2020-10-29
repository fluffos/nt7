// /u/cool/tls/wangxueting.c
// 1997.2.13

#include <ansi.h>
#include <room.h> 
inherit ROOM;
string tree(object);
void create()
{
  set("short","忘雪亭");
  set("long",@LONG
这是一个小亭子，亭边长着一棵枯树。后面山壁上有个洞口，据
说是过去历代高僧苦修的地方，这里山风阴冷，你不由的打了个寒颤，
牙齿也开始打起颤来，还是赶快下去吧。
LONG);

     set("outdoors", "天龙寺");
     set("exits",([
           "southdown" : __DIR__"fqg",
           "down" : __DIR__"wfd",
     ]));
     set("item_desc", ([
        "枯树" : (: tree :),
        "tree" : (: tree :),
        "shu" : (: tree :),
     ]));
     set("coor/x",-390);
  set("coor/y",-250);
   set("coor/z",40);
   setup();
}


string tree(object me)
{   
    if((int)me->query_skill("kurong-changong", 1) < 40)
        return  "这是一棵老树。\n";
    if((int)me->query_skill("kurong-changong", 1) >= 40)
        return  "这是一棵老树,你仔细看了看，这树长的甚是奇怪，一半边树都枯了，可另半边的树干还长出了绿叶。\n"; 
}

void init()
{
	add_action("do_jingzuo","jingzuo");	
        add_action("do_jingzuo","静坐");	
}

int do_jingzuo()
{
	object me = this_player();
       if ( (int)me->query_skill("kurong-changong", 1) < 40 )
               return notify_fail("你坐在这里干嘛，想冻死啊。\n");
        if ( (int)me->query_skill("kurong-changong", 1) > 120 )
               return notify_fail("你看来看去，觉的再坐下去也没什么收获了。\n");
       if (me->query_skill_mapped("force") != "kurong-changong")
               return notify_fail("你现在的内功不对。\n");
       if ( (int)me->query_skill("buddhism", 1) < 120 )
               return notify_fail("你看了半天，可是你佛学造诣太浅，没有什么体会。\n");
       if ( (int)me->query("jing")<30) 
        { write("你太累了，还是歇会再研读吧！\n");
        return 1;
         }
   
	message_vision("$N看着这棵半枯半荣的老树，你暗印佛法，心中若有所思。\n", me);
       	me->receive_damage("jing", 30);
              me->receive_damage("jingli", 10); 
		me->improve_skill("kurong-changong", (int)me->query("int"));
	return 1;
}
