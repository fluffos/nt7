// Room: /d/ruzhou/yamen.c
// llm 1999/07/04

inherit ROOM;

void create()
{
        set("short", "汝州府衙门");
        set("long", @LONG
这里便是汝州重镇的衙门大门，朱木大柱，青瓦白墙，异常醒目。铜皮大门两
边摆动放着两头张牙舞爪的石狮子。前面照例都有一个大鼓，显然是供小民鸣冤用
的。直看到去就可以看到知府做镇的大堂。
LONG
        );
        set("exits", ([
           "south" : __DIR__"xidajie",
      "north" : __DIR__"yamen-datang",
        ]));
        set("objects", ([
        ]));

	set("coor/x", -6770);
	set("coor/y", 1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}