inherit ROOM;

void create()
{
        set("short", "稻香居二楼");
        set("long", @LONG
老大一个大厅内相互间用屏风隔成十多个小间。穿戴厉索的小二
端着菜来往奔走，如果你分量够的话，还可以捞到个窗边的位置。边
喝酒边看看下面的繁华街景，人生一乐。
LONG );
        set("objects", ([
                  __DIR__"npc/gaoyanei" : 1,
                  __DIR__"npc/luyuhou" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"daoxiang",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}