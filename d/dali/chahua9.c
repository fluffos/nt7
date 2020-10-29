//Room: /d/dali/chahua9.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花
园的最高处，低头看去，满园春色，尽在目下。西望亭台楼阁，错落
有秩。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua7": 1,
           "/d/dali/npc/muwanqing": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "southdown"  : "/d/dali/chahua7",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6811);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}