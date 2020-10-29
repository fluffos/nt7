//lianyunge.c                四川唐门—莲云阁

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "莲云阁");
        set("long",
"这里是莲云阁。这里是一个极大、至广阔的建筑，共有七十二道柱梁\n"
"每个梁柱上都栩栩如生的雕着麒麟、龙凤、犀、饕餮等七十二种不同的奇\n"
"珍异兽。天花板中央雕了个遒劲万钧的“唐”字，令人赞叹的是地板上竟\n"
"也十分逼真的刻有齐天大圣闹天宫，而正中厅堂则是太上老君将孙悟空放\n"
"在丹炉里熬炼的雕画手工，堪称绝世精品，可是更令人惊诧的是，地板并\n"
"不因为这些雕刻而有丝毫凹凸不平，反而还十分平滑，似走在坚冰上一般！\n"
);
        set("exits", ([        
                        "east"  : __DIR__"eting",
                        "west"  : __DIR__"wting",
                        "north" : __DIR__"nzlang1",
                        "south" : __DIR__"shuige2",]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangtian" : 1,
                CLASS_D("tangmen") + "/first" : 1,
        ]));
//        set("length",20);
        set("valid_startroom",1);
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}
