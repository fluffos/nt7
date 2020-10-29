// Room: /d/shaolin/hsyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "和尚院二部");
        set("long", @LONG
这里是僧众们饮食起居的地方。靠墙一溜摆着几张木床，床上铺
的是篾席。床头叠着床薄换，冬天想必很冷，僧侣们全靠扎实的内功
根基御寒。地上整齐的放着几个蒲团和木鱼。
LONG );
        set("sleep_room",1);
        set("exits", ([
                "east" : __DIR__"zhulin2",
                "south" : __DIR__"hsyuan1",
                "north" : __DIR__"hsyuan3",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/hui-xiu" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
