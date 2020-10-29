//Room: /d/suzhou/hong-zoulang.c
// by llm 99/06/12

inherit ROOM;

void create()
{
        set("short", "红娘庄走廊");
        set("long", @LONG
走廊两边是红漆金粉的廊柱雕栏，高低错落地挑着两排红灯笼。
地上铺着厚厚的大红地毯，急待结婚的新人们进来踩在上面，一股喜
庆幸福之感自心底油然而生。前面是一个不大的门厅。
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hong-damen",
                "east" : "/d/suzhou/hongniang-zhuang",
   ]) );

   set("objects", ([
           "/d/suzhou/npc/xiao-hongniang" : 1,
      ]) );
   set("coor/x", 220);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
