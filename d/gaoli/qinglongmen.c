// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飞凤门");
        set("long", @LONG
这里是高丽的飞凤门。东面就到了城中，远望人山人海，往来行人
车流不绝。西面一条大路通向中原。城门下有一些执勤的兵士。兵将警
惕的盯着往来人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"qinglong-2",
                "west" : __DIR__"edao1",
                "southwest":__DIR__"dadi",
        ]));
set("objects",([
  __DIR__"npc/guanbing":2,
  __DIR__"npc/wujiang":1,
  ]));
       setup();
        
}

int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","qinglong");
  return ::valid_leave(ob,dir);
}
