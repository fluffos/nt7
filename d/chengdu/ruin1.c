// Room: /d/chengdu/ruyin1.c
// Last Modifyed by Lonely on Jan. 4 2002

inherit ROOM;
void create()
{
        set("short", "破旧大宅");
        set("long", @LONG
这里是一间破旧大宅的前院，大厅已经崩塌了一半，焦黑的梁柱挡
住了你的去路，庭院里杂草丛生，看来已经很久没有人住了，据说这里
晚上有鬼魂出现，但是倒也从没听说过有人被害，因此附近的居民仍然
照常生活。
LONG        );
        set("outdoors", "chengdu");
        set("exits", ([ /* sizeof() == 1 */
                "west"  : __DIR__"ruin2",
                "east"  : __DIR__"westroad1",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 2,
                "/d/gaibang/npc/2dai" : 1,
        ]));
        set("coor/x", -15250);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}