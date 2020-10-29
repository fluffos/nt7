// Room: /d/city/shuyuan.c

inherit ROOM;

void create()
{
	set("short", "书院");
        set("long", @LONG
这里是书院的讲堂，窗明几净，一尘不染。一位庄重严肃的老者
坐在太师椅上讲学，那就是当今大儒朱先生了。在他的两侧坐满了求
学的学生。一张古意盎然的书案放在朱先生的前面，案上摆着几本翻
开了的线装书籍。朱先生的身后是一个书架(shujia)讲堂内多历代楹
联石刻，足见书院历史的悠久。值得一提的是嵌在讲堂前左壁的学规
(xuegui)。
LONG );
	set("item_desc", ([ /* sizeof() == 1 */
		"xuegui": "
		日讲经书三起，日看纲目数页。
		通晓时务物理，参读古文诗赋。
		读书必须过笔，会课按时蚤完。
		夜读仍戒晏起，疑误定要力争。

	求学需缴学费纹银二十两。\n",
	]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

	set("exits", ([ /* sizeof() == 2 */
		"up"    : "/d/city/shuyuan2",
		"south" : "/d/city/dongdajie1",
	]));

	set("objects", ([ /* sizeof() == 1 */
		"/d/city/npc/zhu" : 1,
	]));

	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}