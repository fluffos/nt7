inherit ROOM;

void create()
{
        set("short", "杂货铺");
        set("long", @LONG
这里是古村的杂货铺，两排长长的货架上摆满了玩家们所
需要的东西。老板是个胖胖的中年人，正在一边精神的招呼着
客人，如果你需要什么的话可以看看（输入指令 list）。
LONG);
        set("exits", ([
                "north" : __DIR__"road2",
        ]));

        set("xinshoucun", 1);
        set("no_fight", 1);

        set("objects", ([
               __DIR__"npc/qianbo"  :  1,
        ]));
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}
