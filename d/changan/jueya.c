// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
    set("short", "绝崖");
    set("long",@LONG
眼前一片空旷，脚下是一个深不见底的悬崖，稍一迈步，崖边的
碎岩就纷纷落了下去，久久都没听到回音。
LONG
        );
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"caodi",
        ]));
        set("coor/x", -10610);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}


