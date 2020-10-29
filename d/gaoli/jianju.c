// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "北城监狱");
        set("long", @LONG
这里就是高丽的北城监狱了。面前是一道高墙，就是武林高手也难
以跃过。门口站着几个官兵，正上上下下地打量着你。里面不时传来犯
人惨叫的声音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu16",
                       //"west":__DIR__"jianju",
        ]));
        set("objects",([
         __DIR__"npc/bing":4,
         ]));
       setup();
        
}
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","jianyu");
  return ::valid_leave(ob,dir);
}
