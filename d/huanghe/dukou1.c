#include <ansi.h>
inherit RIVER;

void create()
{
        set ("short", "黄河渡口");
        set ("long", @LONG
渡口前就是汹涌澎湃的黄河 (river)了。浊流滚滚，泥沙
俱下，声震数里。两岸渡船来来往往，在波谷中穿行，甚为凶
险。过了黄河，就是华北了。
LONG);
        set("to", "/d/beijing/dukou2");
        set("exits", ([
                "south" : __DIR__"huanghe4",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu",
        }));

        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        setup();
        replace_program(RIVER);
}
