inherit ROOM;

void create()
{
        set("short", "灵塔林");
        set("long",@LONG
走出了小路，眼前豁然一亮，这是一片塔林。放眼望去，林林总总
有不下百座高矮不一的石塔，这些都是历代高僧圆寂后，为他们修的
灵塔。这里冷冷清清，不时传来几声野兽的嗥叫，走在塔林中，你的
心中不免有些害怕。
LONG
        );
        set("outdoors", "tianlongsi");
        set("exits", ([
		"east" : __DIR__"shanlu-4",
        ]));
//	set("objects",([
//                __DIR__"npc/saodiseng" : 1,
//        ]));
        set("coor/x",-460);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
