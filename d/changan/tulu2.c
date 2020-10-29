// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条黄土飞扬的路，不算太宽，给人一种落寞的感觉，路边
零零散散的分布着几片小田地，偶然也能看得见一些炊烟。四周一片
的荒寂。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northup"   : "/d/changan/tulu3",
                "southwest" : "/d/changan/tulu1",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}