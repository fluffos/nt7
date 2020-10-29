//Room: /d/dali/center.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","中心广场");
        set("long", @LONG
这里就是大理城的中心，彩色石块铺成的大道向四方伸延。广场
呈菱形，一圈围的都是小贩，艺人，和看热闹的。熙熙攘攘的人群中
也少不了几个跑江湖之人，一些在中原闻所未闻的事物令一些刚入江
湖之人兴奋不已。
LONG );
        set("objects", ([
           "/d/dali/npc/jianghuyiren": 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 4 */
            "north"  : "/d/dali/taihejiekou",
            "south"  : "/d/dali/shizilukou",
            "east"   : "/d/dali/taiheju",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}