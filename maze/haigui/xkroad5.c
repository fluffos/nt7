inherit ROOM;

void create()
{
        set("short", "渔村晒网场");
        set("long", @LONG
小村不大，却有个好大的晒网场。几个小孩在场中无忧地玩耍，
声音喧闹。靠南海边上，有个渔夫面向大海，悠然垂钓。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "out"    : "/d/xiakedao/haibin",
        ]));
        set("objects", ([
                CLASS_D("misc/haigui") : 1,
        ]));
        set("coor/x", -1390);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}
