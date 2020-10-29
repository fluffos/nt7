// Room: /d/taishan/taishanjiao.c
// Last Modified by Lonely on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "泰山脚下");
        set("long", @LONG
泰山古称岱山，为五岳的东岳，为道教第二小洞天，向有“五岳独
尊”之称誉，以“泰山天下雄”名闻域内。往北就到进入岱宗坊的前庭
遥参亭了。
LONG );
        set("exits", ([
                "north" : __DIR__"yaocan",
                "south" : __DIR__"yidao3",
                "east"  : __DIR__"kedian",
        ]));
        set("objects", ([
                CLASS_D("misc") + "/shanzheng" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}