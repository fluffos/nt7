inherit ROOM;

void create()
{
        set("short", "睹光台");
        set("long", @LONG
这里是看日出、云海、佛光、神灯之地。台下深崖万丈陡彻无底，
云遮雾掩。极目四望，数百里外的大小雪山皆历历在目。金顶云海，
迷迷茫茫，笼罩四野，远接天际。云海轻荡时，你在金顶，脚踏白云，
大有飘飘欲仙之感；当云涛迅猛涌来时整个金顶都似在向前浮动，令
人有乘舟欲风之意。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/bei" : 1,
        ]));
        set("outdoors", "emei");
        set("exits", ([
                "northeast" : __DIR__"huacangan",
                "northwest" : __DIR__"woyunan",
                "south" : __DIR__"dgtsheshenya", 
        ]));
        set("coor/x", -570);
        set("coor/y", -330);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}