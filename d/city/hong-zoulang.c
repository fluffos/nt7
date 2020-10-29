//Room: /d/ruzhou/hong-zoulang.c
// by llm 99/06/12

inherit ROOM;

void create()
{
        set("short", "红娘庄走廊");
   set("long", @LONG
走廊两边是红漆金粉的廊柱雕栏，高低错落地挑着两排红灯笼。地上
铺着厚厚的大红地毯，急待结婚的新人们进来踩在上面，一股喜庆幸福之
感自心底油然而生。前面是一个不大的门厅。
LONG
   );
        set("exits", ([
                "west" : __DIR__"hong-damen",
                "east" : __DIR__"hongniang-zhuang",
   ]) );

   set("objects", ([
           __DIR__"npc/xiao-hongniang" : 1,
      ]) );
	set("coor/x", 20);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}