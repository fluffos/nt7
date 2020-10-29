inherit ROOM;

void create()
{
        set("short", "福寿庵");
        set("long", @LONG
福寿庵在神水庵南，是一个名叫天性的僧人建造的。庵前有九曲
渠、流杯池，古人曾据在此饮酒流杯观景赋诗，歌咏兴叹不知夕日。
庵旁有株海棠树，数百苍龄高达十余丈。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/zhen" : 1,
                __DIR__"npc/girldizi" : 1,
        ]));
        set("exits", ([
                "enter" : __DIR__"lingwenge",
                "north" : __DIR__"shenshuian",
        ]));
        set("outdoors", "emei");
        set("coor/x", -440);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}