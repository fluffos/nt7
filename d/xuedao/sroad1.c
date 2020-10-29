inherit ROOM;

void create()
{
        set("short","山路");
        set("long", @LONG
川西多是崇山峻岭，交通不便。一条山路蜿蜒在山间，连接着藏
边和中原。
LONG );
        set("exits",([
                "north" : "/d/chengdu/nanheqiaos",
                "west"  : __DIR__"sroad2",
                "south" : "/d/tangmen/bdajie2",
                "northwest" : "/d/lingxiao/boot", 
        ]));
        set("outdoors", "xueshan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
