//Room: /d/dali/tusifu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","土司府");
        set("long", @LONG
土司府是当地傣族世袭土司刀氏的衙门，一座古老的砖木建筑物，
门庭居高临下，庄严坚实，门前是宽广的石阶，有点象衙门气势，房
屋共三台，占地约八百亩，分作正厅，议事厅，后厅，厢房。
LONG );
        set("objects", ([
           "/d/dali/npc/datusi": 1,
           "/d/dali/npc/shicong": 2,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "enter"  : "/d/dali/tusimentang",
            "south"  : "/d/dali/dahejiewest",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}