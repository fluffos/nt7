inherit ROOM;

void create()
{
        set("short", "南街广场");
        set("long", @LONG
这里是南街广场了，由于靠近汴梁城中心，这里更为繁华，西边
是一个妓院，据说京城第一名妓『李师师』就是自那里出名的，看着
往来买笑之人蜂拥不绝，当可知道传言非虚也，东边是个绸缎庄，里
面经营的各种布匹很受达官贵人们的青睐。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"center",
                "south" : __DIR__"nandajie1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}
