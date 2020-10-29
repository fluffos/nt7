#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "荡天门");
        set("long",@LONG
过了此门，便是三元宫、兜率大士院等宝殿。抬头望去，只见屋宇连
绵，轻烟缭绕，传来一阵阵诵经、木鱼之声。这里南面是睡房，供给天龙
俗家弟子休息之用，门口挂着一个牌子(pai)，左右各站着一位武僧。
LONG
        );
	set("outdoors","dali");
        set("exits", ([    			
                "west" : __DIR__"3wg",
                "east" : __DIR__"yz5",
               "south" : __DIR__"xiuxishi2",
               	]));
        set("objects",([
                __DIR__"npc/wuseng" : 2,
        ]));
                                                    
        set("item_desc",([
           "pai" : "南面为天龙俗家弟子睡房。\n"NOR,
        ]));
       
        create_door("west", "木门", "east", DOOR_CLOSED);

        set("coor/x",-380);
  set("coor/y",-320);
   set("coor/z",20);
   setup();
}
int valid_leave(object me, string dir)
{
        if (me->query("family/family_name") != "天龙寺" &&
            present("wu seng", environment(me)) && dir =="south")
           return notify_fail("武僧拦住你的去路，抱拳道：非天龙俗家弟子不得入睡房。\n");
        if ((me->query("class") =="bonze") && dir =="south" )
           return notify_fail("你是出家人，去到那俗家弟子睡放干嘛？\n");                
        return ::valid_leave(me, dir);
}
