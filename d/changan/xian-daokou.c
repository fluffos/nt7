//Room: xian-daokou.c

inherit ROOM;
void create ()
{
        set ("short", "西安道口");
        set("long", @LONG
长安城自古是繁华胜地，为数代皇朝建都之地，又为盐商大贾所
聚集，殷富甲于天下。西安道口是一个四通八达的路口，东方有一条
大路通往扶风道，西面是长安西城门，南北方向是永泰大道。 
LONG );
        set("exits",([//sizeof() == 5
                "south" : "/d/changan/yongtai-dadao4",
                "north" : "/d/changan/yongtai-dadao3",
                "west" : "/d/changan/xi-chengmen",
                "east" : "/d/changan/xian-dadao",
                "southeast" : "/d/changan/bingying3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10760);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        