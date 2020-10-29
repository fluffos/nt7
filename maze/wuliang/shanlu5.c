// Room: 山路 5
// bbb 1997/06/11
// Modify By River 98/12
inherit ROOM;
void create()
{
        set("short", "无量山路");
	set("long", @LONG
你正走在一条崎岖不平的路上,四周是阴森森的原始老林,不时传来一阵阵
的野兽叫声, 头顶有一些不知名的小鸟在跳来跳去。东边一条山路向上延伸，
不知道通向哪里。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
	    "eastup" : __DIR__"xiaolu1",
	    "northdown" : __DIR__"xiaoxi",
        ]));
	set("no_clean_up", 0);
        set("outdoors", "大理");

	set("coor/x",-300);
  set("coor/y",-310);
   set("coor/z",-10);
   setup();
}

int valid_leave(object me, string dir)
{
        if(dir=="eastup" ){
        if( query("can_ride", me)){
          return 0;
          }       
        if( query_temp("ride_horse", me) )
        return notify_fail("上山不宜骑马。\n");
        }
        return ::valid_leave(me, dir);
}