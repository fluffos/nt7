inherit ROOM;

void create()
{
        set("short", "迷宫出口");
        set("long", @LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG );
        set("no_clean_up", 1);
        set("no_drop", 1);
        set("no_sleep_room", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("exits", ([
                "east":__DIR__"maze/exit", 
                "out": "/d/city/wumiao", 
        ]));  
                    
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "out" && userp(me) && query("exits/out"))
        {
                FUBEN_D->clear_fuben("ultra", query("id", me));
        }
        
        return ::valid_leave(me, dir);
}

