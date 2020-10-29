// Room: fuheqiaoe.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","府河桥");
        set("long", @LONG
这里是成都东门外府河桥。成都自古就是川中首府，府河和南河
夹城而过，成为天然的护城河。由于四川外有峡江，秦岭之险，内仗
绵渝坚城之固，成都却因之自来无坐守成功之绩。往往兵到城下，降
旗高扯了。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "east"  : __DIR__"road2",
            "west"  : __DIR__"eastgate",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15180);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}