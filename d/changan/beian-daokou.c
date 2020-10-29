//Room: beian-daokou.c

inherit ROOM;

void create ()
{
        set ("short", "北安道口");
        set("long", @LONG
长安城自古是繁华胜地，为数代皇朝建都之地，又为盐商大贾所
聚集，殷富甲于天下。北安道口是一个四通八达的路口，东西方向通
往麒祥街，北面是长安北城门，南方有一条大路通到故皇宫的金水桥。
 
LONG );
        set("exits",([//sizeof() == 4
                "south" : "/d/changan/beian-dadao",
                "north" : "/d/changan/bei-chengmen",
                "west" : "/d/changan/qixiang3",
                "east" : "/d/changan/qixiang4",
                "southeast" : "/d/changan/bingying1",
                "southwest" : "/d/changan/bingying2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}