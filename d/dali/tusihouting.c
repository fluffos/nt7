//Room: /d/dali/tusihouting.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","后厅");
        set("long", @LONG
议事厅后是后厅，是一楼一底的中式建筑。屋角雕刻细密，纹饰
精美，各种图案和禽兽花木的雕刻，栩栩如生，纹路新颖。这是云南
十八座土司府中保留最好的一座。
LONG );
        set("exits",([ /* sizeof() == 2 */
            "south"  : "/d/dali/tusimentang",
         "down" : "/d/xueshan/mishi" , 
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6881);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}