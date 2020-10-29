inherit ROOM;

void create()
{
        set("short", "三不管");
        set("long", @LONG
这里是四川、湖北与陕西的交界，俗称三不管。小土路的两旁有
疏疏落落的农舍耕田，几只牛羊正在吃草。路上行人很少，都匆匆赶
路。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "east"      : __DIR__"wdroad8",
                "southeast" : __DIR__"wdroad9",
                "southwest" : "/d/emei/wdroad",
                "north"     : "/d/yuanyue/shandao1",
        ]));
        set("objects", ([
                "/d/wudang/npc/cow": 1,
        ]));
        set("coor/x", -330);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
