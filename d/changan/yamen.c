//Room: yamen.c

inherit ROOM;

void create ()
{
        set ("short", "衙门大门");
        set("long", @LONG
这是长安城的衙门大门，也是长安城最高的行政机构，这里负责
管理城里的大事小情。无论是偷鸡摸狗的小贼，还是放火杀人的强盗，
都会在这里受到应有的处罚。墙上贴着一张告示(gaoshi)
LONG );
        set("item_desc", ([
                "gaoshi": ""
        ]) );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/yamen-datang",
                "north" : "/d/changan/qinglong3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yayi" : 4,
        ]));

        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}