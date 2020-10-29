#include <ansi.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIY "【主页维护工作室】" NOR);
        set("long", @LONG
这里是主页维护人员工作的地方，地上散落着各种纸片，留言
版上写满着工作记录。
请将工作情况post到留言版，巫师会定期查询。
LONG
);

        set("exits", ([
                "out" : "/d/city/kedian",                
        ]));

        set("valid_startroom", 1);
        set("sleep_room", 1);
        set("no_fight", 1);

        setup();
        "/clone/board/webmaster_b"->foo();
}

