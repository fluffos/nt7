// Room: xiaoting.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "小厅");
        set("long", @LONG
一间雅致的小厅，桌上点着一对巨烛，东壁上有四幅屏条，绘的是梅兰竹
菊，可是顺序却挂成了兰竹梅菊，西壁上的春夏秋冬，则挂成了冬夏春秋。看
来此间主人必是个武人。
LONG
        );
        set("exits", ([
            "east" : __DIR__"guzhong",           
        ]));

        set("objects", ([
            __DIR__"npc/zhong_ling" : 1,
        ]));

        setup();
}