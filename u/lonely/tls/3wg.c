#include <room.h>

inherit ROOM;

void create()
{
        set("short", "三无宫");
        set("long",@LONG
无住、无相、无愿便是佛家常说的‘三无’。这宝座上坐的是南
无弥勒尊佛金像，开怀露腹，笑看众生。几个知客僧人正来往忙碌招
待香客。北面通往兜率大士院，南面是一条石板路。西面通向龙象台。
LONG);
        set("exits", ([
                "east" : __DIR__"men4",
		"northup" : __DIR__"shiyuan",  
                "westup" : __DIR__"longxiang1",            
	]));
	
        create_door("east", "木门", "west", DOOR_CLOSED);

        set("coor/x",-390);
  set("coor/y",-320);
   set("coor/z",20);
   setup();
}
