// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "天台");
        set("long", @LONG
这里高丽的天台。这里是求神祭天的地方。下面是一个大广场，宽
阔无比。从这里可以看到南边高丽城的风光。这里有几个香烛和其他求
神的东西，看起来有些神秘。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southdown" : __DIR__"guangchang",
                //"northup":__DIR__"tiantai",
        ]));
       setup();
        
}

int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","tiantai");
  return ::valid_leave(ob,dir);
}
