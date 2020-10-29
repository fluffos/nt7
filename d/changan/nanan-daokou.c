//Room: nanan-daokou.c

inherit ROOM;

void create ()
{
        set ("short", "南安道口");
        set("long", @LONG
长安城自古是繁华胜地，为数代皇朝建都之地，又为盐商大贾所
聚集，殷富甲于天下。南安道口是一个四通八达的路口，东西方向通
往华瑞街，南面是长安南城门，北方有一条大路通到故皇宫的金水桥。
 
LONG );
        set("exits",([//sizeof() == 4
                "south" : "/d/changan/nan-chengmen",
                "north" : "/d/changan/nanan-dadao",
                "west" : "/d/changan/huarui3",
                "east" : "/d/changan/huarui4",
                "northeast" : "/d/changan/bingying4",
                "northwest" : "/d/changan/bingying5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        