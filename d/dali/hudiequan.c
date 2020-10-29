//Room: /d/dali/hudiequan.c
//Date: June. 29 1998 by Java

inherit BUILD_ROOM;
void create()
{
        set("short","蝴蝶泉");
        set("long", @LONG
蝴蝶泉就显得更加清凉湿润，大量的蝴蝶，从四面八方，汇集在
树荫下，花丛中，翩翩起舞，成千上万只彩蝶，欢聚一处，使这里变
得花团锦簇。特别是在蝴蝶泉上，顺着那倒垂的扬柳，无数蝴蝶，一
只咬着一只的尾部，形成千百个蝶串，人来不惊，投石不散，构成令
人惊叹的奇观。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yuxuguanqian",
            "east"   : "/d/dali/xiaodao1",
        ]));
        set("max_room",4);
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
}