inherit ROOM;

void create()
{
        set("short", "英雄楼");
        set("long", @LONG
英雄酒楼里桌椅洁净。座中客人衣饰豪奢，十九是富商大贾。这
里可以俯瞰佛山镇全景。
LONG );
        set("objects", ([
                __DIR__"npc/pang": 1,
                __DIR__"npc/shou": 1,
        ]));
        set("exits", ([
                "down" : __DIR__"yingxionglou",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9760);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}