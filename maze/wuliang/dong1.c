// Room: /dali/dong1.c
// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "石室");
	set("long", @LONG
所处之地是座圆型石室，左边石壁上镶着一块水晶，约有铜盆大小，光亮
即由水晶中透入。向外瞧去，可看到水流不停晃动，原来这里地处水底。室内
有一石桌，尘土寸积，不知已有多少年无人来此。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
	   "enter" : __DIR__"dong2",
           "out" : __DIR__"dongkou",
           "up" : __DIR__"taijie",
        ]));
	set("no_clean_up", 0);

	setup();
}