// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "烽火台");
        set("long", @LONG
这里是高丽的东烽火台。这里用来检查边境的情况，以及时传递战
况。再往南边走，就是高丽的朝阳门了。这里戒备森严，有几个官兵在
这里检查来往的行人。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southdown" : __DIR__"shulin3",
                //"north":__DIR__"beifenghuotai",
        ]));
      set("objects",([
         __DIR__"npc/bing":2,
         ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","dongfenghuotai");
  return ::valid_leave(ob,dir);
}