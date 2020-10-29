//Room: baodian.c

inherit ROOM;

void create ()
{
        set ("short", "大雄宝殿");
        set("long", @LONG
大雄宝殿内，金壁辉煌，雕梁画栋，殿两侧共安放了六尊古佛，
古佛之後有释伽与天龙诸部的壁画。大雄宝殿为历朝皇帝招见僧侣、
读经念佛的所在，是以陈设与其馀诸殿大不相同，倒像是庄严肃穆的
佛堂一般。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/baoxiangsi",
                "west" : "/d/changan/piandian",
                "east" : "/d/changan/fangzhangshi",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/xiangke" : 2,
        ]));
        
        set("coor/x", -10730);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}