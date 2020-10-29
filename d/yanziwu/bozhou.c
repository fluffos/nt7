#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "泊舟坞");
        set("long", @LONG
此处一片芦苇，茭白丛中现出一座船坞，大小船只依次排开。菱
花荷叶丛中条条水道 (river)四通八达，由此可乘船离开燕子坞。湖
面系着尾小舟。北面远远望过去有个梯子。
LONG );
        //set("arrive_room", "/d/yanziwu/hupan");
        set("to", __DIR__"hupan");
        set("exits", ([
                "east"      : __DIR__"pindi",
                "northdown" : __DIR__"muti",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "yanziwu");
        replace_program(RIVER);
}
