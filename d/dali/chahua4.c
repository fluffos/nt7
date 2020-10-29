//Room: /d/dali/chahua4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花
园中，北面是一片波光涟滟的湖面。靠岸的柳树下，有几盆茶花，娇
艳照人，在满园烂漫的茶花围中，仍骄然出群。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua4": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/chahua5",
            "northwest"  : "/d/dali/chahua2",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6871);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}