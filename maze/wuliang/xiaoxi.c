// xiaoxi.c
// bbb 1997/06/11
// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "山中小溪");
        set("long", @LONG
在山路的旁边了出现一条小溪。周围安静极了，只听见小河流水在孱孱作
响。一些口渴的行人在溪边喝水，远处好象有一些看不清模样的动物也在溪里
玩闹。南面是一条上山的路，正北面都是荆棘和矮草灌木，走在里面一定会划
伤身体，依稀有一条小路通向深处。
LONG
        );
        set("resource/water", 1);

        set("exits", ([
             "north" : __DIR__"shanlu8",                
	     "southwest" : "/d/dali/shanlu3",
             "southup" : __DIR__"shanlu5",
        ]));
        set("outdoors", "大理");
        set("objects", ([
//            __DIR__"obj/yeguo" : 2,
        ]));

        set("coor/x",-300);
  set("coor/y",-300);
   set("coor/z",-20);
   setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        int current_water;
	int max_water;
        object me;

        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water) {
            set("water", current_water+30, me);
            message("vision", me->name()+"趴在溪边用手捧了一些水喝。\n"
            , environment(me), ({me}) );
            write("你喝了一口从山上流淌下来的溪水，觉得舒服多了。\n");
        }
        else write("喝那么多的凉水，你不怕生病吗?\n");

        return 1;
}

int valid_leave(object me, string dir)
{
        if(dir=="north" ){
        if( query("can_ride", me)){
          return 0;
          }       
        if( query_temp("ride_horse", me) )
        return notify_fail("你不怕荆棘和矮草灌木伤了马匹。\n");
        }
        return ::valid_leave(me, dir);
}