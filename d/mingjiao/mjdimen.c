// Room: /d/mingjiao/mjdimen.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "草地");
        set("long", @LONG
这是一片芳草地，落英缤纷，蜂歌蝶舞，朝露夕光，沁人心脾。
几个小姑娘莺声曼影，顽皮可人，宛如三月桃李，腊冬嫩梅，惹人怜
爱。任你是江湖豪杰，走到这里，心中也平添几寸温柔，少却三分杀
意。
LONG );
    set("exits", ([
        "northeast" : __DIR__"mjdimen1",
        "southwest" : __DIR__"mjsimen1",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}
