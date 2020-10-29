//Room: yamen-datang.c

inherit ROOM;

void create ()
{
        set ("short", "长安府大堂");
        set("long", @LONG
长安府大堂之上有一种威严之势，不由让你心惊胆颤。前方一张
红木大桌，后面坐着知府大人。上有一幅大匾，写着"廉明清正"四个
烫金大字。桌旁站立着一位老师爷。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/yamen",
        ]));
        set("objects", 
        ([ //sizeof() == 2
                "/d/changan/npc/zhifu" : 1,
                "/d/changan/npc/shiye" : 1,
        ]));

        set("coor/x", -10710);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}