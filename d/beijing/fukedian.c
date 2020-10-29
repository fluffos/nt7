inherit ROOM;

void create()
{
        set("short", "虎坊客栈");
        set("long", @LONG
这是京城虎坊路街头邻街的一家客栈。客栈不大，前厅挂着一幅
猛虎下山的巨画。当门挂着对鸳鸯球。球上系着几个小小的黄铜风铃。
微风掠过，风铃发出清脆悦耳的叮咚声。上有横批『虎坊客栈』。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("objects", ([
                "/d/beijing/npc/xiaoer3" : 1,
        ]));
        set("exits", ([
                "north" : "/d/beijing/kediandayuan",
                "south" : "/d/beijing/fu_2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
//        "/clone/board/kedian2_b"->foo();
        replace_program(ROOM);
}