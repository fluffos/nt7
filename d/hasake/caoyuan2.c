// caoyuan1.c 草原
inherit ROOM;
void create()
{
        set("short", "草原");
        set("long", @LONG
你走进了这遍绵绵不绝的大草原，脚下是寸厚的青草，软绵绵的还真
不好走，看来买匹马来代步到是的好主意。北边和西边都有好多帐篷，往
东可以看见沙漠的边缘。
LONG);
        set("exits", ([
            "southeast" : __DIR__"caoyuan",
            "west" : __DIR__"pmchang",
            "south" : __DIR__"caoyuan1",
            "northeast" : __DIR__"caoyuan3",
        ]));
        set("outdoors", "hasake");
        setup();
        replace_program(ROOM);
}