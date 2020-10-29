//  Room:  /d/luoyang/wanglianwu.c

inherit  ROOM;

void  create  ()
{
        set("short",  "练武厅");
        set("long",  @LONG
据说，王家威震豫鄂的武功，就是在这个练武厅里练出来的。可你
看见的也只不过是一个很寻常的屋子而已，唯一突出的，不过是东墙上
挂满的一壁单刀罢了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wanghuating",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -7021);
	set("coor/y", 2139);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}