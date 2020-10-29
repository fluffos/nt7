//Room: minju3.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
这所房子看起来好像已经很久没人住了。雕花漆彩的门窗已是破
败不堪，满目蛛丝鼠粪，墙上地下到处都是灰尘，一只老鼠跑来跑去。
院子里杂草丛生，宅外墙满是青苔蜘网，显得既荒凉又阴森。四周死
一般的沉寂。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui3",
        ]));

        set("coor/x", -10730);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}