#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "晃天门");
        set("long",@LONG
过了此门，便是寺中僧侣清修之地。抬头望去，只见屋宇连绵，
轻烟缭绕，传来一阵阵诵经、木鱼之声。这里南面是睡房，供给天龙
俗家弟子休息之用，门口挂着一个牌子(pai)，左右各站着一位武僧。
LONG);
	set("outdoors","dali");
        set("exits", ([    			
	        "west" : __DIR__"yz4",
		"east" : __DIR__"yaotai",
              "south" : __DIR__"xiuxishi1",
	]));

        set("objects",([
                __DIR__"npc/wuseng" : 2,
        ]));
                                                    
        set("item_desc",([
           "pai" : "南面为天龙俗家弟子睡房。\n"NOR,
        ]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("coor/x",-320);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
int valid_leave(object me, string dir)
{
        if (me->query("family/family_name") != "天龙寺" &&
            present("wu seng", environment(me)) && dir =="south")
           return notify_fail("武僧拦住你的去路，抱拳道：非天龙俗家弟子不得入睡房。\n");
        if ((me->query("class") =="bonze") && dir =="south" )
           return notify_fail("你是出家人，去到那俗家弟子睡房干嘛？\n");                
        return ::valid_leave(me, dir);
}


