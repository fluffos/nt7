inherit ROOM;
void create()
{
        set("short", "石屋");
        set("long",
"走着走着，秘道中忽然亮起了灯光。前面岩壁，已被凿成石灯的模样\n"
"，灯蕊竟有十余条之多，互相连接。石室中一直是阴湿而黝暗，左面一张\n"
"石床，右面一张石桌，几张石凳。\n"
);
        set("no_magic", "1");
        set("exits",([
                "out" :__DIR__"shishi",
        ]) );
        set("objects",([
                __DIR__"npc/kuangren1" : 1,
        ]) );
        setup();
}
