//Room: dongan-daokou.c

inherit ROOM;
void create ()
{
        set ("short", "东安道口");
        set("long", @LONG
长安城自古是繁华胜地，为数代皇朝建都之地，又为盐商大贾所
聚集，殷富甲于天下。东安道口是一个四通八达的路口，西方有一条
大路通往冯诩道，东面是长安东城门，南北方向是连德大道。 
LONG );
        set("exits",([//sizeof() == 5
                "south" : "/d/changan/liande-dadao4",
                "north" : "/d/changan/liande-dadao3",
                "west" : "/d/changan/dongan-dadao",
                "east" : "/d/changan/dong-chengmen",
                "southwest" : "/d/changan/bingying6",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10680);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        