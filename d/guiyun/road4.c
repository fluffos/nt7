// Room: /d/guiyun/road4.c
// Last Modified by Lonely on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "归云庄前");
        set("long",@LONG
这是通向归云庄的道路，西面就是归云庄。向南是一条小路，北面
是一片绿油油的草地。
LONG
);
        set("exits",([
                "west"  : __DIR__"shiqiao",
                "south" : __DIR__"road3",
                "north" : __DIR__"caodi1",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 290);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west")
        {
                write("庄前有一个依据九宫算术布成的桃花阵。\n");
                if( (query("family/family_name", me) == "桃花岛" && 
                        me->query_skill("qimen-wuxing", 1) > 14) ||
                        me->query_skill("qimen-wuxing", 1) > 39)
                        write( "由于你平常看惯了这些简易的阵法，所以不用细想，信步就走出了阵！\n");
                else {
                        set_temp("jiugong_dir", "w", me);
                        me->move(__DIR__"jiugong" + (random(9) + 1));
                        return -1;
                }
        }
        return ::valid_leave(me, dir);
}
