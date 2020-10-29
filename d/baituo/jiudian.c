inherit ROOM;

void create()
{
        set("short", "酒店");
        set("long", @LONG
这里是一家独具特色的酒店，由于地处白驼山下，酒店可以供应
风味食品。许多中原来客都爱来尝尝鲜，所以酒店生意兴隆。酒店还
经营打散装酒的业务。
LONG );
        set("exits", ([
                "north" : __DIR__"xijie",
        ]));
        set("objects",([
                "/d/baituo/npc/xiaoer" : 1,
        ]));
        set("resource/water", 1);
        set("coor/x", -49970);
        set("coor/y", 19970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}