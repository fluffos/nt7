// Room: guzhong.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "万劫谷");
        set("long", @LONG
你来到了万劫谷内，对面不远处是几间瓦房，左首边另有一间小瓦房。两
边的山壁很陡峭，看来是没法上下的。谷中一条小路绕过正面的房舍通往谷后，
不知去向什么地方。
LONG
        );
        set("exits", ([
            "north" : __DIR__"xiaojing",
            "south" : __DIR__"keting",
            "west" : __DIR__"xiaoting",
        ]));

        set("objects", ([
              __DIR__"npc/laifu_er" : 1,
              __DIR__"npc/jinxi_er" : 1,
        ]));
        
        set("outdoors", "大理");

        setup();
}