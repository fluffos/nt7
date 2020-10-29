inherit __DIR__"zhuang";

void create()
{
        set("short", "梅花桩一");
        set("long", @LONG
一人多高的梅花桩，向下望去真让人心惊胆颤。
LONG
        );

        set("exits", ([
        "down" : __DIR__"lianwu",
        "northeast" : __DIR__"zhuang3",
        "southeast" : __DIR__"zhuang5",
]));
        setup();
}
