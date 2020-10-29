// Room: /d/yueyang/yamen.c
// Last Modifyed by Lonely on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "衙门");
        set("long", @LONG
这里是岳阳府衙。两扇朱木大门紧紧关闭着，门上贴着“老爷丁忧”
字样的字条，看来新官未至，这个门也就不用开了。“肃静”“回避”
的牌子分放两头石狮子的旁边。门前侧面架子摆着个皮鼓，挂着一对木
棰。显然是供小民鸣冤用的。几名衙役在门前巡逻。
LONG );
        set("exits", ([
                "south" : __DIR__"dongjie",
        ]));
        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));
        set("outdoors", "yueyang");
	set("coor/x", -6190);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}