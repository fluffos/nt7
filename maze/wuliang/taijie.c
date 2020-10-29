// taijie.c
// bbb 1997/07/20
// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "台阶");
	set("long", @LONG
一条台阶斜向上引，走到一百多级时，隐隐听到轰隆轰隆的水声，又行二
百余级，水声已经震耳欲聋，前面并有光亮透入，走到台阶的尽头，前面是个
仅可容身的洞穴。
LONG
	);

	set("exits", ([
            "down" : __DIR__"dong1",
            "out" : __DIR__"jiangpan",
	]));
	setup();
}