// Room: /d/playtown/biwuchang.c 比武场
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "比武场");
        set("long",
"这是玩家村里的村民练武和过招的地方，时而会冲上两个人来相互切\n"
"磋，大概是因为这里是一个凹地的原因吧，这里总是很大没有什么风，一\n"
"点点小小的动静在这里都会听得清楚。不远的地方埋着一个小石碑（bei）\n"
",似乎年代很久。\n"
);
        set("outdoors", "playertown");
        set("exits", ([
                "south"  : __DIR__"miao",
        ]));
        setup();
        replace_program(ROOM);
}