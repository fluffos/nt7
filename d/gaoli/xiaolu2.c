// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "小路");
        set("long", @LONG
你走在一条小路之上。再往西边走就是高丽的一个烽火台了。烽火
台用来传递军情。不时有几个官兵从这里走过，检查着来往的行人。南
边大海的波涛声，更增添了几分雄壮的氛围。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"xiaolu1",
                "westup":__DIR__"fenghuotai",
                "northdown":__DIR__"zhuangjiadi",
        ]));
       setup();
        replace_program(ROOM);
}        
