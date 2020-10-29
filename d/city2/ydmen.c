inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "永定门");
        set("long",
"\n"
"                         s________________s
                        /LLLLLLLLLLLLLLLLLL\\
    []__[]             ^^||======||======||^^             []__[]
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏------┓_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_┃"HIW"永定门"NOR"┃__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__|┗------┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_/        \\__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]\n\n"
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north"    : __DIR__"hgdadao1",
                "south"    : __DIR__"center",
                "east" : __DIR__"ssfmen",
        ]));

        set("objects", ([
                __DIR__"npc/jinyiwei" : 3,
        ]));
        setup();
}

int valid_leave(object me,string dir)
{
       object *env,room;
       int i;

       room=this_object();
       if( userp(me) && query("degree_jungong", me)<8 && dir == "north" )
       {
        addn_temp("voilet_hg", 1, me);
        if( query_temp("voilet_hg", me)<3 )
        {
         if( query("degree_jungong", me) )
         return notify_fail(
         "锦衣卫一把拦住你道：大人官低位卑，如何能够进宫面圣！\n");
         else
         return notify_fail(
         "锦衣卫一把拦住你道：那里来的刁民，还不速速离去，否则休怪刀下无情！\n");
        } else
        {
         if( query_temp("voilet_hg", me) == 3 )
         {
          env=all_inventory(room);
          for(i=0;i<sizeof(env);i++)
          {
           if( query("id", env[i]) == "jinyiwei" )
           env[i]->kill_ob(me);
          }
          return notify_fail(HIR"你把心一横，决心力闯皇宫！\n"NOR);
         }
        }
      }
      return ::valid_leave(me,dir);
}
