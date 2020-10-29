// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "钱庄");
        set("long", @LONG
钱家开的钱庄，在中原可算是最老字号和信誉最好的钱庄了，已
有几百年的历史，在全国各地都有分号。它发行的银票信誉极好，通
行大江南北。钱庄中央有一半人多高的红木柜台，柜台上面挂着一块
牌子 (paizi)。戴着小眼镜的钱老板正坐在柜台后面看他的帐本，似
乎并没有注意到你进来。
LONG );
	set("exits", ([
		"east" : "/d/city/beidajie1",
	]));
	set("item_desc", ([
		"paizi" : @TEXT
     本钱庄提供以下服务：
      存钱        deposit或者cun
      取钱        withdraw或者qu
      钱币兑换    convert或者duihuan
      查帐        check或者chazhang
      转帐        transfer或者zhuanzhang
TEXT
	]) );

	set("objects", ([
		"/d/city/npc/qian" : 1
	]));
        set("no_fight", 1);
	set("coor/x", -10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}