// Room: /d/ruzhou/jiao1.c  结婚的花轿
// llm 99/06

inherit ROOM;

void create()
{
        set("short", "花轿");
        set("long", @LONG
你正坐在一顶大花轿里，里面空间不大，上衬绫绸、下垫软毯，人在
里面只觉一颠一颠地摇晃着，分明是在行走之中。
LONG
        );

        set("exits", ([
        ]));

        setup();
        replace_program(ROOM);
}


