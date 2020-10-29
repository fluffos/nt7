inherit ROOM;

void create()
{
        set("short", "韦府大厅");
        set("long", @LONG
这里就是鹿鼎公府的大厅，相当的宽敞明亮，四周的墙上悬挂满
了各朝名人的真迹。正厅中央坐着两个老者，较老的老者身旁边还站
着一个老妇和一个四十多岁的中年男子，那男子骨瘦如柴，不住的咳
嗽。大厅北边是韦公爷的书房，左右两边分别是两个厢房。
LONG );
        set("exits", ([
                "north" : "/d/beijing/weifu_shufang",
                "south" : "/d/beijing/weifu_zoulang2",
                "west" : "/d/beijing/weifu_fangw",
                "east" : "/d/beijing/weifu_fange",
        ]));
        set("objects", ([
                "/d/beijing/npc/guixinshu" : 1,
                "/d/beijing/npc/guierniang" : 1,
                "/d/beijing/npc/guizhong" : 1,
                "/d/beijing/npc/liudahong" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}