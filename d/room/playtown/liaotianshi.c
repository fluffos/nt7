// Room: /d/playertown/liaotianshi.c 聊天室
// Build 1999.12.10 bmw

inherit ROOM;
void create()
{
        set("short", "聊天室");
        set("long",
"这是一个很普通的房间，里面只是朴素地摆着一些供人休息桌椅，一\n"
"名老翁热情的招呼着客人。房间里到处聚集着一群群的人，相互愉快着交\n"
"流着。在房间的右边有一个小房间，偶尔有一些疲倦的人向右边的房间离去。\n"
);
        set("no_fight", 1);

        set("exits", ([
                "north"  : __DIR__"miao",
        ]));
        setup();
        replace_program(ROOM);
}