// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "烽火台");
        set("long", @LONG        
这是高丽位于西边山峰上的一个烽火台。有几个官兵正在这里观察
情况。从这里可以看到东边高丽城的全貌，非常壮观。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "eastdown" : __DIR__"shanlu5",
                
        ]));
     set("objects",([
       __DIR__"npc/bing":2,
       ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","xfenghuotai");
  return ::valid_leave(ob,dir);
}
