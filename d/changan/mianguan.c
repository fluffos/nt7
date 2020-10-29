//Room: mianguan.c

inherit ROOM;

void create ()
{
        set ("short", "面馆");
        set("long", @LONG
据说这面馆十几年前就在这里了，而且不论刮风下雨，不论过年
过节，这面馆从未休息过一天。所以城里的夜游神都放心得很，因为
就算回家老婆不开门，至少还可以在老张的面馆里吃上一碗热气腾腾
的牛肉面。
LONG );
        //set("item_desc", ([" *** " : " *** ", ]));
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/huarui2",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/laozhang" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10740);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}