//Room: /d/dali/dianchi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","滇池");
        set("long", @LONG
滇池四周的山脉均属昆仑山系，云岭山脉的东支逶迤南下，总称
乌蒙山，有大小数十个山峰。湖身紧靠西山脚下，山环水抱，天光云
影，构成天然的图画。滇池的『滇』在彝语中即是大坝子，兼司马迁
的《史记·西南夷列传》记载，在古代就是这一地区的最大的部族名
称，是名滇池。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"   : "/d/dali/dasenlin",
            "south"   : "/d/dali/yanchi1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}