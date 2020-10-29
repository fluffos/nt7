// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "烽火台");
        set("long", @LONG        
这是高丽位于海边的一个烽火台。有几个官兵正在这里观海上的情
况。放眼望去，一片碧波，没有边际。看来现在还是风平浪静。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "eastdown" : __DIR__"xiaolu2",
        ]));
        set("objects",([
          __DIR__"npc/bing":2,
          ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","fenghuotai");
  return ::valid_leave(ob,dir);
}
