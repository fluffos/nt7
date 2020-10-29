//Room: /d/dali/wangfugate.c
//Date: June. 29 1998 by Java

inherit ROOM;

void create()
{
        set("short","王府大门");
        set("long", @LONG
你正站在一座豪华的府门前，门前有两只极大的石狮子，门上高
悬一块横匾，上书「镇南王府」四个金字。门口站着两排侍卫，身着
锦衣，手执钢刀，气宇轩昂。
LONG );
        set("objects", ([
                CLASS_D("duan")+"/first" :  1,
           CLASS_D("dali")+"/chuwanli": 1,
           "/d/dali/npc/weishi2": 1,
           "/d/dali/npc/weishi1": 2,
        ]));
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "enter"  : "/d/dali/wfdating",
            "south"  : "/d/dali/wangfulu",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6860);
	set("coor/z", 0);
	setup();
        "/clone/board/dali_b"->foo();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (dir == "enter" && ob = present("chu wanli", this_object()))
                return ob->permit_pass(me, dir);

        return ::valid_leave(me, dir);
}
