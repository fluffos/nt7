inherit ROOM;

void create()
{
        set("short", "宣德门");
        set("long", @LONG
宣德门是开封的北城门，由于这里历来是皇城所在。城墙建筑得
格外牢固。两边的藏兵洞主可容千人，其作用是当敌人攻破城门之时，
由伏兵杀出，截杀敌人。
LONG );
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kaifeng");
        set("exits", ([
                  "south" : __DIR__"road6",
                  "north" : __DIR__"jiaowai",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}