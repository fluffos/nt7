//Room: /d/dali/jingzhuang6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第六层");
        set("long", @LONG
有神龛五座，内中雕有佛像浮雕二百余座。布局严密，层次分明；
表情各异，比例协调；刀痕尤劲，备极精巧；线条流畅，栩栩如生；
不愧是滇南石雕艺术的珍品。世代金文家皆赞『滇中艺术，此及品也
』。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang7",
            "down"  : "/d/dali/jingzhuang5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 59);
	setup();
        replace_program(ROOM);
}