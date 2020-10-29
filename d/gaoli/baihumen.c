// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝阳门");
        set("long", @LONG
这里是高丽的朝阳门。西面就到了城中，远望人山人海，往来行人
车流不绝。东面一条大路通向新罗和百济。城门下有一些执勤的兵士。
兵将警惕的盯着往来人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"baihu-2",
                "east" : __DIR__"dadao1",
                "northeast":__DIR__"shulin1",
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
    ob->add_temp_array("xunluo_dir","baihu");
  return ::valid_leave(ob,dir);
}
