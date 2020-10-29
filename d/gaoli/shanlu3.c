// /d/gaoli/xuanwumen
// Room in 高丽
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是一条山路。东边是一条绎道。这里的山路崎岖曲折，你不禁
小心起来。抬头望去，西边有一个烽火台。这里已经没有什么行人了。
LONG
        );

        set("exits", ([
                "northeast" : __DIR__"edao2",
                "westup":__DIR__"shanlu4",
        ]));
         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


