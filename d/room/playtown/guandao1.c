// by 山猫ADX @ snow 99-12-4

inherit ROOM;

void create ()
{
        set("short",  "官道");
        set("long",  @LONG
这是一条宽阔笔直的官道，黄土路面，足可容得下十马并驰。往东通向
汴梁城，附近有一个玩家村。
LONG);
        set("exits",  ([
                "west"  :  __DIR__"guandao2",
        ]));
        set("outdoors",  1);
        setup();
        replace_program(ROOM);
}