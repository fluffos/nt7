#include <room.h>

inherit ROOM;

void create()
{
        set("short", "清都瑶台");
        set("long",@LONG
由此过去一路都是碎石路了，这一带只准寺内僧侣进入，其它人
等如果没有方丈许可是不可以来此的。向北可到无无境、雨花院阅读
经书文献，向东可至般若台练习武功，南面是寺内的药房。
LONG);
        set("outdoors","天龙寺");
        set("exits", ([
                "northup": __DIR__"road2",
                "eastup": __DIR__"banruo",
                "west": __DIR__"men3",
				"south":__DIR__"yaofang",                          
        ]));
			set("objects",([
                __DIR__"npc/liao-qing" : 1,
        ]));
        set("coor/x",-310);
  set("coor/y",-320);
   set("coor/z",30);
   setup();

        create_door("west", "木门", "east", DOOR_CLOSED);

}
int valid_leave(object me, string dir)
{	
	mapping myfam;
        myfam = (mapping)me->query("family");
                     
   if ((!myfam || myfam["family_name"] != "天龙寺") && objectp(present("liaoqing chanshi", environment(me)))
      &&(dir == "northup"||dir == "eastup"))
            return notify_fail("了清禅师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你不是天龙寺弟子，不得入后寺扰乱清修。\n");

if ( !me->query("tls") && objectp(present("liaoqing chanshi", environment(me)))
      &&(dir == "northup"||dir == "eastup"))
            return notify_fail("了清禅师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你不是天龙寺出家弟子，不得入后寺扰乱清修。\n");
                        
        return ::valid_leave(me, dir);
}