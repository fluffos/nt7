//Room: /d/dali/wangfulu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","王府路");
        set("long", @LONG
镇南王府前大道，延伸两里余。街面是由碗口大的彩色石块铺砌
而成，青兰紫绿，煞是好看。城内居民族裔繁杂，习俗各异，饮食穿
着无不异于中原。太学生们的朗朗之声透室可闻。北面是一座连云府
院，‘镇南’、‘保国’两面大旗矗立门前。
LONG );
        set("objects", ([
           CLASS_D("dali")+"/fusigui": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "west"   : "/d/dali/paifang",
            "north"  : "/d/dali/wangfugate",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}