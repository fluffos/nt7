inherit ROOM;

void create()
{
        set("short", "龙亭园");
        set("long", @LONG
这里是一片花木葱郁的园林。园林的南北两边分别是扬家湖和潘
家湖，湖中碧波荡漾，湖边垂柳依依，芳草如茵。从此向东是龙亭大
殿，西面是西大街道。
LONG );
        set("objects", ([
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"longting",
                "west" : __DIR__"wroad3",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shiqing" : 1,
        ]));

        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}